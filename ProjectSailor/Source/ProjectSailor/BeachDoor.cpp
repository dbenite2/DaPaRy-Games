// Property of DaPaRy Games

#include "BeachDoor.h"

#include "ProjectSailorCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ABeachDoor::ABeachDoor() {
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SceneComponent->SetupAttachment(RootComponent);

	LeftPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Door Pivot"));
	LeftPivot->SetupAttachment(SceneComponent);
	
	RightPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Door Pivot"));
	RightPivot->SetupAttachment(SceneComponent);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door"));
	LeftDoor->SetupAttachment(LeftPivot);

	LeftDoorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Door Collider"));
	LeftDoorCollider->SetupAttachment(LeftPivot);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door"));
	RightDoor->SetupAttachment(RightPivot);

	RightDoorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Door Collider"));
	RightDoorCollider->SetupAttachment(RightPivot);

	DoorTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	DoorTrigger->SetupAttachment(SceneComponent);

	DoorTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABeachDoor::OnTriggerBeginOverlap);

}

void ABeachDoor::BeginPlay() {
	Super::BeginPlay();
	
}

void ABeachDoor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bActivateDoors) {
		TimeCounter += DeltaTime;
		float Value = TimeCounter/AnimationDuration;

		if (Value > 1.f) {
			bActivateDoors = false;
			Value = 1.f;
		}
		const float AnimationEval = AnimationCurve.ExternalCurve ? AnimationCurve.ExternalCurve->GetFloatValue(Value) :
		AnimationCurve.EditorCurveData.Eval(Value);

		FRotator LeftRotator = LeftPivot->GetRelativeRotation();
		FRotator RightRotator = RightPivot->GetRelativeRotation();

		const float NewLeftPos = FMath::Lerp(0, LeftDoorRotationGoal, AnimationEval);
		const float NewRightPos = FMath::Lerp(0, RightDoorRotationGoal, AnimationEval);
		LeftRotator.Yaw = NewLeftPos;
		RightRotator.Yaw = NewRightPos;
		LeftPivot->SetRelativeRotation(LeftRotator);
		RightPivot->SetRelativeRotation(RightRotator);
	}

}

void ABeachDoor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AProjectSailorCharacter* Player = Cast<AProjectSailorCharacter>(OtherActor);
	USailorInstance* GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (Player) {
		if (GameManager->GetCurrentLevelStatus(CurrentLevelName).bGoal2Complete) {
			bActivateDoors = true;
			GameManager->SetCurrentLevelStatus(CurrentLevelName, 0);
		}
	}
}


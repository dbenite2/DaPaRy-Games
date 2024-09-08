// Property of DaPaRy Games

#include "BeachDoor.h"

#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "SailorInstance.h"

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

	RightDoorParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Right Door Particles"));
	RightDoorParticle->SetupAttachment(RightDoor);
	RightDoorParticle->SetVisibility(false);
	RightDoorParticle->bAutoActivate = false;
	
	LeftDoorParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Left Door Particles"));
	LeftDoorParticle->SetupAttachment(LeftDoor);
	LeftDoorParticle->SetVisibility(false);
	LeftDoorParticle->bAutoActivate = false;

}

void ABeachDoor::BeginPlay() {
	Super::BeginPlay();
	if (ParticleSystem) {
		RightDoorParticle->SetTemplate(ParticleSystem);
		// LeftDoorParticle->SetTemplate(ParticleSystem);
	}
}

void ABeachDoor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bActivateDoors) {
		TimeCounter += DeltaTime;
		float Value = TimeCounter/AnimationDuration;

		if (Value > 1.f) {
			bActivateDoors = false;
			RightDoorParticle->DeactivateSystem();
			LeftDoorParticle->DeactivateSystem();
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

FName ABeachDoor::GetInteractTag_Implementation() {
	return InteractTag;
}

void ABeachDoor::Interact_Implementation(bool bInteractive) {
	ActivateDoors();
}

void ABeachDoor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AProjectSailorCharacter* Player = Cast<AProjectSailorCharacter>(OtherActor);
	
}

void ABeachDoor::ActivateDoors() {
	USailorInstance* GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		bActivateDoors = true;
		RightDoorParticle->SetVisibility(true);
		RightDoorParticle->ActivateSystem();
		LeftDoorParticle->SetVisibility(true);
		LeftDoorParticle->ActivateSystem();
		GameManager->SetCurrentLevelStatus(CurrentLevelName, 0);
		AMyAudioSubsystemActor* AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
		AudioSubsystemActor->PlaySFX1("stoneDoor");
	
}


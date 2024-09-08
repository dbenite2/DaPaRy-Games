// Property of DaPaRy Games


#include "TileInteraction.h"

ATileInteraction::ATileInteraction() {

	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(150.f, 150.f, 50.f));
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATileInteraction::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATileInteraction::OnOverlapEnd);
}

void ATileInteraction::BeginPlay() {
	Super::BeginPlay();
	
}

void ATileInteraction::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bIsDropping) {
		ElapsedTime += DeltaTime;
		float LerpAlpha = ElapsedTime / (DropDistance / DropSpeed); 

		if (LerpAlpha >= 1.0f) {
			SetActorLocation(TargetLocation);
			objectTileInteraction->droopDone = true;
			bIsDropping = false;
		}
		else {
			FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, LerpAlpha);
			SetActorLocation(NewLocation);
		}
	}
}

void ATileInteraction::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this)) {
		pickableObject = Cast<APickable_Object>(OtherActor);

		if(pickableObject) {
			InitialLocation = GetActorLocation();
			TargetLocation = InitialLocation - FVector(0, 0, DropDistance);
			bIsDropping = true;
		}
	}
}

void ATileInteraction::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this))
	{
		
	}
}

void ATileInteraction::UpdateDropping() {
	float value;
	FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, value);
	pickableObject->SetActorLocation(NewLocation);
}

// Property of DaPaRy Games


#include "ObjectTileInteraction.h"

AObjectTileInteraction::AObjectTileInteraction() {
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

void AObjectTileInteraction::BeginPlay() {
	Super::BeginPlay();
	
}

void AObjectTileInteraction::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (droopDone) {
		ElapsedTime += DeltaTime;
		float LerpAlpha = ElapsedTime / (DropDistance / DropSpeed);

		if (LerpAlpha >= 1.0f) {
			SetActorLocation(TargetLocation);
			droopDone = false;
		} else {
			FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, LerpAlpha);
			SetActorLocation(NewLocation);
		}
	}
}

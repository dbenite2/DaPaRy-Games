// Property of DaPaRy Games


#include "ObjectTileInteraction.h"

// Sets default values
AObjectTileInteraction::AObjectTileInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AObjectTileInteraction::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectTileInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (droopDone)
	{
		ElapsedTime += DeltaTime;
		float LerpAlpha = ElapsedTime / (DropDistance / DropSpeed);  // Tiempo actual / tiempo total

		if (LerpAlpha >= 1.0f)
		{
			SetActorLocation(TargetLocation);
			droopDone = false;
		}
		else
		{
			FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, LerpAlpha);
			SetActorLocation(NewLocation);
		}
	}

}


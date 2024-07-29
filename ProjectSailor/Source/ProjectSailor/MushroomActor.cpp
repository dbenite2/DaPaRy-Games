// Property of DaPaRy Games


#include "MushroomActor.h"

// Sets default values
AMushroomActor::AMushroomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AMushroomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMushroomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation.Z > TargetZ)
	{
		CurrentLocation.Z -= FallingSpeed * DeltaTime;
		if (CurrentLocation.Z < TargetZ)
		{
			CurrentLocation.Z = TargetZ;
		}
		SetActorLocation(CurrentLocation);
	}
}


// Property of DaPaRy Games


#include "MushroomButtonActor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "UObject/ConstructorHelpers.h"

/**
 *Button that make appear the mushroom and deasepear when hit.
 **/

// Sets default values
AMushroomButtonActor::AMushroomButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(DefaultSceneRoot);

	// Create and attach the cube mesh component
	CircleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CircleMesh->SetupAttachment(BaseMesh); // Adjuntar al StaticMesh

	// Set relative location and scale for the cube mesh
	CircleMesh->SetRelativeLocation(FVector(0.f, 0.f, 33.f));
	CircleMesh->SetRelativeScale3D(FVector(3.f, 3.f, 0.01f));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(CircleMesh);
	PointLight->AttenuationRadius = 150.0f;
	PointLight->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	PointLight->SetVisibility(false);
	PointLight->Intensity = 25000.f;
}

// Called when the game starts or when spawned
void AMushroomButtonActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMushroomButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMushroomButtonActor::SpawnMushroom()
{
	BP_InitialPosition->SetActorLocation(SpawnLocation);
	BP_InitialPosition->SetActorHiddenInGame(false);
	BP_InitialPosition->SetActorEnableCollision(true);
	AMushroomActor* MushroomButton = Cast<AMushroomActor>(BP_InitialPosition);
	MushroomButton->IsHit = true;

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}


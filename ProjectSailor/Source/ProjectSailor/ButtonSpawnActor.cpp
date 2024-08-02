// Property of DaPaRy Games


#include "ButtonSpawnActor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AButtonSpawnActor::AButtonSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(DefaultRoot);

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
void AButtonSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AButtonSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonSpawnActor::SpawnActor()
{
	if(BP_ActorSpawnable!=nullptr)
	{
		//put position 
		BP_ActorSpawnable->SetActorLocation(SpawnLocation);
		//appears cube and add physics
		BP_ActorSpawnable->SetActorHiddenInGame(false);
		BP_ActorSpawnable->SetActorEnableCollision(true);
		

		//hide button
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}


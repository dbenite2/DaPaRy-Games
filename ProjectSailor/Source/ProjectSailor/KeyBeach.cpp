// Property of DaPaRy Games


#include "KeyBeach.h"

// Sets default values
AKeyBeach::AKeyBeach()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create and initialize the mesh component
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;
	KeyMesh->SetSimulatePhysics(false);
	KeyMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	
}

// Called when the game starts or when spawned
void AKeyBeach::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyBeach::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AKeyBeach::ActivateKeyPhysics()
{
	KeyMesh->SetSimulatePhysics(true);
}

void AKeyBeach::Interact_Implementation()
{
	IInteractionInterface::Interact_Implementation();
	ActivateKeyPhysics();
}


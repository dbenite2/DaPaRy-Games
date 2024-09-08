// Property of DaPaRy Games


#include "Pickable_Object.h"

APickable_Object::APickable_Object() {
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mesh);
	// mesh->SetupAttachment(SceneComponent);
}

void APickable_Object::BeginPlay() {
	Super::BeginPlay();
	
}

void APickable_Object::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APickable_Object::PickedObject() {
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	mesh->SetAngularDamping(5.f);
}

void APickable_Object::DropObject() {
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	mesh->SetAngularDamping(0.05f);
}

void APickable_Object::ResetObjectLocation(FVector& Location) {
	// SceneComponent->SetWorldLocation(Location);
	mesh->SetSimulatePhysics(false);
	SetActorLocation(Location, false,nullptr, ETeleportType::TeleportPhysics);
}


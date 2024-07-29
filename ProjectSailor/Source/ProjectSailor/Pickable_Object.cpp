// Property of DaPaRy Games


#include "Pickable_Object.h"

// Sets default values
APickable_Object::APickable_Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
	mesh->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void APickable_Object::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickable_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickable_Object::PickedObject()
{
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	mesh->SetAngularDamping(5.f);
}

void APickable_Object::DropObject()
{
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	mesh->SetAngularDamping(0.05f);
}

// void APickable_Object::TakeDamage()
// {
// 	Destroy();
// }


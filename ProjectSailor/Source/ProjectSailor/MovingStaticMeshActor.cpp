// Property of DaPaRy Games


#include "MovingStaticMeshActor.h"

#include "MovableStaticMeshComponent.h"

AMovingStaticMeshActor::AMovingStaticMeshActor() {
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	MovableMesh = CreateDefaultSubobject<UMovableStaticMeshComponent>(TEXT("Movable Mesh"));
	MovableMesh->SetupAttachment(GetRootComponent());
}

void AMovingStaticMeshActor::BeginPlay() {
	Super::BeginPlay();
	
}

void AMovingStaticMeshActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

FName AMovingStaticMeshActor::GetInteractTag_Implementation() {
	return InteractTag;
}

void AMovingStaticMeshActor::Interact_Implementation(bool bInteractive) {
	if (!bIsDisabled) {
		MovableMesh->Move(bInteractive);
	}
}

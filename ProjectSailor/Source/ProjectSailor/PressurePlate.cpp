// Property of DaPaRy Games

#include "PressurePlate.h"

#include "InteractablePressInterface.h"
#include "KeyBeach.h"
#include "MovableStaticMeshComponent.h"
#include "MyAudioSubsystemActor.h"
#include "Pickable_Object.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

APressurePlate::APressurePlate() {
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	MovableMesh = CreateDefaultSubobject<UMovableStaticMeshComponent>(TEXT("Movable Mesh"));
	MovableMesh->SetupAttachment(BaseMesh);

	OverlapComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Area"));
	OverlapComponent->SetupAttachment(MovableMesh);
}

void APressurePlate::BeginPlay() {
	Super::BeginPlay();
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	OverlapComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void APressurePlate::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APressurePlate::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if(!bIsDisabled && !bIsTriggered) {
		//to know it is not the tutorial
		APickable_Object* pickable_object = Cast<APickable_Object>(OtherActor);
		AKeyBeach* keyBeach = Cast<AKeyBeach>(OtherActor);
		if((pickable_object && !pickable_object->bNotActivatePlatform ) || keyBeach)
		{
			Interact(true);
		}
		MovableMesh->Move(true);
		bIsTriggered = true;
	}
}

void APressurePlate::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	
	if(!bIsDisabled) {
		//to know it is not the tutorial
		APickable_Object* pickable_object = Cast<APickable_Object>(OtherActor);
		AKeyBeach* keyBeach = Cast<AKeyBeach>(OtherActor);
		if((pickable_object && !pickable_object->bNotActivatePlatform ) || keyBeach)
		{
			Interact(false);
		}
		MovableMesh->Move(false);
		bIsTriggered = false;
	}
}


void APressurePlate::Interact(bool bIsInteracting) {
	TArray<AActor*> InteractableActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteractablePressInterface::StaticClass(), InteractableActors);

	for (AActor* Actor : InteractableActors) {
		FName InteractTag = IInteractablePressInterface::Execute_GetInteractTag(Actor);
		for (FName Tag : TargetTags) {
			if (InteractTag.IsEqual(Tag, ENameCase::IgnoreCase)) {
				IInteractablePressInterface::Execute_Interact(Actor, bIsInteracting);
			} 
		}
	}
}


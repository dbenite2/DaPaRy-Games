
#include "ObjectInteraction.h"

UObjectInteraction::UObjectInteraction() {
	PrimaryComponentTick.bCanEverTick = true;
}



void UObjectInteraction::BeginPlay() {
	Super::BeginPlay();
}


void UObjectInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(accessFunctionality) {
		
	}
}

void UObjectInteraction::ActivateObject() {
	accessFunctionality= true;
}

void UObjectInteraction::Interact_Implementation() {
	IInteractionInterface::Interact_Implementation();
	UE_LOG(LogTemp, Warning, TEXT("Interact with Object done!"));
}

bool UObjectInteraction::CanInteract_Implementation() {
	return canMakeAction;
}

UTexture2D* UObjectInteraction::GetObjectImage_Implementation(){
	return ObjectImage;
}


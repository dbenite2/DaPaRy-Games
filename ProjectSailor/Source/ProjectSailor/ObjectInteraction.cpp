// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectInteraction.h"

// Sets default values for this component's properties
UObjectInteraction::UObjectInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UObjectInteraction::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UObjectInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(accessFunctionality)
	{
		//MAKE FUNCTIONALITY
		UE_LOG(LogTemp, Warning, TEXT("Interact with Object done!"));
	}
}

void UObjectInteraction::ActivateObject()
{
	accessFunctionality= true;
}

void UObjectInteraction::Interact_Implementation()
{
	IInteractionInterface::Interact_Implementation();
	ActivateObject();
}

bool UObjectInteraction::CanInteract_Implementation()
{
	return canMakeAction;
}

//returns the image initialized on the editor
UTexture2D* UObjectInteraction::GetObjectImage_Implementation()
{
	
	return ObjectImage;
}


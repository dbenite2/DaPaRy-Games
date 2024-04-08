// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Components/ActorComponent.h"
#include "ObjectInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UObjectInteraction : public UActorComponent,public IInteractionInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectInteraction();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION() void ActivateObject();
	virtual void Interact_Implementation() override;
	virtual bool CanInteract_Implementation() override;
	virtual UTexture2D* GetObjectImage_Implementation() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//image to put on canvas when interacts with this
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ObjectImage{nullptr};
	
	UPROPERTY() bool accessFunctionality = false;
	UPROPERTY() bool canMakeAction = true;
};

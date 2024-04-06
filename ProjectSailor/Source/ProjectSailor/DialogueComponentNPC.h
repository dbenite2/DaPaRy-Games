// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Components/Image.h"
#include "GameFramework/Actor.h"
#include "DialogueComponentNPC.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UDialogueComponentNPC : public UActorComponent,public IInteractionInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponentNPC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION() void ActivateObject();
	virtual void Interact_Implementation() override;
	virtual bool CanInteract_Implementation() override;
	virtual UTexture2D* GetObjectImage_Implementation() override;

private:
	
	//image to put on canvas when interacts with this
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ObjectImage{nullptr};
	
	UPROPERTY() bool accessFunctionality = false;
	UPROPERTY() bool canMakeAction = true;
	
};

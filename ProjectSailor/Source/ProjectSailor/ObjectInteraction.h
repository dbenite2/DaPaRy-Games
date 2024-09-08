
#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Components/ActorComponent.h"
#include "ObjectInteraction.generated.h"

/**
* Defines interactive capabilities for objects in the game.
* This class allows objects to be interacted with, potentially triggering in-game effects or actions,
* such as opening doors, picking up items, or activating machinery.
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UObjectInteraction : public UActorComponent,public IInteractionInterface {
	GENERATED_BODY()

public:	
	UObjectInteraction();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION() void ActivateObject();
	virtual void Interact_Implementation() override;
	virtual bool CanInteract_Implementation() override;
	virtual UTexture2D* GetObjectImage_Implementation() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ObjectImage{nullptr};
	
	UPROPERTY() bool accessFunctionality = false;
	UPROPERTY() bool canMakeAction = true;
};

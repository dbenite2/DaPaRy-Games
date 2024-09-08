// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractablePressInterface.generated.h"
/**
 * The IInteractablePressInterface is an interface that defines standard interaction methods for objects
 * that can be interacted with in a game environment. It provides a contract for interaction-related functionalities,
 * allowing different actors to implement custom behaviors for interaction.
 */

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractablePressInterface : public UInterface {
	GENERATED_BODY()
};

/**
 * Interface that actors can implement to become interactable. This interface allows for defining
 * how an actor is interacted with in the game, particularly specifying what happens when an actor is
 * interacted with and identifying the actor by a specific tag related to its interaction.
 */
class PROJECTSAILOR_API IInteractablePressInterface {
	GENERATED_BODY()

public:
	/**
	 * Retrieves the tag associated with the interactable object. This tag can be used to identify the type of interaction
	 * expected or to distinguish between different interactable objects.
	 * @return Returns a FName representing the interaction tag.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	FName GetInteractTag();

	/**
	 * Triggers an interaction with the implementor of this interface. This method can initiate any number of behaviors
	 * such as opening doors, picking up items, or triggering a dialogue.
	 * @param bInteractive A boolean flag indicating the state or type of interaction, where true might enable
	 * interaction and false could mean the opposite or disable interaction, depending on implementation.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Interact(bool bInteractive);
};

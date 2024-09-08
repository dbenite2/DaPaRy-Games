
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

/**
 * IInteractionInterface provides an interface for implementing interaction functionalities
 * in actors or components. This interface standardizes the ability to interact, check interaction availability,
 * and retrieve associated interaction imagery within the game.
 */

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface {
	GENERATED_BODY()
};

class PROJECTSAILOR_API IInteractionInterface {
	GENERATED_BODY()

public:
	// Executes interaction logic specific to the implementing class.
	UFUNCTION(BlueprintNativeEvent, Category = "Interface")
	void Interact();
	// Determines if interaction is currently possible.
	UFUNCTION(BlueprintNativeEvent, Category = "Interface")
	bool CanInteract();
	// Retrieves a texture related to the interactable object, which can be used for UI displays.
	UFUNCTION(BlueprintNativeEvent, Category = "Interface")
	UTexture2D* GetObjectImage();
	
};

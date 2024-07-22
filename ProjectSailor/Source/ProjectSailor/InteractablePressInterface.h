// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractablePressInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractablePressInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSAILOR_API IInteractablePressInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	FName GetInteractTag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Interact(bool bInteractive);
};

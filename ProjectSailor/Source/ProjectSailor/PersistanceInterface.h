// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PersistanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPersistanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSAILOR_API IPersistanceInterface
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category="Save System")
	void RequestSave(bool Async);
};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "PSSaveGame.h"
#include "UObject/Interface.h"
#include "Savable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USavable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSAILOR_API ISavable
{
	GENERATED_BODY()

	
public:
	void SaveData(UPSSaveGame* SaveGameRef) {
		// temporary Implementation
	}
};

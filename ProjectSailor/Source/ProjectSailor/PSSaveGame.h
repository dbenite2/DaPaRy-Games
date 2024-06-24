// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSAILOR_API UPSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	void SaveAllData(TArray<AActor*> SavableObjects);
	
};

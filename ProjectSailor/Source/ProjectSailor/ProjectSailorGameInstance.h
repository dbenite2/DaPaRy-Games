// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectSailorGameInstance.generated.h"

class USaveGame;
/**
 * Game instance class for Project Sailor
 * handles the save system and persistant information of the game
 */
UCLASS()
class PROJECTSAILOR_API UProjectSailorGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SaveGame(bool bAsync);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
	FString SaveGameSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
	int32 UserIndex{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
	TSubclassOf<USaveGame> SaveGameClass;

protected:

	UPROPERTY()
	USaveGame* SaveGameRef;

	UFUNCTION()
	void OnGameSaved(const FString& SlotName, const int32 UserIndexToSave, bool bSuccess);
	
};

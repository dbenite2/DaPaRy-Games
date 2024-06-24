// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "PersistanceInterface.h"
#include "PSSaveGame.h"
#include "Engine/GameInstance.h"
#include "ProjectSailorGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameCompleted, UPSSaveGame*, SaveGameRef);

/**
 * Game instance class for Project Sailor
 * handles the save system and persistant information of the game
 */
UCLASS()
class PROJECTSAILOR_API UProjectSailorGameInstance : public UGameInstance, public IPersistanceInterface
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
	
	UFUNCTION(BlueprintCallable)
	virtual void RequestSave_Implementation(bool Async) override;

	UPROPERTY(BlueprintAssignable, Category="Save")
	FOnSaveGameCompleted OnSaveGameCompleted;

protected:

	UPROPERTY()
	UPSSaveGame* SaveGameRef;

	UFUNCTION()
	void OnGameSaved(const FString& SlotName, const int32 UserIndexToSave, bool bSuccess);
	
};

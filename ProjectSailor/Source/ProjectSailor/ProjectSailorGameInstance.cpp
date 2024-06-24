// Property of DaPaRy Games


#include "ProjectSailorGameInstance.h"

#include "Savable.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

void UProjectSailorGameInstance::OnGameSaved(const FString& SlotName, const int32 UserIndexToSave, bool bSuccess) {
	if (bSuccess) {
		// Game saved
	} else {
		// error saving game
	}
	OnSaveGameCompleted.Broadcast(SaveGameRef);
}

void UProjectSailorGameInstance::SaveGame(bool bAsync) {
	if (!SaveGameClass) return;

	SaveGameRef = Cast<UPSSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
	if (!SaveGameRef) return;

	if (bAsync) {
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameRef, SaveGameSlotName, UserIndex,
			FAsyncSaveGameToSlotDelegate::CreateUObject(this, &UProjectSailorGameInstance::OnGameSaved));
	} else {
		bool bSuccess = UGameplayStatics::SaveGameToSlot(SaveGameRef, SaveGameSlotName, UserIndex);
		OnGameSaved(SaveGameSlotName, UserIndex, bSuccess);
	}
}

void UProjectSailorGameInstance::RequestSave_Implementation(bool Async) {
	TArray<AActor*> SavableObjects;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavable::StaticClass(), SavableObjects);
	SaveGameRef->SaveAllData(SavableObjects);
	SaveGame(Async);
}

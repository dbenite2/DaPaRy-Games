// Property of DaPaRy Games


#include "ProjectSailorGameInstance.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

void UProjectSailorGameInstance::OnGameSaved(const FString& SlotName, const int32 UserIndexToSave, bool bSuccess) {
	
}

void UProjectSailorGameInstance::SaveGame(bool bAsync) {
	if (!SaveGameClass) return;

	SaveGameRef = Cast<USaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
	if (!SaveGameRef) return;

	if (bAsync) {
		
	}
}


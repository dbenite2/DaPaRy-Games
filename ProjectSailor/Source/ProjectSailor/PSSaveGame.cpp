// Property of DaPaRy Games


#include "PSSaveGame.h"
#include "Savable.h"
#include "GameFramework/Actor.h"


void UPSSaveGame::SaveAllData(TArray<AActor*> SavableObjects) {
	for (AActor* Object : SavableObjects) {
		if (ISavable* SavableObject = Cast<ISavable>(Object)) {
			SavableObject->SaveData(this);
		}
	}
}



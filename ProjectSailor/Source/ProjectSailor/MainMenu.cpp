// Property of DaPaRy Games

#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct() {
	Super::NativeConstruct();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController) {
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}



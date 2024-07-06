// Property of DaPaRy Games

#include "MainMenu.h"

#include "CommonButton.h"
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

	if (OptionsButton) {
		OptionsButton->OnButtonClicked.AddDynamic(this, &UMainMenu::RemoveWidget);
	}
}

void UMainMenu::RemoveWidget() {
	RemoveFromParent();
	if (OptionsWidget) {
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidget);
		if (newWidget) {
			newWidget->AddToViewport();
		}
	}
}

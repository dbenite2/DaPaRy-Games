// Property of DaPaRy Games

#include "MainMenu.h"

#include "CommonButton.h"
#include "OptionsMenu.h"
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
		OptionsButton->OnButtonClicked.AddUniqueDynamic(this, &UMainMenu::RemoveWidget);
	}
}

void UMainMenu::RemoveWidget() {
	RemoveFromParent();
	if (ExternalWidget) {
		ExternalWidget->AddToViewport(1);
	}
	if (OptionsWidget && !ExternalWidget) {
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidget);
		if (newWidget) {
			ExternalWidget = Cast<UOptionsMenu>(newWidget);
			ExternalWidget->InitialWidget = this;
			ExternalWidget->AddToViewport(1);
		}
	}
}

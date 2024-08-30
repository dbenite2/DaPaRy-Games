// Property of DaPaRy Games

#include "MainMenu.h"

#include "CommonButton.h"
#include "ControlsMenu.h"
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
	if (ControlsButton) {
		ControlsButton->OnButtonClicked.AddUniqueDynamic(this, &UMainMenu::RemoveWidget);
	}
}

void UMainMenu::RemoveWidget() {
	RemoveFromParent();
	if (ExternalWidgetOptionsMenu) {
		ExternalWidgetOptionsMenu->AddToViewport(1);
	}
	else if (ExternalWidgetControlsMenu) {
		ExternalWidgetControlsMenu->AddToViewport(1);
	}
	
	if (OptionsWidget && !ExternalWidgetOptionsMenu) {
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidget);
		if (newWidget) {
			ExternalWidgetOptionsMenu = Cast<UOptionsMenu>(newWidget);
			ExternalWidgetOptionsMenu->InitialWidget = this;
			ExternalWidgetOptionsMenu->AddToViewport(1);
		}
	}
	else if(ControlsWidget && !ExternalWidgetControlsMenu) {
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), ControlsWidget);
		if (newWidget) {
			ExternalWidgetControlsMenu = Cast<UControlsMenu>(newWidget);
			ExternalWidgetControlsMenu->InitialWidget = this;
			ExternalWidgetControlsMenu->AddToViewport(1);
		}
	}
}

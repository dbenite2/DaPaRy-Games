// Property of DaPaRy Games

#include "PauseMenu.h"

#include "CommonButton.h"
#include "OptionsMenu.h"

void UPauseMenu::NativeConstruct() {
	if (OptionsButton) {
		OptionsButton->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenu::SwitchWidget);
	}
}

void UPauseMenu::SwitchWidget() {
	RemoveFromParent();
	if (ExternalWidget) {
		ExternalWidget->AddToViewport(1);
	}
	if (OptionsWidget && !ExternalWidget) {
		if (UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidget)) {
			ExternalWidget = Cast<UOptionsMenu>(NewWidget);
			ExternalWidget->InitialWidget = this;
			ExternalWidget->AddToViewport(1);
		} 
	}
}


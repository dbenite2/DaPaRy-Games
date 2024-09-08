// Property of DaPaRy Games


#include "ControlsMenu.h"
#include "CommonButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UControlsMenu::NativeConstruct() {
	Super::NativeConstruct();

	if (BackButton) {
		BackButton->OnButtonClicked.AddUniqueDynamic(this, &UControlsMenu::SwitchWidget);
	}
}

void UControlsMenu::SwitchWidget() {
	RemoveFromParent();
	if (InitialWidget) {
		InitialWidget->AddToViewport(0);
	}
}

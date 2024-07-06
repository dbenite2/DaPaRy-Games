// Property of DaPaRy Games


#include "OptionsMenu.h"

#include "CommonButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsMenu::NativeConstruct() {
	Super::NativeConstruct();

	if (BackButton) {
		BackButton->OnButtonClicked.AddDynamic(this, &UOptionsMenu::SwitchWidget);
	}
	if (ApplyButton) {
		ApplyButton->OnButtonClicked.AddDynamic(this, &UOptionsMenu::ApplyNewSettings);
	}
	if (DecreaseResolutionButton && IncreaseResolutionButton) {
		DecreaseResolutionButton->OnClicked.AddDynamic(this, &UOptionsMenu::ChangeResolutionSize);
		IncreaseResolutionButton->OnClicked.AddDynamic(this, &UOptionsMenu::ChangeResolutionSize);
	}
	if (IncreaseWindowButton && DecreaseWindowButton) {
		IncreaseWindowButton->OnClicked.AddDynamic(this, &UOptionsMenu::ChangeWindowMode);
		DecreaseWindowButton->OnClicked.AddDynamic(this, &UOptionsMenu::ChangeWindowMode);
	}

	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings) {
		WindowModeToApply = UserSettings->GetFullscreenMode();
		UpdateWindowModeText();
	}
}

void UOptionsMenu::SwitchWidget() {
	RemoveFromParent();
	if (InitialWidget) {
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), InitialWidget);
		if (newWidget) {
			newWidget->AddToViewport();
		}
	}
}

void UOptionsMenu::ChangeWindowMode() {
	switch (WindowModeToApply) {
	case EWindowMode::Fullscreen:
		WindowModeToApply = EWindowMode::WindowedFullscreen;
		break;
	case EWindowMode::WindowedFullscreen:
		WindowModeToApply = EWindowMode::Windowed;
		break;
	case EWindowMode::Windowed:
	default:
		WindowModeToApply = EWindowMode::Fullscreen;
		break;
	}
	UpdateWindowModeText();
}

void UOptionsMenu::UpdateWindowModeText() {
	if (WindowText) {
		FText WindowModeTextValue;

		switch (WindowModeToApply) {
		case EWindowMode::Fullscreen:
			WindowModeTextValue = FText::FromString(TEXT("Fullscreen"));
			break;
		case EWindowMode::WindowedFullscreen:
			WindowModeTextValue = FText::FromString(TEXT("Windowed Fullscreen"));
			break;
		case EWindowMode::Windowed:
		default:
			WindowModeTextValue = FText::FromString(TEXT("Windowed"));
			break;
		}

		WindowText->SetText(WindowModeTextValue);
	}
}

void UOptionsMenu::ChangeResolutionSize() {
}

void UOptionsMenu::ApplyNewSettings() {
	if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings()) {
		UserSettings->SetFullscreenMode(WindowModeToApply);
		UserSettings->ApplySettings(false);
	}
}

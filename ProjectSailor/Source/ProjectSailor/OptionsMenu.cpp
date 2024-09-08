// Property of DaPaRy Games

#include "OptionsMenu.h"

#include "CommonButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsMenu::NativeConstruct() {
	Super::NativeConstruct();

	Resolutions.Add(FIntPoint(1920, 1080));
	Resolutions.Add(FIntPoint(1280, 720));
	Resolutions.Add(FIntPoint(800, 600));

	if (BackButton) {
		BackButton->OnButtonClicked.AddUniqueDynamic(this, &UOptionsMenu::SwitchWidget);
	}
	if (ApplyButton) {
		ApplyButton->OnButtonClicked.AddUniqueDynamic(this, &UOptionsMenu::ApplyNewSettings);
	}
	if (DecreaseResolutionButton && IncreaseResolutionButton) {
		IncreaseResolutionButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenu::ChangeResolutionWrapperIncrease);
		DecreaseResolutionButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenu::ChangeResolutionWrapperDecrease);
	}
	if (IncreaseWindowButton && DecreaseWindowButton) {
		IncreaseWindowButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenu::ChangeWindowMode);
		DecreaseWindowButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenu::ChangeWindowMode);
	}

	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings) {
		WindowModeToApply = UserSettings->GetFullscreenMode();
		ResolutionToApply = UserSettings->GetScreenResolution();
		CurrentResolutionIndex = Resolutions.IndexOfByKey(ResolutionToApply);
		UpdateWindowModeText();
		UpdateResolutionText();
	}
}

void UOptionsMenu::SwitchWidget() {
	RemoveFromParent();
	if (InitialWidget) {
		InitialWidget->AddToViewport(0);
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

void UOptionsMenu::ChangeResolutionSize(bool bNextOption) {
	CurrentResolutionIndex = bNextOption ?
		(CurrentResolutionIndex + 1) % Resolutions.Num() :
		(CurrentResolutionIndex - 1  + Resolutions.Num()) % Resolutions.Num();
	
	ResolutionToApply = Resolutions[CurrentResolutionIndex];
	UpdateResolutionText();
}

void UOptionsMenu::UpdateResolutionText() {
	if (ResolutionText) {
		const int XValue = ResolutionToApply.X;
		const int YValue = ResolutionToApply.Y;
		FText Value = FText::FromString(FString::Printf(TEXT("%d x %d"), XValue, YValue));
		ResolutionText->SetText(Value);
	}
}

void UOptionsMenu::ApplyNewSettings() {
	if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings()) {
		UserSettings->SetFullscreenMode(WindowModeToApply);
		UserSettings->SetScreenResolution(ResolutionToApply);
		UserSettings->ApplySettings(false);
	}
}

void UOptionsMenu::ChangeResolutionWrapperIncrease() {
	ChangeResolutionSize(true);
}

void UOptionsMenu::ChangeResolutionWrapperDecrease() {
	ChangeResolutionSize(false);
}

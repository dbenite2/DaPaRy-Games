// Property of DaPaRy Games


#include "CommonButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UCommonButton::NativeConstruct() {
	Super::NativeConstruct();

	World = GetWorld();

	if (Button) {
		Button->OnClicked.AddDynamic(this, &UCommonButton::OnClicked);
		Button->OnHovered.AddDynamic(this, &UCommonButton::OnHover);
		Button->OnUnhovered.AddDynamic(this, &UCommonButton::OnUnHover);
	}

	if (ButtonText) {
		ButtonText->SetText(ButtonLabel);
	}
}

void UCommonButton::OnClicked() {
	if (!LevelToLoadReference.IsNull()) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController) {
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoadReference);
	}

	if (bProgramQuit) {
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
	}

	if (bResumeGame) {
		//
	}

	if (bEmmitEvent) {
		OnButtonClicked.Broadcast();
	}
}

void UCommonButton::OnHover() {
	ButtonText->SetColorAndOpacity(FSlateColor(HoveredTextColor));
}

void UCommonButton::OnUnHover() {
	ButtonText->SetColorAndOpacity(FSlateColor(DefaultTextColor));
}


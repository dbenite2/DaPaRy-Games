// Property of DaPaRy Games

#include "SailorController.h"

#include "DialogueWidget.h"
#include "EnhancedInputSubsystems.h"
#include "PauseMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void ASailorController::BeginPlay() {
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
	
	if (!PauseMenuTemplate) return;
	PauseMenuWidget = CreateWidget<UPauseMenu>(this, PauseMenuTemplate);
	if (PauseMenuWidget) {
		PauseMenuWidget->AddToViewport(1);
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASailorController::ShowPauseMenu() {
	if (!PauseMenuWidget) return;
	PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}

void ASailorController::UnPauseGame() {
	bShowMouseCursor = false;
	PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	SetInputMode(FInputModeGameOnly());
}

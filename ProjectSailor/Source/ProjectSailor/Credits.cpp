// Property of DaPaRy Games


#include "Credits.h"

#include "CommonButton.h"
#include "Kismet/GameplayStatics.h"

void UCredits::NativeConstruct()
{
	Super::NativeConstruct();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController) {
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}

	if (Exit_Button)
	{
		Exit_Button->OnButtonClicked.AddUniqueDynamic(this, &UCredits::GoToMainMenu);
	}
}

void UCredits::GoToMainMenu()
{
	if (!LevelToLoadReference.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoadReference);
	}
}

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsMenu.generated.h"


class UButton;
class UCommonButton;
class UTextBlock;
class UImage;

/**
 * UControlsMenu is a user interface component derived from UUserWidget, designed specifically for the Project Sailor game.
 * It functions as the UI for the controls menu, providing a structured and interactive way for players to navigate back to the initial menu or other parts of the UI.
 */

UCLASS()
class PROJECTSAILOR_API UControlsMenu : public UUserWidget {
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* MenuBackground{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* ImageTitle{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* BackButton{nullptr};

	UFUNCTION()
	void SwitchWidget();
	
public:

	UPROPERTY(EditDefaultsOnly, Category="UI")
	UUserWidget* InitialWidget{nullptr};
};
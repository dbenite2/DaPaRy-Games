// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UImage;
class UTextBlock;
class UCommonButton;
/**
 * 
 */
UCLASS()
class PROJECTSAILOR_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* Title{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* MenuBackground{nullptr};
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* NewGameButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* OptionsButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* QuitButton{nullptr};
};

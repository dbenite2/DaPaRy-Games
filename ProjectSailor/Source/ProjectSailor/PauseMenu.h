// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UOptionsMenu;
class UVerticalBox;
class UCommonButton;

UCLASS()
class PROJECTSAILOR_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UCommonButton* ContinueButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UCommonButton* OptionsButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UCommonButton* MainMenuButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category = "Pause menu options")
	UCommonButton* QuitButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UVerticalBox* ButtonContainer{nullptr};

	UFUNCTION(BlueprintCallable)
	void SwitchWidget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> OptionsWidget{nullptr};

	UPROPERTY()
	UOptionsMenu* ExternalWidget{nullptr};
};

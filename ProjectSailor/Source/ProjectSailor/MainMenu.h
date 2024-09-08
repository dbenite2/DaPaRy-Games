// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UOptionsMenu;
class UControlsMenu;
class UImage;
class UTextBlock;
class UCommonButton;

/**
 * User interface widget designed to be the entry point of interaction for players when they start the game.
 * It provides navigation options such as starting a new game, accessing options, controls setup, and quitting the game.
 */

UCLASS()
class PROJECTSAILOR_API UMainMenu : public UUserWidget {
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* Title{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* ImageTitle{nullptr};
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* MenuBackground{nullptr};
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* NewGameButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* OptionsButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* ControlsButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* QuitButton{nullptr};

	UFUNCTION(BlueprintCallable)
	void RemoveWidget();

	UFUNCTION(BlueprintCallable)
	void RemoveWidget2();

	UPROPERTY()
	UOptionsMenu* ExternalWidgetOptionsMenu{nullptr};
	
	UPROPERTY()
	UControlsMenu* ExternalWidgetControlsMenu{nullptr};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> OptionsWidget{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ControlsWidget{nullptr};
};

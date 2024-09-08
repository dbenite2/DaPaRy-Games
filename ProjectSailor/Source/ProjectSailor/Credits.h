// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Credits.generated.h"


class UImage;
class UTextBlock;
class UCommonButton;
/**
 * The UCredits class represents the credits menu in Project Sailor, allowing players to view credits and return to the main menu.
 */
UCLASS()
class PROJECTSAILOR_API UCredits : public UUserWidget {
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TextCredits{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TextButtonExit {nullptr};
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* Exit_Button {nullptr};

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> LevelToLoadReference{nullptr};
	
	UFUNCTION(BlueprintCallable)
	void GoToMainMenu();
	
};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Credits.generated.h"


class UImage;
class UTextBlock;
class UCommonButton;
/**
 * 
 */
UCLASS()
class PROJECTSAILOR_API UCredits : public UUserWidget
{
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

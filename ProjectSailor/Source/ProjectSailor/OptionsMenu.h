// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"

class UButton;
class UCommonButton;
class UTextBlock;
class UImage;
class UHorizontalBox;
class UVerticalBox;

UCLASS()
class PROJECTSAILOR_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* MenuBackground{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* MenuTitle{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UVerticalBox* OptionsContainer{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UHorizontalBox* WindowsOptionsContainer{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UHorizontalBox* ResolutionOptionsContainer{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UHorizontalBox* SFXSliderContainer{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* IncreaseWindowButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* DecreaseWindowButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* WindowText{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* IncreaseResolutionButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* DecreaseResolutionButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* ResolutionText{nullptr};
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* ApplyButton{nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCommonButton* BackButton{nullptr};

	UFUNCTION()
	void SwitchWidget();

	UFUNCTION()
	void ChangeWindowMode();

	UFUNCTION()
	void UpdateWindowModeText();

	UFUNCTION()
	void ChangeResolutionSize(bool bNextOption);

	UFUNCTION()
	void UpdateResolutionText();

	UFUNCTION()
	void ApplyNewSettings();

	UFUNCTION()
	void ChangeResolutionWrapperIncrease();

	UFUNCTION()
	void ChangeResolutionWrapperDecrease();

	EWindowMode::Type WindowModeToApply;
	FIntPoint ResolutionToApply;
	TArray<FIntPoint> Resolutions;
	int32 CurrentResolutionIndex;

public:

	UPROPERTY(EditDefaultsOnly, Category="UI")
	UUserWidget* InitialWidget{nullptr};
};

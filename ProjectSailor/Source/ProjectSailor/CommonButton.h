// Property of DaPaRy Games
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommonButton.generated.h"

class UTextBlock;
class UButton;
class AMyAudioSubsystemActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class PROJECTSAILOR_API UCommonButton : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UWorld* World;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button{nullptr};

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText{nullptr};

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnButtonClicked OnButtonClicked;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClicked();

	UFUNCTION()
	void OnHover();

	UFUNCTION()
	void OnUnHover();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	TSoftObjectPtr<UWorld> LevelToLoadReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	bool bProgramQuit{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	bool bResumeGame{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level System")
	bool bEmmitEvent{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button Text")
	FText ButtonLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button Text")
	FLinearColor DefaultTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button Text")
	FLinearColor HoveredTextColor;
};

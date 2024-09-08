// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DialogueWidget.generated.h"

class UImage;
class UTextBlock;
class UCommonButton;

/**
 * UDialogueWidget is a UserWidget subclass designed to display dialogue text in a UI component within the game.
 * It is primarily used to show NPC dialogues to the player.
 */
UCLASS()
class PROJECTSAILOR_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* DialogueImage {nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))

	UTextBlock* TextDialogue {nullptr};

public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void UpdateText(const FText& NewText);

protected:
	virtual void NativeConstruct() override;

};

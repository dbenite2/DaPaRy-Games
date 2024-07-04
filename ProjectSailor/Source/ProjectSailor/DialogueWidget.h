// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DialogueWidget.generated.h"
/**
 * 
 */

class UImage;
class UTextBlock;
class UCommonButton;
UCLASS()
class PROJECTSAILOR_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UImage* DialogueImage {nullptr};

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))

	UTextBlock* TextDialogue {nullptr};

public:
	// Método para actualizar el texto del widget
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void UpdateText(const FText& NewText);

protected:
	virtual void NativeConstruct() override;

};

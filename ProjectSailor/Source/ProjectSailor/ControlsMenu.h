// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsMenu.generated.h"

#pragma once

class UButton;
class UCommonButton;
class UTextBlock;
class UImage;

UCLASS()
class PROJECTSAILOR_API UControlsMenu : public UUserWidget
{
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
// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SailorController.generated.h"

class UDialogueWidget;
class UInputMappingContext;
class UPauseMenu;

UCLASS()
class PROJECTSAILOR_API ASailorController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	bool bShowPauseMenu{false};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPauseMenu> PauseMenuTemplate{nullptr};

	virtual void BeginPlay() override;

public:
	
	UPROPERTY()
	UPauseMenu* PauseMenuWidget{nullptr};

	UPROPERTY()
	UDialogueWidget* IntroLevelWidget{nullptr};

	UFUNCTION()
	void UnPauseGame();
	
	UFUNCTION()
	void ShowPauseMenu();
};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "DialogDataAsset.h"
#include "DialogueWidget.h"
#include "Components/SphereComponent.h"
#include "ProjectSailorCharacter.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "GhostNPC.generated.h"
class AProjectSailorCharacter;
class UDialogDataAsset;
struct FLevelStatus;

/**
 * AGhostNPC represents a non-player character (NPC) designed to engage in dialogue with the player.
 * This actor utilizes a trigger zone to initiate interactions and displays dialogue through a UI widget.
 */

UCLASS()
class PROJECTSAILOR_API AGhostNPC : public AActor {
	GENERATED_BODY()
	
public:	
	AGhostNPC();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* TriggerZone;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

private:
	UPROPERTY()
	UDialogueWidget* DialogueWidget;
	
	int32 CurrentTextIndex;

	UFUNCTION()
	void SetWidget(bool set);

	UFUNCTION()
	void SetCurrentDialogSet(FLevelStatus PlayerStatus);

	UFUNCTION()
	void SetUpEventSubscription(AProjectSailorCharacter* Player);
public:	
	UFUNCTION()
	void ChangeToNextText();
	

	UPROPERTY(EditAnywhere)
	TArray<FText> CurrentDialogSet;

	UPROPERTY(EditAnywhere)
	UDialogDataAsset* Dialogs{nullptr};

};

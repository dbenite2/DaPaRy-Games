// Property of DaPaRy Games

#pragma once


#include "CoreMinimal.h"
#include "DialogueWidget.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "DialogueNPCCharacter.generated.h"
class AProjectSailorCharacter;
class UDialogDataAsset;
class AMyAudioSubsystemActor;
struct FLevelStatus;

/**
 * ADialogueNPCCharacter represents an NPC (Non-Player Character) that players can interact with to engage in dialogues.
 * This class manages the triggering and display of dialogue widgets based on the player's proximity and interaction.
 */

UCLASS()
class PROJECTSAILOR_API ADialogueNPCCharacter : public ACharacter {
	GENERATED_BODY()

public:
	ADialogueNPCCharacter();
	
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
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Audio")
	TArray<FText> RandomSoundDialogue;
	
private:
	UPROPERTY()
	UDialogueWidget* DialogueWidget;
	
	int32 CurrentTextIndex;
	// States to track if certain dialogues have been read.
	bool State1Read{false};
	bool State2Read{false};
	bool State3Read{false};
	int32 CurrentReadState{1}; // Tracks the current state of the dialogue interacti

	// The current set of dialogues available to this NPC.
	UPROPERTY()
	TArray<FText> CurrentDialogSet;

	UPROPERTY(EditAnywhere)
	bool bBlockMovementUntilFinished{false};

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementRef{nullptr};

	UFUNCTION()
	void SetWidget(bool Set);

	UFUNCTION()
	void SetCurrentDialogSet(FLevelStatus PlayerStatus);

	UFUNCTION()
	void SetUpEventSubscription(AProjectSailorCharacter* Player);

	UFUNCTION()
	void PlayRandomSound();
	
public:
	UFUNCTION()
	void ChangeToNextText();
	
	UPROPERTY(EditAnywhere)
	UDialogDataAsset* Dialogs{nullptr};
};

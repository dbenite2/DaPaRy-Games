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

UCLASS()
class PROJECTSAILOR_API ADialogueNPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADialogueNPCCharacter();

	// Trigger zone component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* TriggerZone;

	// Function to handle overlap events
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);


	// Widget to display when overlapping
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Audio")
	TArray<FText> RandomSoundDialogue;
private:
	UPROPERTY()
	UDialogueWidget* DialogueWidget;
	int32 CurrentTextIndex;

	UFUNCTION()
	void SetWidget(bool set);

	UPROPERTY()
	TArray<FText> CurrentDialogSet;

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

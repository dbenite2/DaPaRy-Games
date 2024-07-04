// Property of DaPaRy Games

#pragma once


#include "CoreMinimal.h"
#include "DialogueWidget.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "DialogueNPCCharacter.generated.h"
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
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

private:
	UDialogueWidget* DialogueWidget;

public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

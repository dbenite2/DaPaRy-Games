// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "DialogueWidget.h"
#include "GameFramework/Actor.h"
#include "GhostNPC.generated.h"

UCLASS()
class PROJECTSAILOR_API AGhostNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
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
public:	
	UFUNCTION()
	void ChangeToNextText();
	

	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueTexts;

};

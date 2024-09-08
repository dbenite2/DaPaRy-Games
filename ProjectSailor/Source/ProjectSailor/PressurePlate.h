// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class USphereComponent;
class UMovableStaticMeshComponent;
class AMyAudioSubsystemActor;

/**
 * A pressure plate actor that triggers interactions when objects or characters overlap with it. 
 * It can be used to activate or deactivate various gameplay elements based on the overlap state.
 */

UCLASS()
class PROJECTSAILOR_API APressurePlate : public AActor {
	GENERATED_BODY()

	void Interact(bool bIsInteracting);

	bool bIsTriggered{false};
	
public:	
	APressurePlate();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Trigger")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Trigger")
	UMovableStaticMeshComponent* MovableMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Trigger")
	USphereComponent* OverlapComponent{nullptr};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	bool bIsDisabled{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	bool bResetTrigger{false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger")
	TArray<FName> TargetTags;


protected:
	virtual void BeginPlay() override;
	
};

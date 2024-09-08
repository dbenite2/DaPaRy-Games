// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "InteractablePressInterface.h"
#include "GameFramework/Actor.h"
#include "BeachDoor.generated.h"

enum ParticleSystemLODMethod : int;
class UBoxComponent;
class AMyAudioSubsystemActor;

/**
 * ABeachDoor is an interactive actor class used to handle the behavior of doors in the game,
 * including opening and closing animations, sound effects, and particle effects triggered by player interactions.
 */
UCLASS()
class PROJECTSAILOR_API ABeachDoor : public AActor, public IInteractablePressInterface {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent{nullptr};

	UPROPERTY(EditAnywhere)
	USceneComponent* LeftPivot{nullptr};

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RightPivot{nullptr};

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftDoor{nullptr};

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* LeftDoorCollider{nullptr};

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightDoor{nullptr};

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* RightDoorCollider{nullptr};

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* DoorTrigger{nullptr};

	UPROPERTY(EditDefaultsOnly)
	FRuntimeFloatCurve AnimationCurve;

	UPROPERTY(EditAnywhere)
	bool bActivateDoors{false};

	UPROPERTY(EditDefaultsOnly)
	float AnimationDuration{3.f};

	UPROPERTY(EditDefaultsOnly)
	int LeftDoorRotationGoal{-90};

	UPROPERTY(EditDefaultsOnly)
	int RightDoorRotationGoal{270};

	UPROPERTY(VisibleAnywhere, Category="Effects")
	UParticleSystemComponent* RightDoorParticle{nullptr};
	
	UPROPERTY(VisibleAnywhere, Category="Effects")
	UParticleSystemComponent* LeftDoorParticle{nullptr};
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* ParticleSystem{nullptr};

	void ActivateDoors();
	
	float TimeCounter{0.f};
	

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	ABeachDoor();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
	FName InteractTag;
	
	virtual void Tick(float DeltaTime) override;

	virtual FName GetInteractTag_Implementation() override;
	virtual void Interact_Implementation(bool bInteractive) override;

protected:
	virtual void BeginPlay() override;
	
	
};

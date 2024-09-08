// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MushroomActor.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class AMyAudioSubsystemActor;

/**
 * Mushroom Actor Appears When MushroomButtonActor is hit, and move down until SpawnLocation.
 * Then wait 16 seconds and disappear
 **/

UCLASS()
class PROJECTSAILOR_API AMushroomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMushroomActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Components")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	float FallingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	float TargetZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	float timerHold = 14.0f;

	FTimerHandle DespawnTimerHandle;

	UFUNCTION()
	void Despawn();

	UFUNCTION()
	void SetVisibilityActor();

	UPROPERTY(EditAnywhere, Category = "Blueprints")
	AActor* BP_InitialPosition;

	UPROPERTY(EditAnywhere)
	bool IsHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CAtegory = "ParticleSystem")
	UNiagaraComponent* pSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CAtegory = "ParticleSystem")
	UNiagaraComponent* endParticleSystem;

	
};

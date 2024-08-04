// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MushroomActor.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class PROJECTSAILOR_API AMushroomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMushroomActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Components")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	float FallingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Components")
	float TargetZ;

	UFUNCTION()
	void Despawn();

	UFUNCTION()
	void SetVisibilityActor();

	UPROPERTY(EditAnywhere, Category = "Blueprints")
	AActor* BP_InitialPosition;

	UPROPERTY(EditAnywhere)
	bool IsHit = false;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "ParticleSystem")
	// UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CAtegory = "ParticleSystem")
	UNiagaraComponent* pSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CAtegory = "ParticleSystem")
	UNiagaraComponent* endParticleSystem;

	
};

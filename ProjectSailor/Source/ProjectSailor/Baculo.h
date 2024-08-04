// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Baculo.generated.h"

class AProjectSailorCharacter;
class UNiagaraComponent;
class UNiagaraSystem;
class UNiagaraScript;

UCLASS()
class PROJECTSAILOR_API ABaculo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaculo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * baculo  = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Decorations")
	USkeletalMeshComponent* Octopus{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	UAnimMontage* GrabAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	UNiagaraSystem* NiagaraSystem{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraComponent* ConnectionParticleComponent{nullptr};

	UPROPERTY()
	AProjectSailorCharacter* Player{nullptr};

	UFUNCTION()
	void PlayAnimMontage();

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};

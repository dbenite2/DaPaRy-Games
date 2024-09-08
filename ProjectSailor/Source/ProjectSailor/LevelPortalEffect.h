// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPortalEffect.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class UBoxComponent;

/**
 * Class that handles the visual effects of a portal or transition point within the game world.
 * This class uses Niagara systems to produce visual effects.
 */
UCLASS()
class PROJECTSAILOR_API ALevelPortalEffect : public AActor {
	GENERATED_BODY()
	
public:
	ALevelPortalEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraComponent* ExternalNiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraComponent* InternalNiagaraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* NiagaraSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	UBoxComponent* TriggerBoxComponent;
	
	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							 bool bFromSweep, const FHitResult& SweepResult);

};

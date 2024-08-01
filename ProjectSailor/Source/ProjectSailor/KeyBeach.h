// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "CableComponent.h"
#include "Components/SphereComponent.h" // Include the SphereComponent header
#include "GameFramework/Actor.h"
#include "KeyBeach.generated.h"

class USailorInstance;
class AMyAudioSubsystemActor;

UCLASS()
class PROJECTSAILOR_API AKeyBeach : public AActor,  public IInteractionInterface
{
	GENERATED_BODY()
    
public:    
	AKeyBeach();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollider; 

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* MaterialInterface{nullptr};

	UPROPERTY(EditAnywhere, Category = "Materials")
	FName BrightnessParameterName = "glow";
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category = "Blueprints")
	AActor* BP_Rope{nullptr};

	UPROPERTY()
	bool hasPhysics{false};

public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMesh{nullptr};
	
	void ActivateKeyPhysics();

	virtual void Interact_Implementation() override;

private:
	FTimerHandle TimerHandle_Blink;

	UFUNCTION()
	void BlinkEffect();

	UFUNCTION()
	void ModifyCableComponent();

	UPROPERTY()
	USailorInstance* GameManager{nullptr};
};
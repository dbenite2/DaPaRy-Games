// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"

#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "KeyBeach.generated.h"

UCLASS()
class PROJECTSAILOR_API AKeyBeach : public AActor,  public IInteractionInterface
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	AKeyBeach();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* MaterialInterface;

	UPROPERTY(EditAnywhere, Category = "Materials")
	FName BrightnessParameterName = "glow";

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMesh;

	// Function to initialize the key position and physics
	void ActivateKeyPhysics();

	virtual void Interact_Implementation() override;

private:
	FTimerHandle TimerHandle_Blink;

	UFUNCTION()
	void BlinkEffect();
};
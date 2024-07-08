// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"

#include "InteractionInterface.h"
#include "Components/SphereComponent.h" // Include the SphereComponent header
#include "GameFramework/Actor.h"
#include "KeyBeach.generated.h"

UCLASS()
class PROJECTSAILOR_API AKeyBeach : public AActor,  public IInteractionInterface
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	AKeyBeach();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollider; // Declare the SphereComponent

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* MaterialInterface;

	UPROPERTY(EditAnywhere, Category = "Materials")
	FName BrightnessParameterName = "glow";

	// Overlap event function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
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
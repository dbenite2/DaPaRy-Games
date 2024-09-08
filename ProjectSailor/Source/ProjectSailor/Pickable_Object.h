// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "GameFramework/Actor.h"
#include "Pickable_Object.generated.h"

/**
 * Represents a pickable object in the game. This object can be picked up and moved around by the player.
 */
UCLASS()
class PROJECTSAILOR_API APickable_Object : public AActor {
	GENERATED_BODY()

	FVector InitialLocation;
	bool bIsReset;
	
public:	
	APickable_Object();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void PickedObject();

	UFUNCTION()
	void DropObject();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent * mesh  = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	bool bNotActivatePlatform = false;

	UFUNCTION()
	void ResetObjectLocation(FVector& Location);
	
};

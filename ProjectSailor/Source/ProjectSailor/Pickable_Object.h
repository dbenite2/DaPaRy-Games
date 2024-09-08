// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "GameFramework/Actor.h"
#include "Pickable_Object.generated.h"

UCLASS()
class PROJECTSAILOR_API APickable_Object : public AActor {
	GENERATED_BODY()

	FVector InitialLocation;
	bool bIsReset;
	
public:	
	// Sets default values for this actor's properties
	APickable_Object();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// virtual void TakeDamage() override;
	
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

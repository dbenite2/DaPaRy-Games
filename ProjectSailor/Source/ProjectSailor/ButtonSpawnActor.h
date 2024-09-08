// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonSpawnActor.generated.h"

class APickable_Object;
class UBoxComponent;
class UPointLightComponent;
class AMyAudioSubsystemActor;

/**
 * AButtonSpawnActor is a customizable actor class, designed to manage the spawning
 * and resetting of other actors within the game environment, particularly those that are interactable or pickable.
 * This actor can act as both a spawn point and a reset button, allowing dynamic interaction scenarios in the game.
 */

UCLASS()
class PROJECTSAILOR_API AButtonSpawnActor : public AActor {
	GENERATED_BODY()
	
public:	
	AButtonSpawnActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnActor();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	USceneComponent* DefaultRoot{nullptr};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	UStaticMeshComponent* CircleMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	UPointLightComponent* PointLight{nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Blueprints")
	AActor* BP_ActorSpawnable{nullptr};
	
	UPROPERTY(EditAnywhere, Category = "Reset")
	TMap<APickable_Object*, FVector> ActorsWithInitialLocation;

	UPROPERTY(EditAnywhere, Category = "Reset")
	bool bResetButton{false};

};

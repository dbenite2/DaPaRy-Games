// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "MushroomActor.h"
#include "GameFramework/Actor.h"
#include "MushroomButtonActor.generated.h"


class UBoxComponent;
class UPointLightComponent;

UCLASS()
class PROJECTSAILOR_API AMushroomButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMushroomButtonActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void SpawnMushroom();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	UStaticMeshComponent* CircleMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Blueprints")
	AActor* BP_InitialPosition;
};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectTileInteraction.generated.h"

/**
 * Handles the interactive tile objects within the ProjectSailor game.
 * This class manages the animation of tiles dropping from an initial to a target location based on specified parameters.
 */

UCLASS()
class PROJECTSAILOR_API AObjectTileInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectTileInteraction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	FVector InitialLocation;
	FVector TargetLocation;
	bool droopDone;
	float ElapsedTime;
    
	UPROPERTY(EditAnywhere, Category = "Drop")
	float DropSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Drop")
	float DropDistance = 150.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

};

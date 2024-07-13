// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectTileInteraction.generated.h"

UCLASS()
class PROJECTSAILOR_API AObjectTileInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectTileInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
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

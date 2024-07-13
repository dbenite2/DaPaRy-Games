// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "ObjectTileInteraction.h"
#include "Pickable_Object.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TileInteraction.generated.h"

UCLASS()
class PROJECTSAILOR_API ATileInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileInteraction();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	APickable_Object* pickableObject;

	FVector InitialLocation;
	FVector TargetLocation;
	bool bIsDropping;
	float ElapsedTime;
    
	UPROPERTY(EditAnywhere, Category = "Drop")
	float DropSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Drop")
	float DropDistance = 10.0f;

	UPROPERTY(EditAnywhere)
	AObjectTileInteraction* objectTileInteraction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void UpdateDropping();
};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "MushroomActor.h"
#include "GameFramework/Actor.h"
#include "GenericGeometricPuzzlePiece.generated.h"

class UBoxComponent;
class UPointLightComponent;
class UParticleSystemComponent;
class AMyAudioSubsystemActor;
UCLASS()
class PROJECTSAILOR_API AGenericGeometricPuzzlePiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenericGeometricPuzzlePiece();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CubeMesh; // Nuevo componente para el cubo

	// Public property for the figure step
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Figure")
	FString NameFigureStep;

	// Public property for the figure step
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Figure")
	bool isCorrect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystemComponent* incorrectParticleSystem;

	UPROPERTY(EditAnywhere,  Category = "Spawn")
	bool isSpawnLevelPlatform;

	UPROPERTY(EditAnywhere,  Category = "Mushroom")
	TArray<AMushroomActor*> MushroomActors;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* PointLight;

	// Reference to the Blueprint
	UPROPERTY(EditAnywhere, Category = "Blueprints")
	AActor* BP_InitialPosition;

	


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

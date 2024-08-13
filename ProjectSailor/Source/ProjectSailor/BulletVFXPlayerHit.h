// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletVFXPlayerHit.generated.h"

class UParticleSystemComponent;
class UStaticMeshComponent;
UCLASS()
class PROJECTSAILOR_API ABulletVFXPlayerHit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletVFXPlayerHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleSystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	float Velocity;
	float Lifetime;

};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletVFXPlayerHit.generated.h"

class UParticleSystemComponent;
class UStaticMeshComponent;

/**
 * ABulletVFXPlayerHit represents a bullet visual effects actor in the game,
 * designed to simulate a bullet hit using particle effects and to manage the bullet's lifecycle.
 */
UCLASS()
class PROJECTSAILOR_API ABulletVFXPlayerHit : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletVFXPlayerHit();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector InitDirection;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FRotator CameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UParticleSystem* HitParticleSystemWhenDestroys {nullptr};

public:	
	virtual void Tick(float DeltaTime) override;
	float Lifetime;

private:

	float Velocity;
	
};

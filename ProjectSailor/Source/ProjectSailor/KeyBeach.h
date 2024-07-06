// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "GameFramework/Actor.h"
#include "KeyBeach.generated.h"

UCLASS()
class PROJECTSAILOR_API AKeyBeach : public AActor, public IIDamageable
{
	GENERATED_BODY()
    
public:    
	// Sets default values for this actor's properties
	AKeyBeach();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMesh;

	// Function to initialize the key position and physics
	void ActivateKeyPhysics();
};
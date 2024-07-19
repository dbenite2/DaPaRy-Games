// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "InteractablePressInterface.h"
#include "GameFramework/Actor.h"
#include "MovingStaticMeshActor.generated.h"

class UMovableStaticMeshComponent;

UCLASS()
class PROJECTSAILOR_API AMovingStaticMeshActor : public AActor, public IInteractablePressInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingStaticMeshActor();
	
	virtual FName GetInteractTag_Implementation() override;
	virtual void Interact_Implementation(bool bInteractive) override;

	bool IsDisabled() const {return bIsDisabled;}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Moving")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Moving")
	UMovableStaticMeshComponent* MovableMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	FName InteractTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	bool bIsDisabled{false};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

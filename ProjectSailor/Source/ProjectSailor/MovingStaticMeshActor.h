// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "InteractablePressInterface.h"
#include "GameFramework/Actor.h"
#include "MovingStaticMeshActor.generated.h"

/**
 * Implements IInteractablePressInterface to provide an interactable actor
 * with a static mesh base and a movable component, typically used for objects in the game that can be interacted with
 * to trigger movement (e.g., doors, platforms, levers).
 */

class UMovableStaticMeshComponent;

UCLASS()
class PROJECTSAILOR_API AMovingStaticMeshActor : public AActor, public IInteractablePressInterface
{
	GENERATED_BODY()
	
public:	
	AMovingStaticMeshActor();
	
	virtual FName GetInteractTag_Implementation() override;
	virtual void Interact_Implementation(bool bInteractive) override;

	bool IsDisabled() const {return bIsDisabled;}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Moving")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category = "Moving")
	UMovableStaticMeshComponent* MovableMesh{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
	FName InteractTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	bool bIsDisabled{false};

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};

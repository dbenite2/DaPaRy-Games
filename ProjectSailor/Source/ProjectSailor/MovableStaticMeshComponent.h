// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "MovableStaticMeshComponent.generated.h"

UENUM(BlueprintType)
enum class ERotationAxis : uint8 {
	Yaw, Pitch, Roll
};

UENUM(BlueprintType)
enum class ELocationAxis : uint8 {
	X, Y, Z
};

UENUM(BlueprintType)
enum class EMovementType : uint8 {
	Location, Rotation
};

/**
 * 
 */
UCLASS()
class PROJECTSAILOR_API UMovableStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UMovableStaticMeshComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UCurveFloat* MoveCurve{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	EMovementType MovementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta=(EditCondition="MovementType == EMovementType::Rotation"))
	ERotationAxis RotateAxis;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta=(EditCondition="MovementType == EMovementType::Location"))
	ELocationAxis LocationAxis;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsReversed{false};

	UFUNCTION(BlueprintCallable)
	void Move(bool bTriggered);

	UFUNCTION()
	void OnMove();

	UFUNCTION()
	void OnMoveFinished();
	
	bool IsMoving() const {return  bIsMoving;}
	bool IsTriggered() const {return bIsTriggered;}

private:
	bool bIsMoving{false};
	FTimeline MoveTimeline;

	bool bIsTriggered;
	float PreviousTimeLineValue;

	void UpdateRotation(float CurveValue);
	void UpdateLocation(float CurveValue);
	
};

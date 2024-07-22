// Property of DaPaRy Games


#include "MovableStaticMeshComponent.h"

UMovableStaticMeshComponent::UMovableStaticMeshComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovableStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsMoving) {
		MoveTimeline.TickTimeline(DeltaTime);
	}
}

void UMovableStaticMeshComponent::BeginPlay() {
	Super::BeginPlay();

	if (MoveCurve) {
		FOnTimelineFloat TimeLineCallback;
		FOnTimelineEventStatic TimeLineFinishCallback;

		TimeLineCallback.BindUFunction(this, FName("OnMove"));
		TimeLineFinishCallback.BindUFunction(this, FName("OnMoveFinished"));

		MoveTimeline.AddInterpFloat(MoveCurve, TimeLineCallback);
		MoveTimeline.SetTimelineFinishedFunc(TimeLineFinishCallback);
	}
}

void UMovableStaticMeshComponent::Move(bool bTriggered) {
	bIsTriggered = bTriggered;
	if (bTriggered) {
		MoveTimeline.PlayFromStart();
	} else {
		MoveTimeline.Reverse();
	}
	bIsMoving = true;
}

void UMovableStaticMeshComponent::OnMove() {
	const float PlayBackPosition = MoveTimeline.GetPlaybackPosition();
	float CurveValue = MoveCurve->GetFloatValue(PlayBackPosition);

	if (bIsReversed) {
		CurveValue = -CurveValue;
	}

	if (MovementType == EMovementType::Location) {
		UpdateLocation(CurveValue);
	} else if (MovementType == EMovementType::Rotation) {
		UpdateRotation(CurveValue);
	}
}

void UMovableStaticMeshComponent::OnMoveFinished() {
	bIsMoving = false;
}

void UMovableStaticMeshComponent::UpdateRotation(float CurveValue) {
	FRotator NewRotation = GetRelativeRotation();
	switch (RotateAxis) {
	case ERotationAxis::Pitch:
		NewRotation = FRotator(CurveValue, 0.f, 0.f);
		break;
	case ERotationAxis::Roll:
		NewRotation = FRotator(0.f, 0.f, CurveValue);
		break;
	case ERotationAxis::Yaw:
		NewRotation = FRotator(0.f, CurveValue, 0.f);
		break;
	default:
		break;
	}
	SetRelativeRotation(NewRotation);
}

void UMovableStaticMeshComponent::UpdateLocation(float CurveValue) {
	FVector NewLocation = GetRelativeLocation();
	switch (LocationAxis) {
	case ELocationAxis::X:
		NewLocation.X += CurveValue - PreviousTimeLineValue;
		break;
	case ELocationAxis::Y:
		NewLocation.Y += CurveValue - PreviousTimeLineValue;
		break;
	case ELocationAxis::Z:
		NewLocation.Z += CurveValue - PreviousTimeLineValue;
		break;
	default:
		break;
	}

	PreviousTimeLineValue = CurveValue;
	SetRelativeLocation(NewLocation);
}

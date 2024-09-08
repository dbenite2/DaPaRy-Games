// Property of DaPaRy Games


#include "DoorWayComponent.h"

UDoorWayComponent::UDoorWayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UDoorWayComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UDoorWayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
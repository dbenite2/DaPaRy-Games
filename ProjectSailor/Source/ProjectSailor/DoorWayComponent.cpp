// Property of DaPaRy Games


#include "DoorWayComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDoorWayComponent::UDoorWayComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorWayComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDoorWayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
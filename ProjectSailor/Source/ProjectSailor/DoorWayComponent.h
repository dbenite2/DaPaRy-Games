// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorWayComponent.generated.h"

// this class seems to be able to delete
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UDoorWayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorWayComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};

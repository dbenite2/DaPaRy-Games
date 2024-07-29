// Property of DaPaRy Games


#include "MyBlueprintSubsystemInitializer.h"

void UMyGameInstanceSubsystemInitializer::Initialize(FSubsystemCollectionBase& Collection)
{
	const UMyBlueprintSubsystemInitializer* BlueprintSubsystemInitializer = GetDefault<UMyBlueprintSubsystemInitializer>();

	//check if array is empty
	if(BlueprintSubsystemInitializer->GameInstanceSubsystems.IsEmpty())
	{
		return;
	}

	//initialize each subsystems of the array
	for(TSubclassOf<UGameInstanceSubsystem> Subsystem : BlueprintSubsystemInitializer->GameInstanceSubsystems)
	{
		Collection.InitializeDependency(Subsystem);
	}
}

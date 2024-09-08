// Property of DaPaRy Games


#include "MyBlueprintSubsystemInitializer.h"

void UMyGameInstanceSubsystemInitializer::Initialize(FSubsystemCollectionBase& Collection) {
	const UMyBlueprintSubsystemInitializer* BlueprintSubsystemInitializer = GetDefault<UMyBlueprintSubsystemInitializer>();
	
	if(BlueprintSubsystemInitializer->GameInstanceSubsystems.IsEmpty()) {
		return;
	}
	
	for(TSubclassOf<UGameInstanceSubsystem> Subsystem : BlueprintSubsystemInitializer->GameInstanceSubsystems) {
		if (Subsystem) Collection.InitializeDependency(Subsystem);
	}
}

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MyBlueprintSubsystemInitializer.generated.h"

/**
 * Class derived from UDeveloperSettings, designed to allow the configuration
 * of GameInstanceSubsystems via the Unreal Editor's Project Settings. This setup facilitates the initialization of
 * specific subsystems that are critical for the game's operations, particularly those that need to be loaded with the
 * game instance.
 */

UCLASS(config = UE_GAME, DefaultConfig, meta = (DisplayName = "Blueprin Subsystems"))
class PROJECTSAILOR_API UMyBlueprintSubsystemInitializer : public UDeveloperSettings {
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Meta = (BlueprintBaseOnly))
	TArray<TSubclassOf<UGameInstanceSubsystem>> GameInstanceSubsystems;
	
};

UCLASS()
class PROJECTSAILOR_API UMyGameInstanceSubsystemInitializer : public UGameInstanceSubsystem {
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override final;
	
};

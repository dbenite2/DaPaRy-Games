// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MyBlueprintSubsystemInitializer.generated.h"

/**
 * 
 */
UCLASS(config = UE_GAME, DefaultConfig, meta = (DisplayName = "Blueprin Subsystems"))
class PROJECTSAILOR_API UMyBlueprintSubsystemInitializer : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Meta = (BlueprintBaseOnly))
	TArray<TSubclassOf<UGameInstanceSubsystem>> GameInstanceSubsystems;
	
};

UCLASS()
class PROJECTSAILOR_API UMyGameInstanceSubsystemInitializer : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override final;
	
};

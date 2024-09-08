#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "MyAudioSubsystem.generated.h"

/**
 * UMyAudioSubsystem is a game instance subsystem responsible for managing audio-related functionality
 * across the entire game. This class provides a structured way to handle audio initialization and cleanup at a global level.
 */
UCLASS(Blueprintable, Abstract)
class PROJECTSAILOR_API UMyAudioSubsystem : public UGameInstanceSubsystem {
	GENERATED_BODY()

protected:
	/**
	 * Initializes the subsystem. This function is called when the game instance initializes the subsystem.
	 * 
	 * @param Collection Reference to the subsystem collection this subsystem is a part of, which provides the context of the initialization.
	 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	/**
	 * Cleans up the subsystem. This function is called when the game instance shuts down and the subsystem is being destroyed.
	 * function to free resources, stop audio that may be playing, and perform general cleanup.
	 */
	virtual void Deinitialize() override;

};
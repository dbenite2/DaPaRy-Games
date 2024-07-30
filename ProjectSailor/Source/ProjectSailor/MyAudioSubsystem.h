#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "MyAudioSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class PROJECTSAILOR_API UMyAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

};
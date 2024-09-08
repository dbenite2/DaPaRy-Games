#include "MyAudioSubsystem.h"

#include "MyAudioSubsystemActor.h"
#include "Engine/World.h"
#include "Sound/SoundWave.h"


void UMyAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    Super::Initialize(Collection);
    
}

void UMyAudioSubsystem::Deinitialize() {
    
    Super::Deinitialize();
}

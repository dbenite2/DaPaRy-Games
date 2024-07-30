#include "MyAudioSubsystem.h"

#include "MyAudioSubsystemActor.h"
#include "Engine/World.h"
#include "Sound/SoundWave.h"




void UMyAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

  
    // //Create Actor MyAudioSubsystemActor initial
    // FActorSpawnParameters SpawnParams;
    // SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    // //actor
    // GetWorld()->SpawnActor<AMyAudioSubsystemActor>(AMyAudioSubsystemActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}

void UMyAudioSubsystem::Deinitialize()
{

    //destroy actor
    Super::Deinitialize();
}






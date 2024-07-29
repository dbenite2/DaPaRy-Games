// Property of DaPaRy Games


#include "MyAudioSubsystem.h"

#include "Kismet/GameplayStatics.h"

UMyAudioSubsystem::UMyAudioSubsystem()
{
	AudioComponent = nullptr;
}

void UMyAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// Crear el AudioComponent y asignar al Subsystem
	if (!AudioComponent)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			AudioComponent = NewObject<UAudioComponent>(World);
			if (AudioComponent)
			{
				AudioComponent->RegisterComponent(); // Necesario para que funcione
			}
			// Necesario para que funcione
		}
	}
}

void UMyAudioSubsystem::Deinitialize()
{
	if (AudioComponent)
	{
		if (AudioComponent->IsRegistered())
		{
			// AudioComponent->Stop();
			AudioComponent->UnregisterComponent();
		}
		AudioComponent = nullptr; // Limpiar el puntero después de usarlo
	}
	Super::Deinitialize();
}

void UMyAudioSubsystem::PlayMusic(const FString& MusicName)
{
	if (USoundWave** SoundWavePtr = MusicTracks.Find(MusicName))
	{
		if (USoundWave* SoundWave = *SoundWavePtr)
		{
			if (AudioComponent)
			{
				AudioComponent->SetSound(SoundWave);
				AudioComponent->Play();
			}
		}
	}
}

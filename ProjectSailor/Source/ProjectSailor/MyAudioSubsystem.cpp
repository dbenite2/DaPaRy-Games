// Property of DaPaRy Games


#include "MyAudioSubsystem.h"

#include "Kismet/GameplayStatics.h"

UMyAudioSubsystem::UMyAudioSubsystem()
{
	MusicComponent = nullptr;
	SFX1Component = nullptr;
}

void UMyAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// Crear el AudioComponent y asignar al Subsystem
	if (!MusicComponent)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			MusicComponent = NewObject<UAudioComponent>(World);
			if (MusicComponent)
			{
				MusicComponent->RegisterComponent(); // Necesario para que funcione
			}
			// Necesario para que funcione
		}
	}

	if (!SFX1Component)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			SFX1Component = NewObject<UAudioComponent>(World);
			if (SFX1Component)
			{
				SFX1Component->RegisterComponent(); // Necesario para que funcione
			}
			// Necesario para que funcione
		}
	}
}

void UMyAudioSubsystem::Deinitialize()
{
	if (MusicComponent)
	{
		if (MusicComponent->IsRegistered())
		{
			// AudioComponent->Stop();
			MusicComponent->UnregisterComponent();
		}
		MusicComponent = nullptr; // Limpiar el puntero después de usarlo
	}

	if (SFX1Component)
	{
		if (SFX1Component->IsRegistered())
		{
			// AudioComponent->Stop();
			SFX1Component->UnregisterComponent();
		}
		SFX1Component = nullptr; // Limpiar el puntero después de usarlo
	}
	Super::Deinitialize();
}

void UMyAudioSubsystem::PlayMusic(const FString& MusicName)
{
	if (USoundWave** SoundWavePtr = MusicTracks.Find(MusicName))
	{
		if (USoundWave* SoundWave = *SoundWavePtr)
		{
			if (MusicComponent)
			{
				MusicComponent->SetSound(SoundWave);
				MusicComponent->Play();
			}
		}
	}
}

void UMyAudioSubsystem::PlaySFX1(const FString& MusicName)
{
	if (USoundWave** SoundWavePtr = SFXTracks.Find(MusicName))
	{
		if (USoundWave* SoundWave = *SoundWavePtr)
		{
			if (SFX1Component)
			{
				SFX1Component->SetSound(SoundWave);
				SFX1Component->Play();
			}
		}
	}
}

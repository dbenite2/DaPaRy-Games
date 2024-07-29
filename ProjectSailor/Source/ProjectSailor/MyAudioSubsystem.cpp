// Property of DaPaRy Games


#include "MyAudioSubsystem.h"

#include "Kismet/GameplayStatics.h"

UMyAudioSubsystem::UMyAudioSubsystem()
{
	
}

void UMyAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
	
	// Inicialización del subsistema (ej: carga de pistas de música)
	
	PlayMusic("MainMenu");
}

void UMyAudioSubsystem::Deinitialize()
{
	
	Super::Deinitialize();
}

void UMyAudioSubsystem::PlayMusic(const FString& MusicName)
{
	if (USoundWave** SoundWavePtr = MusicTracks.Find(MusicName))
	{
		if (USoundWave* SoundWave = *SoundWavePtr)
		{
			// Obtener el contexto del mundo de manera segura
			UWorld* World = GetWorld();
			if (World)
			{
				// Reproducir música usando UGameplayStatics
				UGameplayStatics::PlaySound2D(World, SoundWave);
			}
		}
	}
}

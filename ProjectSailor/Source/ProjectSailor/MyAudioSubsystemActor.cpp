#include "MyAudioSubsystemActor.h"
#include "MyAudioSubsystem.h"
#include "Engine/World.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

AMyAudioSubsystemActor::AMyAudioSubsystemActor()
	: MusicComponent(nullptr)
	, SFX1Component(nullptr)
	, SFX2Component(nullptr)
	, SFX3Component(nullptr)
{
	// Constructor initialization if needed
	
}
void AMyAudioSubsystemActor::BeginPlay()
{
	Super::BeginPlay();
	InitializeAudioComponents();
}
void AMyAudioSubsystemActor::InitializeAudioComponents()
{
		MusicComponent = CreateAudioComponent(this);
		SFX1Component =  CreateAudioComponent(this);
		SFX2Component =  CreateAudioComponent(this);
	    SFX3Component =  CreateAudioComponent(this);
}
UAudioComponent* AMyAudioSubsystemActor::CreateAudioComponent(UObject* Outer)
{
	if (Outer)
	{
		UAudioComponent* AudioComp = NewObject<UAudioComponent>(Outer);
		if (AudioComp)
		{
			AudioComp->RegisterComponentWithWorld(GetWorld());
			return AudioComp;
		}
	}
	return nullptr;
}
void AMyAudioSubsystemActor::PlayMusic(const FString& MusicName)
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




void AMyAudioSubsystemActor::PlaySFX1(const FString& MusicName)
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
void AMyAudioSubsystemActor::PlaySFX2(const FString& MusicName)
{
	if (USoundWave** SoundWavePtr = SFXTracks.Find(MusicName))
	{
		if (USoundWave* SoundWave = *SoundWavePtr)
		{
			if (SFX2Component)
			{
				SFX2Component->SetSound(SoundWave);
				SFX2Component->Play();
			}
		}
	}
}
void AMyAudioSubsystemActor::PlaySFX3(const FString& MusicName)
{
	if (USoundWave** SoundWavePtr = SFXTracks.Find(MusicName))
	{
		if (USoundWave* SoundWave = *SoundWavePtr)
		{
			if (SFX3Component)
			{
				SFX3Component->SetSound(SoundWave);
				SFX3Component->Play();
			}
		}
	}
}
void AMyAudioSubsystemActor::StopMusic()
{
	if (MusicComponent && MusicComponent->IsPlaying())
	{
		MusicComponent->Stop();
	}
}
void AMyAudioSubsystemActor::StopSFX1()
{
	if (SFX1Component)
	{
		if(SFX1Component->IsPlaying())
		{
			SFX1Component->Stop();
		}
	}
}
void AMyAudioSubsystemActor::StopSFX2()
{
	if (SFX2Component && SFX2Component->IsPlaying())
	{
		SFX2Component->Stop();
	}
}

void AMyAudioSubsystemActor::StopSFX3()
{
	if (SFX3Component && SFX3Component->IsPlaying())
	{
		SFX3Component->Stop();
	}
}

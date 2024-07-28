// Property of DaPaRy Games


#include "AudioManager.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

UAudioManager::UAudioManager()
{
	// Create audio components for music and sound effects
	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));
	MusicAudioComponent->bAutoActivate = false;

	SoundEffectAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEffectAudioComponent"));
	SoundEffectAudioComponent->bAutoActivate = false;

	SoundEffectAudioComponent2 = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEffectAudioComponent2"));
	SoundEffectAudioComponent2->bAutoActivate = false;

	SoundEffectAudioComponent3 = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEffectAudioComponent3"));
	SoundEffectAudioComponent3->bAutoActivate = false;

	SoundEffectAudioComponent4 = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEffectAudioComponent4"));
	SoundEffectAudioComponent4->bAutoActivate = false;
}


void UAudioManager::PlayMusic(int32 SoundIndex) {
	if (MusicCues.IsValidIndex(SoundIndex)) {
		USoundCue* MusicCue = MusicCues[SoundIndex];
		if (MusicCue) {
			MusicAudioComponent->SetSound(MusicCue);
			MusicAudioComponent->Play();
		}
	}
}

void UAudioManager::PlayMusicByName(FString SoundName)
{
	int32 Index = MusicNames.IndexOfByKey(SoundName);
	if (MusicCues.IsValidIndex(Index))
	{
		PlayMusic(Index);
	}
}

void UAudioManager::StopMusic() {
	if (MusicAudioComponent->IsPlaying()) {
		MusicAudioComponent->Stop();
	}
}

void UAudioManager::PlaySoundEffect(int32 SoundIndex) {
	if (SoundEffectCues.IsValidIndex(SoundIndex))
	{
		USoundCue* SoundCue = SoundEffectCues[SoundIndex];
		if (SoundCue) {
			SoundEffectAudioComponent->SetSound(SoundCue);
			SoundEffectAudioComponent->Play();
		}
	}
}

void UAudioManager::PlaySoundEffectByName(FString SoundName) {
	int32 Index = SoundEffectNames.IndexOfByKey(SoundName);
	if (SoundEffectCues.IsValidIndex(Index)) {
		PlaySoundEffect(Index);
	}
}

void UAudioManager::PlaySoundEffect2(int32 SoundIndex)
{
	if (SoundEffectCues.IsValidIndex(SoundIndex))
	{
		USoundCue* SoundCue = SoundEffectCues[SoundIndex];
		if (SoundCue) {
			SoundEffectAudioComponent2->SetSound(SoundCue);
			SoundEffectAudioComponent2->Play();
		}
	}
}

void UAudioManager::PlaySoundEffectByName2(FString SoundName)
{
	int32 Index = SoundEffectNames.IndexOfByKey(SoundName);
	if (SoundEffectCues.IsValidIndex(Index))
	{
		PlaySoundEffect2(Index);
	}
}

void UAudioManager::PlaySoundEffect3(int32 SoundIndex)
{
	if (SoundEffectCues.IsValidIndex(SoundIndex))
	{
		USoundCue* SoundCue = SoundEffectCues[SoundIndex];
		if (SoundCue)
		{
			SoundEffectAudioComponent3->SetSound(SoundCue);
			SoundEffectAudioComponent3->Play();
		}
	}
}

void UAudioManager::PlaySoundEffectByName3(FString SoundName)
{

	int32 Index = SoundEffectNames.IndexOfByKey(SoundName);
	if (SoundEffectCues.IsValidIndex(Index))
		{
		PlaySoundEffect3(Index);
	}
}

void UAudioManager::PlaySoundEffect4(int32 SoundIndex)
{
	if (SoundEffectCues.IsValidIndex(SoundIndex))
	{
		USoundCue* SoundCue = SoundEffectCues[SoundIndex];
		if (SoundCue)
		{
			SoundEffectAudioComponent4->SetSound(SoundCue);
			SoundEffectAudioComponent4->Play();
		}
	}
}

void UAudioManager::PlaySoundEffectByName4(FString SoundName)
{
	int32 Index = SoundEffectNames.IndexOfByKey(SoundName);
	if (SoundEffectCues.IsValidIndex(Index))
	{
		PlaySoundEffect4(Index);
	}
}

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "UObject/NoExportTypes.h"
#include "AudioManager.generated.h"

/**
 * 
 */
class UAudioComponent;
UCLASS()
class PROJECTSAILOR_API UAudioManager : public UObject
{
	GENERATED_BODY()

public:
	UAudioManager();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayMusic(int32 SoundIndex);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayMusicByName(FString SoundName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopMusic();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySoundEffect(int32 SoundIndex);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySoundEffectByName(FString SoundName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySoundEffect2(int32 SoundIndex);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySoundEffectByName2(FString SoundName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
    	void PlaySoundEffect3(int32 SoundIndex);
    
    	UFUNCTION(BlueprintCallable, Category = "Audio")
    	void PlaySoundEffectByName3(FString SoundName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
    	void PlaySoundEffect4(int32 SoundIndex);
    
    	UFUNCTION(BlueprintCallable, Category = "Audio")
    	void PlaySoundEffectByName4(FString SoundName);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundCue*> MusicCues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundCue*> SoundEffectCues;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<FString> MusicNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<FString> SoundEffectNames;

private:
	UPROPERTY()
	UAudioComponent* MusicAudioComponent;

	UPROPERTY()
	UAudioComponent* SoundEffectAudioComponent;
	
	UPROPERTY()
	UAudioComponent* SoundEffectAudioComponent2;

	UPROPERTY()
	UAudioComponent* SoundEffectAudioComponent3;

	UPROPERTY()
	UAudioComponent* SoundEffectAudioComponent4;
};
	

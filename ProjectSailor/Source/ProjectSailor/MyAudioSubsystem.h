// Property of DaPaRy Games

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

public:
	UMyAudioSubsystem();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayMusic(const FString& MusicName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySFX1(const FString& MusicName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TMap<FString, USoundWave*> MusicTracks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TMap<FString, USoundWave*> SFXTracks;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
private:
	UAudioComponent* MusicComponent;

	UAudioComponent* SFX1Component;
	
};

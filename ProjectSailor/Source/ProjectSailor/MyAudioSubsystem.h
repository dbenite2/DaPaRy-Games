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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TMap<FString, USoundWave*> MusicTracks;


protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
private:
	UAudioComponent* AudioComponent;
	
};

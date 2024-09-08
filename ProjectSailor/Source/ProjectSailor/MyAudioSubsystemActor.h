#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyAudioSubsystemActor.generated.h"

/**
 * Responsible for handling audio playback within the game.
 * It manages multiple sound effects and music tracks, providing methods to play, stop, and manage these audio elements.
 * This class utilizes Unreal Engine's AudioComponent to handle individual sounds.
 */

UCLASS()
class PROJECTSAILOR_API AMyAudioSubsystemActor : public AActor {
	GENERATED_BODY()
public:
	AMyAudioSubsystemActor();

	void InitializeAudioComponents();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayMusic(const FString& MusicName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySFX1(const FString& MusicName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySFX2(const FString& MusicName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySFX3(const FString& MusicName);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopMusic();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopSFX1();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopSFX2();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopSFX3();
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	TMap<FString, USoundWave*> MusicTracks;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TMap<FString, USoundWave*> SFXTracks;

	

protected:
	virtual void BeginPlay() override;

private:
	
	UAudioComponent* CreateAudioComponent(UObject* Outer);
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* MusicComponent{nullptr};
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* SFX1Component{nullptr};
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* SFX2Component{nullptr};
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* SFX3Component{nullptr};
};
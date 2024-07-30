#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyAudioSubsystemActor.generated.h"

UCLASS()
class PROJECTSAILOR_API AMyAudioSubsystemActor : public AActor
{
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
	void StopMusic();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopSFX1();

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopSFX2();

	UPROPERTY(EditAnywhere, Category = "Audio")
	TMap<FString, USoundWave*> MusicTracks;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TMap<FString, USoundWave*> SFXTracks;

protected:
	virtual void BeginPlay() override;

private:

    
	UAudioComponent* CreateAudioComponent(UObject* Outer);

	UAudioComponent* MusicComponent;
	UAudioComponent* SFX1Component;
	UAudioComponent* SFX2Component;
};
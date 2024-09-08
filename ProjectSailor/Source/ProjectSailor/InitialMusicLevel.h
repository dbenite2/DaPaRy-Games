// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InitialMusicLevel.generated.h"

class AMyAudioSubsystemActor;

/**
 * AInitialMusicLevel is responsible for managing the playback of initial music
 * at the start of a game level. It utilizes an audio subsystem to handle the audio operations.
 */
UCLASS()
class PROJECTSAILOR_API AInitialMusicLevel : public AActor {
	GENERATED_BODY()
	
public:	
	AInitialMusicLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	FString initialMusic;

protected:
	virtual void BeginPlay() override;
	void PostBeginPlay();

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AMyAudioSubsystemActor* AudioSubsystemActor{nullptr};
};

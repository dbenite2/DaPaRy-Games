// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InitialMusicLevel.generated.h"

class AMyAudioSubsystemActor;
UCLASS()
class PROJECTSAILOR_API AInitialMusicLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInitialMusicLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	FString initialMusic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PostBeginPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AMyAudioSubsystemActor* AudioSubsystemActor;
};

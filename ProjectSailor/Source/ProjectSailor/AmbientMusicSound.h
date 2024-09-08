// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundWave.h"
#include "AmbientMusicSound.generated.h"


class AMyAudioSubsystemActor;
class USphereComponent;

/**
 * This class represents an ambient sound actor that can trigger sound effects
 * when a player enters or exits its sphere of influence.
 */

UCLASS()
class PROJECTSAILOR_API AAmbientMusicSound : public AActor
{
	GENERATED_BODY()

public:
	AAmbientMusicSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	FString nameSFXProximityBegin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	FString nameSFXProximityEnd;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY()
	AMyAudioSubsystemActor* AudioSubsystemActor;

};

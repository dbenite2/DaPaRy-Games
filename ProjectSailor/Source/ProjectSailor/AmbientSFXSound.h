// Property of DaPaRy Games

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundWave.h"


#include "AmbientSFXSound.generated.h"

class AMyAudioSubsystemActor;
class USphereComponent;
UCLASS()
class PROJECTSAILOR_API AAmbientSFXSound : public AActor
{
	GENERATED_BODY()

public:
	AAmbientSFXSound();

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

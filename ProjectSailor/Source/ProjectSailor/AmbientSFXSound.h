// Property of DaPaRy Games

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundWave.h"
#include "MyAudioSubsystem.h"
#include "AmbientSFXSound.generated.h"

class UBoxComponent;
UCLASS()
class PROJECTSAILOR_API AAmbientSFXSound : public AActor
{
	GENERATED_BODY()

public:
	AAmbientSFXSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	FString nameSFXProximity;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY()
	UMyAudioSubsystem* AudioSubsystem;

};

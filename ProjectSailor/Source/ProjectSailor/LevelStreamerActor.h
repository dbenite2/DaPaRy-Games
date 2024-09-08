#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LevelStreamerActor.generated.h"

/**
 *  Responsible for dynamically loading different levels within the game when the player interacts with specific trigger volumes.
 * It uses a box component as a trigger volume to detect overlaps and initiate level streaming based on the specified level reference.
 */

UCLASS()
class PROJECTSAILOR_API ALevelStreamerActor : public AActor {
	GENERATED_BODY()
	
public:	
	ALevelStreamerActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> LevelToLoadReference{nullptr};

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverlapVolume;
	
};

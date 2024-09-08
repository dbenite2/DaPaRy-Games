// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "BulletVFXPlayerHit.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "HItComponent.generated.h"

class AMyAudioSubsystemActor;
class AKeyBeach;

/**
 * Custom ActorComponent designed for handling hit detection and executing corresponding abilities
 * or interactions based on the type of hit object within a game environment. It leverages raycasting to determine
 * hits and dynamically binds interactions or effects based on the hit results.
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UHItComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	UHItComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void HitAbility(UCameraComponent* Camera, AActor* Player, ABulletVFXPlayerHit* bullet, APlayerController* playerController);

	UPROPERTY()
	FHitResult HitScore;

	UPROPERTY(EditAnywhere)
	FVector offset = {0.f, 0.f, 50.f};
};

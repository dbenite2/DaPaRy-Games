// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "MushroomButtonActor.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "HItComponent.generated.h"

class AMyAudioSubsystemActor;
class AKeyBeach;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UHItComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHItComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void HitAbility(UCameraComponent* Camera, AActor* Player);

	UPROPERTY()
	FHitResult HitScore;

	UPROPERTY(EditAnywhere)
	FVector offset = {0.f, 0.f, 50.f};
};

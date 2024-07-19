// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class USphereComponent;
class UMovableStaticMeshComponent;

UCLASS()
class PROJECTSAILOR_API APressurePlate : public AActor
{
	GENERATED_BODY()

	void Interact(bool bIsInteracting);

	bool bIsTriggered{false};
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Trigger")
	UStaticMeshComponent* BaseMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Trigger")
	UMovableStaticMeshComponent* MovableMesh{nullptr};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Trigger")
	USphereComponent* OverlapComponent{nullptr};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	bool bIsDisabled{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	bool bResetTrigger{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Trigger")
	TArray<FName> TargetTags;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

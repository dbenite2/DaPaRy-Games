// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Baculo.h"
#include "GameFramework/Actor.h"
#include "Pickable_Crosier.generated.h"

class AMyAudioSubsystemActor;

/**
 * Represents a pickable object in the game, it destroys itself when picked and spawn the staff in player hands
 */
UCLASS()
class PROJECTSAILOR_API APickable_Crosier : public AActor {
	GENERATED_BODY()
	
public:	
	APickable_Crosier();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * baculo  = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* TriggerZone;

	UPROPERTY()
	ABaculo* baculoComponent;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ABaculo> baculoClass;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage{nullptr};

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	void PickObject(AProjectSailorCharacter* PlayerCharacter);
};

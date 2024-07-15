// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Baculo.h"
#include "GameFramework/Actor.h"
#include "Pickable_Crosier.generated.h"

UCLASS()
class PROJECTSAILOR_API APickable_Crosier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable_Crosier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
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
};

// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Baculo.generated.h"

UCLASS()
class PROJECTSAILOR_API ABaculo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaculo();

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
};

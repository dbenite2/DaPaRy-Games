// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "DoorWay.h"
#include "GameFramework/Actor.h"
#include "Game_Manager.generated.h"

UCLASS()
class PROJECTSAILOR_API AGame_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGame_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostBeginPlay();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ADoorWay*> MiArray;

	UPROPERTY()
	TSubclassOf<ADoorWay> doorWay;

	UFUNCTION()
	void TurnOnPortal(int32 index);
};

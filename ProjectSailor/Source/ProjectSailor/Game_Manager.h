// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "DoorWay.h"
#include "GameFramework/Actor.h"
#include "Game_Manager.generated.h"

/**
 * Custom actor class designed to manage game-level operations,
 * focusing on controlling doorways and portals throughout the game environment.
 * It primarily functions to activate or modify properties of these doorways based on game logic
 * or player interactions.
 */

UCLASS()
class PROJECTSAILOR_API AGame_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGame_Manager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ADoorWay*> MiArray;

	UPROPERTY()
	TSubclassOf<ADoorWay> doorWay;

	UFUNCTION()
	void TurnOnPortal(int32 index);
};

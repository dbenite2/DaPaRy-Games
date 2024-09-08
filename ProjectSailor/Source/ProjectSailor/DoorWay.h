// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamerActor.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "DoorWay.generated.h"

/**
 * ADoorWay derived from AActor, designed to represent doorways in the game that may involve level streaming.
 * This actor is used to manage transitions or interactions associated with doorways, including handling lighting effects 
 * to indicate state changes like level completion.
 */
UCLASS()
class PROJECTSAILOR_API ADoorWay : public AActor {
	GENERATED_BODY()
	
public:	
	ADoorWay();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	ALevelStreamerActor* LevelStreamerActor{nullptr};

	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight{nullptr};

	UPROPERTY(EditAnywhere)
	bool LevelDone = false;

};

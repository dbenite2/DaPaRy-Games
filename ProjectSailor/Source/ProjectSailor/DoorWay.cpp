// Property of DaPaRy Games


#include "DoorWay.h"

#include "LevelStreamerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorWay::ADoorWay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADoorWay::BeginPlay()
{
	Super::BeginPlay();

	pointLight = FindComponentByClass<UPointLightComponent>();
	pointLight->SetIntensity(0.f);
}

// Called every frame
void ADoorWay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


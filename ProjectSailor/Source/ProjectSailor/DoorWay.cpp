// Property of DaPaRy Games


#include "DoorWay.h"

#include "LevelStreamerActor.h"
#include "Kismet/GameplayStatics.h"

ADoorWay::ADoorWay() {
	PrimaryActorTick.bCanEverTick = false;
}

void ADoorWay::BeginPlay() {
	Super::BeginPlay();

	PointLight = FindComponentByClass<UPointLightComponent>();
	PointLight->SetIntensity(0.f);
}

void ADoorWay::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}


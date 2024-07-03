#include "LevelStreamerActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"



ALevelStreamerActor::ALevelStreamerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;
	OverlapVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelStreamerActor::OverlapBegins);
}

void ALevelStreamerActor::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelStreamerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * Function that checks when a character pass over a loader trigger.
 * It will start loading the passed level reference.
 */
void ALevelStreamerActor::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	const ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == MyCharacter && !LevelToLoadReference.IsNull()) {
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoadReference);
	}
}



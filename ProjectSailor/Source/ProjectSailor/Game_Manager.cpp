// Property of DaPaRy Games


#include "Game_Manager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AGame_Manager::AGame_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGame_Manager::BeginPlay()
{
	Super::BeginPlay();

	TurnOnPortal(0.f);
}

// Called every frame
void AGame_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGame_Manager::TurnOnPortal(int32 index)
{
	if(MiArray.IsValidIndex(index))
	{
		for (int i = 0; i < MiArray.Num(); ++i)
		{
			if (MiArray[i]->LevelStreamerActor)
			{
				MiArray[i]->LevelStreamerActor->SetActorEnableCollision(ECollisionEnabled::NoCollision);

				if(MiArray[i]->LevelDone)
				{
					MiArray[i]->pointLight->SetLightColor(FColor::Yellow);
					MiArray[i]->LevelDone = false;
				}
			}
		}
		
		MiArray[index]->pointLight->SetIntensity(5000.f);
		if (MiArray[index]->LevelStreamerActor)
		{
			MiArray[index]->LevelStreamerActor->SetActorEnableCollision(true);
		}
	}
}


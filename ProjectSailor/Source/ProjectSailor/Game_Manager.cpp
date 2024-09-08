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

	
}

void AGame_Manager::PostBeginPlay()
{
	TurnOnPortal(0.f);
}

// Called every frame
void AGame_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGame_Manager::TurnOnPortal(int32 index)
{
	if (MiArray.IsValidIndex(index) && MiArray[index])
    	{
    		for (int i = 0; i < MiArray.Num(); ++i)
    		{
    			if (MiArray[i] && MiArray[i]->LevelStreamerActor) // Verifica que no sea nullptr
    			{
    				MiArray[i]->LevelStreamerActor->SetActorEnableCollision(ECollisionEnabled::NoCollision);
    
    				if (MiArray[i]->LevelDone && MiArray[i]->pointLight) // Verifica el puntero pointLight
    				{
    					MiArray[i]->pointLight->SetLightColor(FColor::Yellow);
    					MiArray[i]->LevelDone = false;
    				}
    			}
    		}
    
    		// Asegúrate de que el índice y sus propiedades no son nullptr
    		if (MiArray[index]->pointLight)
    		{
    			MiArray[index]->pointLight->SetIntensity(5000.f);
    		}
    		if (MiArray[index]->LevelStreamerActor)
    		{
    			MiArray[index]->LevelStreamerActor->SetActorEnableCollision(true);
    		}
    	}
}


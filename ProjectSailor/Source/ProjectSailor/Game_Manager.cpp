// Property of DaPaRy Games


#include "Game_Manager.h"

#include "Kismet/GameplayStatics.h"

AGame_Manager::AGame_Manager() {
	PrimaryActorTick.bCanEverTick = false;

}

void AGame_Manager::BeginPlay() {
	Super::BeginPlay();

	
}

void AGame_Manager::PostBeginPlay()
{
	TurnOnPortal(0.f);
}

void AGame_Manager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}


void AGame_Manager::TurnOnPortal(int32 index)
{
	if (MiArray.IsValidIndex(index) && MiArray[index])
    	{
    		for (int i = 0; i < MiArray.Num(); ++i)
    		{
    			if (MiArray[i] && MiArray[i]->LevelStreamerActor) 
    			{
    				MiArray[i]->LevelStreamerActor->SetActorEnableCollision(ECollisionEnabled::NoCollision);
    
    				if (MiArray[i]->LevelDone && MiArray[i]->PointLight) 
    				{
    					MiArray[i]->PointLight->SetLightColor(FColor::Yellow);
    					MiArray[i]->LevelDone = false;
    				}
    			}
    		}
    

    		if (MiArray[index]->PointLight)
    		{
    			MiArray[index]->PointLight->SetIntensity(5000.f);
    		}
    		if (MiArray[index]->LevelStreamerActor)
    		{
    			MiArray[index]->LevelStreamerActor->SetActorEnableCollision(true);
    		}
    }
}


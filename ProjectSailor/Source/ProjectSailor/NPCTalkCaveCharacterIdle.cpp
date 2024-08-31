// Property of DaPaRy Games


#include "NPCTalkCaveCharacterIdle.h"

// Sets default values
ANPCTalkCaveCharacterIdle::ANPCTalkCaveCharacterIdle()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCTalkCaveCharacterIdle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCTalkCaveCharacterIdle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCTalkCaveCharacterIdle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


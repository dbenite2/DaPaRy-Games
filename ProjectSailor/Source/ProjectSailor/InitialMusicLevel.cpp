// Property of DaPaRy Games


#include "InitialMusicLevel.h"

#include "MyAudioSubsystemActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInitialMusicLevel::AInitialMusicLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioSubsystemActor = nullptr;
}

// Called when the game starts or when spawned
void AInitialMusicLevel::BeginPlay()
{
	Super::BeginPlay();
	//  encontrar el AMyAudioSubsystemActor
	UWorld* World = GetWorld();
	if (World)
	{
		AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(World, AMyAudioSubsystemActor::StaticClass()));
		if (!AudioSubsystemActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to get UMyAudioSubsystem from GameInstance!"));
		}
		GetWorldTimerManager().SetTimerForNextTick(this, &AInitialMusicLevel::PostBeginPlay);
		
	}
}

void AInitialMusicLevel::PostBeginPlay()
{
	AudioSubsystemActor->PlayMusic(initialMusic);
}

// Called every frame
void AInitialMusicLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


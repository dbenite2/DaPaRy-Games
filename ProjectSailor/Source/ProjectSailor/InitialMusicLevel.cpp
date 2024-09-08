// Property of DaPaRy Games


#include "InitialMusicLevel.h"

#include "MyAudioSubsystemActor.h"
#include "Kismet/GameplayStatics.h"


AInitialMusicLevel::AInitialMusicLevel() {
	PrimaryActorTick.bCanEverTick = true;
}

void AInitialMusicLevel::BeginPlay() {
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld()) {
		AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(World, AMyAudioSubsystemActor::StaticClass()));
		if (!AudioSubsystemActor) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to get UMyAudioSubsystem from GameInstance!"));
		}
		GetWorldTimerManager().SetTimerForNextTick(this, &AInitialMusicLevel::PostBeginPlay);
	}
}

void AInitialMusicLevel::PostBeginPlay() {
	if (AudioSubsystemActor)  AudioSubsystemActor->PlayMusic(initialMusic);
}

void AInitialMusicLevel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}


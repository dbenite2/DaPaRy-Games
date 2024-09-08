// Property of DaPaRy Games

#include "AmbientMusicSound.h"
#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"

AAmbientMusicSound::AAmbientMusicSound() {
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmbientMusicSound::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAmbientMusicSound::OnOverlapEnd);
	SphereComponent->InitSphereRadius(300.0f);
	AudioSubsystemActor = nullptr;
}

void AAmbientMusicSound::BeginPlay() {
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World) {
		AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(World, AMyAudioSubsystemActor::StaticClass()));
		if (!AudioSubsystemActor) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to get UMyAudioSubsystem from GameInstance!"));
		}
	}
}
void AAmbientMusicSound::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AProjectSailorCharacter::StaticClass())) {
		if (AudioSubsystemActor) {
			if(nameSFXProximityBegin!="") {
				AudioSubsystemActor->StopMusic();
				AudioSubsystemActor->PlayMusic(nameSFXProximityBegin);
			}
		}
	}
}
void AAmbientMusicSound::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AProjectSailorCharacter::StaticClass())) {
		if (AudioSubsystemActor ) {
			if(nameSFXProximityBegin!="") {
				AudioSubsystemActor->StopMusic();
			}
			if(nameSFXProximityEnd!="") {
				AudioSubsystemActor->PlayMusic(nameSFXProximityEnd);
			}
		}
	}
}

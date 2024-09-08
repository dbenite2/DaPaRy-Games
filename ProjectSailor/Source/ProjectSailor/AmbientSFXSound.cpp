// Property of DaPaRy Games


#include "AmbientSFXSound.h"

#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"

AAmbientSFXSound::AAmbientSFXSound() {
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmbientSFXSound::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAmbientSFXSound::OnOverlapEnd);
	
	SphereComponent->InitSphereRadius(300.0f);
	AudioSubsystemActor = nullptr;
}

void AAmbientSFXSound::BeginPlay() {
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World) {
		AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(World, AMyAudioSubsystemActor::StaticClass()));
		if (!AudioSubsystemActor) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to get UMyAudioSubsystem from GameInstance!"));
		}
	}
}

void AAmbientSFXSound::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AProjectSailorCharacter::StaticClass())) {
		if (AudioSubsystemActor) {
			if(nameSFXProximityBegin!="") {
				AudioSubsystemActor->StopSFX1();
				AudioSubsystemActor->PlaySFX1(nameSFXProximityBegin);
			}
		}
	}
}

void AAmbientSFXSound::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AProjectSailorCharacter::StaticClass())) {
		if (AudioSubsystemActor ) {
			if(nameSFXProximityBegin!="") {
				AudioSubsystemActor->StopSFX1();
			}
			if(nameSFXProximityEnd!="") {
				AudioSubsystemActor->PlaySFX1(nameSFXProximityEnd);
			}
		}
	}
}

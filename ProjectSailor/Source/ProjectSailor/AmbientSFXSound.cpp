// Property of DaPaRy Games


#include "AmbientSFXSound.h"

#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAmbientSFXSound::AAmbientSFXSound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmbientSFXSound::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAmbientSFXSound::OnOverlapEnd);
	
	// Configura el tamaño del BoxComponent según sea necesario
	SphereComponent->InitSphereRadius(300.0f);
	AudioSubsystemActor = nullptr;
}

// Called when the game starts or when spawned
void AAmbientSFXSound::BeginPlay()
{
	Super::BeginPlay();
	// Obtener el GameInstance y encontrar el UMyAudioSubsystem
	UWorld* World = GetWorld();
	if (World)
	{
		AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(World, AMyAudioSubsystemActor::StaticClass()));
		if (!AudioSubsystemActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to get UMyAudioSubsystem from GameInstance!"));
		}
	}
}

void AAmbientSFXSound::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AProjectSailorCharacter::StaticClass()))
	{
		if (AudioSubsystemActor)
		{
			//play start sound
			if(nameSFXProximityBegin!="")
			{
				//por si habia algun sonido pendiente
				AudioSubsystemActor->StopSFX1();
				AudioSubsystemActor->PlaySFX1(nameSFXProximityBegin);
			}
		}
	}
}

void AAmbientSFXSound::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AProjectSailorCharacter::StaticClass()))
	{
		if (AudioSubsystemActor )
		{
			//finish startSound
			if(nameSFXProximityBegin!="")
			{
				AudioSubsystemActor->StopSFX1();
			}
			//startEndSound
			if(nameSFXProximityEnd!="")
			{
				AudioSubsystemActor->PlaySFX1(nameSFXProximityEnd);
			}
		}
	}
}
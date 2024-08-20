// Property of DaPaRy Games


#include "BulletVFXPlayerHit.h"

#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"



ABulletVFXPlayerHit::ABulletVFXPlayerHit() {
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(DefaultSceneRoot);
	
	Velocity = 1000.0f;
	
	Lifetime = 10.0f;
}

void ABulletVFXPlayerHit::BeginPlay() {
	Super::BeginPlay();
	//initial position player
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FVector Location = PlayerCharacter->GetActorLocation();

	
	SetActorLocation(Location);
}

void ABulletVFXPlayerHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the bullet forward
	FVector CurrentLocation = GetActorLocation();
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FVector NewLocation = CurrentLocation + PlayerCharacter->GetActorForwardVector() * Velocity * DeltaTime;
	SetActorLocation(NewLocation);
	
	// Decrease the bullet's lifetime
	Lifetime -= DeltaTime;
	
	// Destroy the bullet if its lifetime is over
	if (Lifetime <= 0.0f)
	{
		Destroy();
	}
}


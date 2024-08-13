// Property of DaPaRy Games


#include "BulletVFXPlayerHit.h"

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
	
}

void ABulletVFXPlayerHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the bullet forward
	FVector Location = GetActorLocation();
	Location += FVector(Velocity, 0.0f, 0.0f) * DeltaTime;
	SetActorLocation(Location);

	// Decrease the bullet's lifetime
	Lifetime -= DeltaTime;

	// Destroy the bullet if its lifetime is over
	if (Lifetime <= 0.0f)
	{
		Destroy();
	}
}


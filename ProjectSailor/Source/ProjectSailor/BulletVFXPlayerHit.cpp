// Property of DaPaRy Games


#include "BulletVFXPlayerHit.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABulletVFXPlayerHit::ABulletVFXPlayerHit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(DefaultSceneRoot);

	// Set the bullet's velocity
	Velocity = 1000.0f;

	// Set the bullet's lifetime
	Lifetime = 10.0f;
}

// Called when the game starts or when spawned
void ABulletVFXPlayerHit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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


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
	
	Velocity = 5000.0f;
	
	Lifetime = 0.75f;
}

void ABulletVFXPlayerHit::BeginPlay() {
	Super::BeginPlay();
	//camera rotation
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector CameraLocation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//initial position player
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FVector Location = PlayerCharacter->positionBaculoCharacter;

	// Get player's forward vector and location
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();

	// Adjust the start location to be a bit in front of the player and a bit higher in the Y axis
	FVector LineTraceStart = Location + ForwardVector;

	// Calculate the direction of the bullet based on camera rotation
	FVector Direction = FRotator(CameraRotation.Pitch, CameraRotation.Yaw, CameraRotation.Roll).Vector();

	// Normalize the direction vector
	Direction = Direction.GetSafeNormal();

	// Set the initial direction of the bullet
	InitDirection = Direction;

	// Set the location of the bullet
	SetActorLocation(LineTraceStart);

	
}

void ABulletVFXPlayerHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the bullet forward
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + InitDirection * Velocity * DeltaTime;
	SetActorLocation(NewLocation);
	SetActorRotation(CameraRotation);
	// Decrease the bullet's lifetime
	Lifetime -= DeltaTime;
	
	// Destroy the bullet if its lifetime is over
	if (Lifetime <= 0.0f)
	{
		FTransform SpawnTransform = GetActorTransform();
		// Spawn Cascade particle effect
		UParticleSystemComponent* ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticleSystemWhenDestroys,  // Tu sistema de partículas
			SpawnTransform.GetLocation(),   // Localización donde spawnear la partícula
			FRotator::ZeroRotator,
			FVector(1.0f)   // Escala de la partícula
		);

		if (ParticleComponent)
		{
			// Configurar temporizador para desactivar y destruir el componente de la partícula
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ParticleComponent]()
			{
				ParticleComponent->DeactivateSystem();
				ParticleComponent->DestroyComponent();
				
			}, 0.5f, false);  // 1.0f es la duración antes de desactivar
			Destroy();
		}
		
	}
}


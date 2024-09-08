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
	
	Lifetime = 0.25f;
}

void ABulletVFXPlayerHit::BeginPlay() {
	Super::BeginPlay();
	//camera rotation
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// Get the screen center
	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenCenter(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);

	// Convert screen position to world position and direction
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection);
	
	// Set the initial direction of the bullet
	InitDirection = WorldDirection;

	// Set the location of the bullet
	SetActorLocation(WorldLocation);
	
}

void ABulletVFXPlayerHit::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Move the bullet forward
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + InitDirection * Velocity * DeltaTime;
	SetActorLocation(NewLocation);
	SetActorRotation(CameraRotation);
	Lifetime -= DeltaTime;
	
	// Destroy the bullet if its lifetime is over
	if (Lifetime <= 0.0f) {
		FTransform SpawnTransform = GetActorTransform();
		// Spawn Cascade particle effect
		UParticleSystemComponent* ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticleSystemWhenDestroys, 
			SpawnTransform.GetLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f)
		);

		if (ParticleComponent) {
			
			FTimerHandle TimerHandle;
			if (TimerHandle.IsValid()) {
			    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ParticleComponent] {
                				ParticleComponent->DeactivateSystem();
                				ParticleComponent->DestroyComponent();
                				
                			}, 0.5f, false); 
                			Destroy();
			}
		}
	}
}


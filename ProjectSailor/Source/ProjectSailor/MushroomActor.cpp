// Property of DaPaRy Games


#include "MushroomActor.h"
#include "NiagaraComponent.h"
#include "UObject/ConstructorHelpers.h"

/**
 * Muhsroom Actor Appears When MushroomButtomActor is hit, and move down until SpawnLocation. Then wait 16 seconds and desapear
 **/

// Sets default values
AMushroomActor::AMushroomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(DefaultSceneRoot);

	pSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystem"));
	pSystem->SetupAttachment(RootComponent);
	pSystem->bAutoActivate = true;

	endParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystemEnd"));
	endParticleSystem->SetupAttachment(RootComponent);
	endParticleSystem->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AMushroomActor::BeginPlay()
{
	Super::BeginPlay();
	if (NiagaraSystem) {
		endParticleSystem->SetAsset(NiagaraSystem);
	}
}

// Called every frame
void AMushroomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation.Z > TargetZ)
	{
		CurrentLocation.Z -= FallingSpeed * DeltaTime;
		if (CurrentLocation.Z <= TargetZ)
		{
			CurrentLocation.Z = TargetZ;

			if(IsHit)
			{
				// FTimerHandle DespawnTimerHandle;
				GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle, this, &AMushroomActor::Despawn, timerHold, false);
			}
			
		}
		SetActorLocation(CurrentLocation);
	}	
}

void AMushroomActor::Despawn()
{
	BP_InitialPosition->SetActorHiddenInGame(false);
	BP_InitialPosition->SetActorEnableCollision(true);
	
	if (endParticleSystem)
	{
		endParticleSystem->SetVisibility(true);
		endParticleSystem->Activate(true); // Activa el sistema de partículas

		FTimerHandle DespawnTimerHandle2;
		GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle2, this, &AMushroomActor::SetVisibilityActor, 0.5f, false);
	}	
}

void AMushroomActor::SetVisibilityActor()
{
	IsHit = false;
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	endParticleSystem->SetVisibility(false);
	endParticleSystem->Activate(false);
}
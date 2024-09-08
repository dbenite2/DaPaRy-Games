// Property of DaPaRy Games


#include "ButtonSpawnActor.h"
#include "Kismet/GameplayStatics.h"
#include "MyAudioSubsystemActor.h"
#include "Components/PointLightComponent.h"
#include "Pickable_Object.h"

#include "UObject/ConstructorHelpers.h"

AButtonSpawnActor::AButtonSpawnActor() {
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BaseMesh->SetupAttachment(DefaultRoot);
	
	CircleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CircleMesh->SetupAttachment(BaseMesh);
	
	CircleMesh->SetRelativeLocation(FVector(0.f, 0.f, 33.f));
	CircleMesh->SetRelativeScale3D(FVector(3.f, 3.f, 0.01f));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(CircleMesh);
	PointLight->AttenuationRadius = 150.0f;
	PointLight->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	PointLight->SetVisibility(false);
	PointLight->Intensity = 25000.f;
}

void AButtonSpawnActor::BeginPlay() {
	Super::BeginPlay();
	
}

void AButtonSpawnActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AButtonSpawnActor::SpawnActor() {
	AMyAudioSubsystemActor* AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
	if (bResetButton) {
		for (const TPair<APickable_Object*, FVector>& Pair : ActorsWithInitialLocation) {
			APickable_Object* ActorToReset = Pair.Key;
			FVector InitialLocation = Pair.Value;
			if (ActorToReset) {
				ActorToReset->mesh->SetSimulatePhysics(false);
				ActorToReset->mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				ActorToReset->SetActorLocation(InitialLocation, true);
				ActorToReset->ResetObjectLocation(InitialLocation);
				// ActorToReset->mesh->SetSimulatePhysics(true);
				ActorToReset->mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				ActorToReset->TeleportTo(InitialLocation, ActorToReset->GetActorRotation());
				UE_LOG(LogTemp, Warning, TEXT("Moving %s to %s"), *ActorToReset->GetName(), *InitialLocation.ToString());
			}
			if (AudioSubsystemActor) {
				AudioSubsystemActor->PlaySFX1("hitAttackMagic2");
				AudioSubsystemActor->PlaySFX3("tentaculo2");
			}
		}
		return;
	}
	
	if(BP_ActorSpawnable!=nullptr) {
		//put position 
		BP_ActorSpawnable->SetActorLocation(SpawnLocation);
		//appears cube and add physics
		BP_ActorSpawnable->SetActorHiddenInGame(false);
		BP_ActorSpawnable->SetActorEnableCollision(true);
		

		//sound button
		if (AudioSubsystemActor) {
			AudioSubsystemActor->PlaySFX1("hitAttackMagic2");
			AudioSubsystemActor->PlaySFX3("tentaculo2");
		}
		
		//hide button
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
 
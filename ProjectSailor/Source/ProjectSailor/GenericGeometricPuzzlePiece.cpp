// Property of DaPaRy Games


#include "GenericGeometricPuzzlePiece.h"

#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AGenericGeometricPuzzlePiece::AGenericGeometricPuzzlePiece() {
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->SetupAttachment(StaticMesh);
	
	CubeMesh->SetRelativeLocation(FVector(0.f, 0.f, 33.f));
	CubeMesh->SetRelativeScale3D(FVector(3.f, 3.f, 0.01f));
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(150.f, 150.f, 50.f));
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGenericGeometricPuzzlePiece::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AGenericGeometricPuzzlePiece::OnOverlapEnd);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->AttenuationRadius = 150.0f;
	PointLight->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	PointLight->SetVisibility(false);
	PointLight->Intensity = 25000.f;
	
	incorrectParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IncorrectParticleSystem"));
	incorrectParticleSystem->SetupAttachment(RootComponent);
	incorrectParticleSystem->bAutoActivate = false;
	
}

void AGenericGeometricPuzzlePiece::BeginPlay() {
	Super::BeginPlay();
	
}

void AGenericGeometricPuzzlePiece::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGenericGeometricPuzzlePiece::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if (OtherActor && (OtherActor != this)) {
		AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
		if (PlayerCharacter) {
			AMyAudioSubsystemActor* AudioSubsystemActor =
				Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
			
			if(!isCorrect) {
				if (AudioSubsystemActor) {
					if(!isSpawnLevelPlatform) {
						AudioSubsystemActor->PlaySFX1("wronganswer");
						AudioSubsystemActor->PlaySFX3("explosionIncorrect");
					} else {
						AudioSubsystemActor->PlaySFX1("spawnSoul");
					}
				}
				
				if (BP_InitialPosition) {
					FVector InitialPosition = BP_InitialPosition->GetActorLocation();
					FVector PlayerPosition = OtherActor->GetActorLocation();
					
					PlayerPosition.X = InitialPosition.X;
					PlayerPosition.Y = InitialPosition.Y;
					PlayerPosition.Z = InitialPosition.Z + 100.f;

					for (AMushroomActor* MushroomActor : MushroomActors) {
						if (MushroomActor) {
							MushroomActor->GetWorld()->GetTimerManager().ClearTimer(MushroomActor->DespawnTimerHandle);
							MushroomActor->Despawn();
						}
					}
					OtherActor->SetActorLocation(PlayerPosition);
				}
			} else {
				if (AudioSubsystemActor) {
					AudioSubsystemActor->PlaySFX1("correctAnswer");	
				}
				if (NameFigureStep == "Cross") {
					PointLight->SetLightColor(FLinearColor::Red);
				} else if (NameFigureStep == "Circle") {
					PointLight->SetLightColor(FLinearColor::Blue);
				} else if (NameFigureStep == "Square") {
					PointLight->SetLightColor(FLinearColor::Yellow);
				} else if (NameFigureStep == "Triangle") {
					PointLight->SetLightColor(FLinearColor::Green);
				}
				PointLight->SetVisibility(true);
			}
		}
	}
}

void AGenericGeometricPuzzlePiece::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this)) {
		if(!isCorrect) {
			if (incorrectParticleSystem) {
				incorrectParticleSystem->ActivateSystem();
			}
		}
	}
}

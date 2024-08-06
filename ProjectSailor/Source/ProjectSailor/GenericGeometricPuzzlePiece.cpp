// Property of DaPaRy Games


#include "GenericGeometricPuzzlePiece.h"

#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGenericGeometricPuzzlePiece::AGenericGeometricPuzzlePiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	 // Create and attach the cube mesh component
        CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
        CubeMesh->SetupAttachment(StaticMesh); // Adjuntar al StaticMesh

	// Set relative location and scale for the cube mesh
	CubeMesh->SetRelativeLocation(FVector(0.f, 0.f, 33.f));
	CubeMesh->SetRelativeScale3D(FVector(3.f, 3.f, 0.01f));

	// Create and attach the trigger box component
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(150.f, 150.f, 50.f));
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	// Bind events to the trigger box
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGenericGeometricPuzzlePiece::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AGenericGeometricPuzzlePiece::OnOverlapEnd);

	//Create and attach the point light component
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->AttenuationRadius = 150.0f;
	PointLight->SetRelativeLocation(FVector(0.f, 0.f, 80.f)); // Adjust the location as needed
	PointLight->SetVisibility(false); // Initially hidden
	PointLight->Intensity = 25000.f;


	// Create and attach the particle system component
	incorrectParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IncorrectParticleSystem"));
	incorrectParticleSystem->SetupAttachment(RootComponent);
	incorrectParticleSystem->bAutoActivate = false; // Disable auto-activation


}

// Called when the game starts or when spawned
void AGenericGeometricPuzzlePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenericGeometricPuzzlePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenericGeometricPuzzlePiece::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			AMyAudioSubsystemActor* AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
			// UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with %s"), *OtherActor->GetName());
			// UE_LOG(LogTemp, Warning, TEXT("Figure Step: %s"), *NameFigureStep);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Figure Step: %s"), *NameFigureStep));

			// Implement specific behavior for overlap begin here if needed
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Figure correct: %s"), isCorrect ? TEXT("true") : TEXT("false")));

			if(!isCorrect)
			{
				//incorrect sound if its casilla
				if(!isSpawnLevelPlatform)
				{
					AudioSubsystemActor->PlaySFX1("wronganswer");
					AudioSubsystemActor->PlaySFX3("explosionIncorrect");
				}
				//if its spawn actor
				else
				{
					AudioSubsystemActor->PlaySFX1("spawnSoul");
				}
				
				//TO-DO--> teleport
				if (BP_InitialPosition)
				{
					FVector InitialPosition = BP_InitialPosition->GetActorLocation();
					FVector PlayerPosition = OtherActor->GetActorLocation();

					// Set the player's X and Y to the InitialPosition's X and Y, keep the player's Z
					PlayerPosition.X = InitialPosition.X;
					PlayerPosition.Y = InitialPosition.Y;
					PlayerPosition.Z = InitialPosition.Z + 100.f;

					OtherActor->SetActorLocation(PlayerPosition);
				}
			}
			else
			{
				//correct sound
				AudioSubsystemActor->PlaySFX1("correctAnswer");
				// Set light color based on NameFigureStep
				if (NameFigureStep == "Cross")
				{
					PointLight->SetLightColor(FLinearColor::Red);
				}
				else if (NameFigureStep == "Circle")
				{
					PointLight->SetLightColor(FLinearColor::Blue);
				}
				else if (NameFigureStep == "Square")
				{
					PointLight->SetLightColor(FLinearColor::Yellow);
				}
				else if (NameFigureStep == "Triangle")
				{
					PointLight->SetLightColor(FLinearColor::Green);
				}

				PointLight->SetVisibility(true);

			}
		}
	}
}

void AGenericGeometricPuzzlePiece::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		if(!isCorrect)
		{
			if (incorrectParticleSystem)
			{
				incorrectParticleSystem->ActivateSystem();
			}
		}
		
	}
}


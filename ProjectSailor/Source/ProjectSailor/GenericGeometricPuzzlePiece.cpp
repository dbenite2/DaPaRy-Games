// Property of DaPaRy Games


#include "GenericGeometricPuzzlePiece.h"

#include "Components/BoxComponent.h"

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
	TriggerBox->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	// Bind events to the trigger box
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGenericGeometricPuzzlePiece::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AGenericGeometricPuzzlePiece::OnOverlapEnd);

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
		// UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with %s"), *OtherActor->GetName());
		// UE_LOG(LogTemp, Warning, TEXT("Figure Step: %s"), *NameFigureStep);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Figure Step: %s"), *NameFigureStep));

		// Implement specific behavior for overlap begin here if needed
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Figure correct: %s"), isCorrect ? TEXT("true") : TEXT("false")));

		if(!isCorrect)
		{
			//TO-DO--> teleport 
		}
	}
}

void AGenericGeometricPuzzlePiece::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		
		
	}
}


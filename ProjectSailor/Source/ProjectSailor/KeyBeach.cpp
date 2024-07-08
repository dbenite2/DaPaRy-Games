// Property of DaPaRy Games


#include "KeyBeach.h"

#include "Components/SphereComponent.h"

// Sets default values
AKeyBeach::AKeyBeach()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create and initialize the mesh component
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;
	KeyMesh->SetSimulatePhysics(false);
	KeyMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	// Create and initialize the sphere collider
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent); // Attach the sphere collider to the root component
	SphereCollider->SetSphereRadius(300.f); // Adjust the radius as needed
	SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereCollider->SetGenerateOverlapEvents(true);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AKeyBeach::OnOverlapBegin);
	
	MaterialInterface = nullptr;
	
}

// Called when the game starts or when spawned
void AKeyBeach::BeginPlay()
{
	Super::BeginPlay();
	// Obtener el material asignado al objeto
	MaterialInterface = KeyMesh->GetMaterial(0);
	// Llamar a la función de parpadeo cada cierto intervalo de tiempo
	GetWorldTimerManager().SetTimer(TimerHandle_Blink, this, &AKeyBeach::BlinkEffect, 0.5f, true);
	
}

void AKeyBeach::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap detected with %s"), *OtherActor->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Overlap detected with %s"), *OtherActor->GetName()));

		// Implement specific behavior for overlap here if needed
	}
}

// Called every frame
void AKeyBeach::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AKeyBeach::ActivateKeyPhysics()
{
	KeyMesh->SetSimulatePhysics(true);
}

void AKeyBeach::Interact_Implementation()
{
	IInteractionInterface::Interact_Implementation();
	ActivateKeyPhysics();
	ModifyCableComponent();
}

void AKeyBeach::BlinkEffect()
{
	if (MaterialInterface)
	{
		//time passed since beginning
		float TimeElapsed = FMath::Fmod(GetGameTimeSinceCreation(), 3.0f);
		//half period of 1.5s
		float HalfPeriod = 1.5f;

		//initial brightness
		float Brightness = 0.1f;
		//brightness from 0.1 to 5
		if (TimeElapsed < HalfPeriod)
		{
			Brightness = FMath::Lerp(0.1f, 5.0f, TimeElapsed / HalfPeriod);
		}
		//brightness from 5 to 0.1
		else
		{
			Brightness = FMath::Lerp(5.0f, 0.1f, (TimeElapsed - HalfPeriod) / HalfPeriod);
		}

		//create a dynamic instance
		UMaterialInstanceDynamic* DynamicMaterialInstance = KeyMesh->CreateAndSetMaterialInstanceDynamic(0);

		//apply the new value to the scalar parameter
		if (DynamicMaterialInstance)
		{
			DynamicMaterialInstance->SetScalarParameterValue(BrightnessParameterName, Brightness);
		}
	}
}

void AKeyBeach::ModifyCableComponent()
{
	if (BP_Rope)
	{

		// Obtener los componentes del Blueprint
		UCableComponent* CableComponent = BP_Rope->FindComponentByClass<UCableComponent>();
		
			if (CableComponent)
			{
				// Se encontró el UCableComponent, ahora desactivar el attach
				CableComponent->bAttachEnd = false;
            
				// Aquí podrías hacer otras operaciones con CableComponent si es necesario
			}
		
	}
}


// Property of DaPaRy Games


#include "KeyBeach.h"

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


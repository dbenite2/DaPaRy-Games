// Property of DaPaRy Games


#include "KeyBeach.h"

#include "ProjectSailorCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

// Called when the game starts or when spawned
void AKeyBeach::BeginPlay()
{
	Super::BeginPlay();
	// Obtener el material asignado al objeto
	MaterialInterface = KeyMesh->GetMaterial(0);
	// Llamar a la función de parpadeo cada cierto intervalo de tiempo
	GetWorldTimerManager().SetTimer(TimerHandle_Blink, this, &AKeyBeach::BlinkEffect, 0.5f, true);
	GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
}

void AKeyBeach::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this)) {
		FString CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		//if it has physics, the hit has been done and if the overlap is the player
		if(hasPhysics) {
			AProjectSailorCharacter* SailorCharacter = Cast<AProjectSailorCharacter>(OtherActor);
			if (SailorCharacter && GameManager) {
				GameManager->SetCurrentLevelStatus(CurrentLevelName, 2);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Key Taken")));
				SetActorHiddenInGame(true);
				SetActorEnableCollision(false);
			}
		}
	}
}


void AKeyBeach::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AKeyBeach::ActivateKeyPhysics() {
	KeyMesh->SetSimulatePhysics(true);
	hasPhysics = true;
}

void AKeyBeach::Interact_Implementation() {
	IInteractionInterface::Interact_Implementation();
	ActivateKeyPhysics();
	ModifyCableComponent();
}

void AKeyBeach::BlinkEffect() {
	if (MaterialInterface) {
		//time passed since beginning
		float TimeElapsed = FMath::Fmod(GetGameTimeSinceCreation(), 3.0f);
		//half period of 1.5s
		float HalfPeriod = 1.5f;

		//initial brightness
		float Brightness = 0.1f;
		//brightness from 0.1 to 5
		if (TimeElapsed < HalfPeriod) {
			Brightness = FMath::Lerp(0.1f, 5.0f, TimeElapsed / HalfPeriod);
		}
		//brightness from 5 to 0.1
		else {
			Brightness = FMath::Lerp(5.0f, 0.1f, (TimeElapsed - HalfPeriod) / HalfPeriod);
		}

		//create a dynamic instance
		UMaterialInstanceDynamic* DynamicMaterialInstance = KeyMesh->CreateAndSetMaterialInstanceDynamic(0);

		//apply the new value to the scalar parameter
		if (DynamicMaterialInstance) {
			DynamicMaterialInstance->SetScalarParameterValue(BrightnessParameterName, Brightness);
		}
	}
}

void AKeyBeach::ModifyCableComponent() {
	if (!BP_Rope) return;
	UCableComponent* CableComponent = BP_Rope->FindComponentByClass<UCableComponent>();
	if (CableComponent) {
		CableComponent->bAttachEnd = false;
	}
}

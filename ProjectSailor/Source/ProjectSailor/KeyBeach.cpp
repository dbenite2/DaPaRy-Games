// Property of DaPaRy Games


#include "KeyBeach.h"

#include "MyAudioSubsystemActor.h"
#include "CableComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SailorInstance.h"
#include "Components/PointLightComponent.h"

AKeyBeach::AKeyBeach() {
	PrimaryActorTick.bCanEverTick = true;
	
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;
	KeyMesh->SetSimulatePhysics(false);
	KeyMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSphereRadius(300.f);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereCollider->SetGenerateOverlapEvents(true);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AKeyBeach::OnOverlapBegin);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->AttenuationRadius = 150.0f;
	PointLight->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	PointLight->SetVisibility(true);
	PointLight->Intensity = 25000.f;
}

void AKeyBeach::BeginPlay() {
	Super::BeginPlay();
	MaterialInterface = KeyMesh->GetMaterial(0);
	GetWorldTimerManager().SetTimer(TimerHandle_Blink, this, &AKeyBeach::BlinkEffect, 0.5f, true);
	GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
}

void AKeyBeach::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this)) {
		FString CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	}
}


void AKeyBeach::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AKeyBeach::ActivateKeyPhysics() {
	KeyMesh->SetSimulatePhysics(true);
	hasPhysics = true;
	AMyAudioSubsystemActor* AudioSubsystemActor =
		Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
	if (AudioSubsystemActor)  AudioSubsystemActor->PlaySFX1("hitAttackMagic2");
}

void AKeyBeach::Interact_Implementation() {
	IInteractionInterface::Interact_Implementation();
	ActivateKeyPhysics();
	ModifyCableComponent();
}

void AKeyBeach::BlinkEffect() {
	if (MaterialInterface) {
		
		float TimeElapsed = FMath::Fmod(GetGameTimeSinceCreation(), 3.0f);
		float HalfPeriod = 1.5f;
		
		float Brightness = 0.1f;
		if (TimeElapsed < HalfPeriod) {
			Brightness = FMath::Lerp(0.1f, 5.0f, TimeElapsed / HalfPeriod);
		} else {
			Brightness = FMath::Lerp(5.0f, 0.1f, (TimeElapsed - HalfPeriod) / HalfPeriod);
		}
		
		UMaterialInstanceDynamic* DynamicMaterialInstance = KeyMesh->CreateAndSetMaterialInstanceDynamic(0);
		
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

void AKeyBeach::PickedObject() {
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (GameManager) {
		GameManager->SetCurrentLevelStatus(CurrentLevelName, 2);
		AMyAudioSubsystemActor* AudioSubsystemActor =
			Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
		if (AudioSubsystemActor) AudioSubsystemActor->PlaySFX1("keyTaken");
	}
	if (KeyMesh) {
		KeyMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		KeyMesh->SetAngularDamping(5.f);	
	}
}

void AKeyBeach::DropObject() {
	if (!KeyMesh) return;
	KeyMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	KeyMesh->SetAngularDamping(0.05f);
}



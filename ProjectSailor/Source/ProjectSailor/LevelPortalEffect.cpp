// Property of DaPaRy Games


#include "LevelPortalEffect.h"
#include "NiagaraComponent.h"
#include "ProjectSailorCharacter.h"
#include "Components/BoxComponent.h"

ALevelPortalEffect::ALevelPortalEffect()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	InternalNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("InternalNiagaraComponent"));
	InternalNiagaraComponent->SetupAttachment(RootComponent);

	ExternalNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ExternalNiagaraComponent"));
	ExternalNiagaraComponent->SetupAttachment(RootComponent);
	
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	TriggerBoxComponent->SetupAttachment(RootComponent);
	
	InternalNiagaraComponent->SetVisibility(false);
	InternalNiagaraComponent->SetAutoActivate(false);
	ExternalNiagaraComponent->SetVisibility(false);
	ExternalNiagaraComponent->SetAutoActivate(false);

}

void ALevelPortalEffect::BeginPlay()
{
	Super::BeginPlay();
	if (NiagaraSystem) {
		InternalNiagaraComponent->SetAsset(NiagaraSystem);
		ExternalNiagaraComponent->SetAsset(NiagaraSystem);
	}
	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ALevelPortalEffect::OnTriggerBoxOverlap);
}

void ALevelPortalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelPortalEffect::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (AProjectSailorCharacter* Player = Cast<AProjectSailorCharacter>(OtherActor)) {
		InternalNiagaraComponent->SetVisibility(true);
		InternalNiagaraComponent->Activate();
		ExternalNiagaraComponent->SetVisibility(true);
		ExternalNiagaraComponent->Activate();
	}
}


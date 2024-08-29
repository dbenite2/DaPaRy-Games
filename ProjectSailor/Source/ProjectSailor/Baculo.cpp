// Property of DaPaRy Games


#include "Baculo.h"

#include "HeadMountedDisplayTypes.h"
#include "NiagaraComponent.h"
#include "ProjectSailorCharacter.h"
#include "SailorController.h"

ABaculo::ABaculo()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	baculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	baculo->SetupAttachment(Root);

	Octopus = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Octopus Skeleton"));
	Octopus->SetupAttachment(baculo);

	ConnectionParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Grab Effect"));
	ConnectionParticleComponent->SetupAttachment(Octopus);

	ConnectionParticleComponent->SetVisibility(false);
	ConnectionParticleComponent->SetAutoActivate(false);
}

void ABaculo::BeginPlay() {
	Super::BeginPlay();
	Player = Cast<AProjectSailorCharacter>(GetOwner());
	
}

void ABaculo::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Player) {
		if (Player->IsHolding) {
			ConnectionParticleComponent->SetVisibility(true);
			ConnectionParticleComponent->Activate();
		} else {
			ConnectionParticleComponent->SetVisibility(false);
			ConnectionParticleComponent->Deactivate();
		}
	}
}

void ABaculo::PlayAnimMontage() {
	
	if(!GrabAnimMontage) return;
	
	if (UAnimInstance* AnimInstance = Octopus->GetAnimInstance()) {
		AnimInstance->Montage_Play(GrabAnimMontage);
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ThisClass::OnMontageEnded);
		AnimInstance->Montage_SetEndDelegate(EndDelegate);
	}
}

void ABaculo::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) {
}


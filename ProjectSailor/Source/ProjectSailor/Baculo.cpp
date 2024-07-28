// Property of DaPaRy Games


#include "Baculo.h"

// Sets default values
ABaculo::ABaculo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	baculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	baculo->SetupAttachment(Root);

	Octopus = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Octopus Skeleton"));
	Octopus->SetupAttachment(baculo);
}

// Called when the game starts or when spawned
void ABaculo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaculo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


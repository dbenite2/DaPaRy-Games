// Property of DaPaRy Games


#include "Pickable_Crosier.h"

#include "MyAudioSubsystemActor.h"
#include "ProjectSailorCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SailorInstance.h"

APickable_Crosier::APickable_Crosier() {
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	baculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	baculo->SetupAttachment(Root);

	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(Root);
	TriggerZone->InitSphereRadius(300.0f);
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &APickable_Crosier::OnOverlapBegin);
}

void APickable_Crosier::BeginPlay() {
	Super::BeginPlay();
	
}

void APickable_Crosier::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APickable_Crosier::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
	USailorInstance* GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if(PlayerCharacter && GameManager) {
		PlayerCharacter->Crosier = this;
		PlayerCharacter->PlayCharacterMontage(Montage);
		GameManager->SetCurrentLevelStatus(CurrentLevelName, 1);
		AMyAudioSubsystemActor* AudioSubsystemActor =
			Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
		if (AudioSubsystemActor) {
			AudioSubsystemActor->PlaySFX1("drop");	
		}
	}
}

void APickable_Crosier::PickObject(AProjectSailorCharacter* PlayerCharacter) {
	if (!PlayerCharacter) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerCharacter->GetOwner();
	SpawnParams.Instigator = PlayerCharacter->GetInstigator();
			
	FVector SpawnLocation = PlayerCharacter->GetMesh()->GetSocketLocation(FName("WeaponSocket"));
	FRotator SpawnRotation = PlayerCharacter->GetMesh()->GetSocketRotation(FName("WeaponSocket"));
		
	baculoComponent = GetWorld()->SpawnActor<ABaculo>(baculoClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (baculoComponent) {
		baculoComponent->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("WeaponSocket"));
		PlayerCharacter->SetBaculoIsActive(true);
		PlayerCharacter->StaffComponent = baculoComponent;
		PlayerCharacter->StaffComponent->Player = PlayerCharacter;
		if (UUserWidget* PlayerCrosshairWidget = PlayerCharacter->CrosshairWidget) {
			PlayerCrosshairWidget->SetVisibility(ESlateVisibility::Visible);
		}
		Destroy();
	}
}

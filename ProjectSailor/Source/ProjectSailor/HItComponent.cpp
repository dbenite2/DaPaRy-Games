// Property of DaPaRy Games


#include "HItComponent.h"

#include "Baculo.h"
#include "ButtonSpawnActor.h"
#include "KeyBeach.h"
#include "MushroomButtonActor.h"
#include "MyAudioSubsystemActor.h"
#include "ObjectInteraction.h"
#include "Pickable_Object.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ICookInfo.h"

UHItComponent::UHItComponent() {

	PrimaryComponentTick.bCanEverTick = true;
}

void UHItComponent::BeginPlay() {
	Super::BeginPlay();
}

void UHItComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHItComponent::HitAbility(UCameraComponent* Camera, AActor* Player, ABulletVFXPlayerHit* bullet, APlayerController* PlayerController) {
	UWorld* World = GetWorld();
	
	if (!PlayerController) return;
	
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;

	// Get the screen center
	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenCenter(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);

	// Convert screen position to world position and direction
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection);
	
	FVector Start = PlayerController->PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = Start + WorldDirection * 1500.f;
	
	FCollisionQueryParams LineCollisionParams;
	LineCollisionParams.AddIgnoredActor(PlayerCharacter);
	
	FHitResult HitResult;	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,                      
	Start,                 
	LineTraceEnd,                   
	ECollisionChannel::ECC_Visibility, 
	FCollisionQueryParams(TEXT("Trace"), false, PlayerCharacter)
	);
	
	if(bHit) {

		if(AActor* HitObject = HitResult.GetActor()) {
			FTimerHandle HitTimerHandle;
			if (HitTimerHandle.IsValid()) {
			    GetWorld()->GetTimerManager().SetTimer(HitTimerHandle, [this, Camera, Player, HitObject]() {
                     if (HitObject->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass())) {
                         AMyAudioSubsystemActor* AudioSubsystemActor =
                            Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(),
                                AMyAudioSubsystemActor::StaticClass()));
        
                        if (AudioSubsystemActor) AudioSubsystemActor->PlaySFX2("tentaculo1");
                         
                         if(AKeyBeach* KeyBeachActor = Cast<AKeyBeach>(HitObject)) {
                             KeyBeachActor->Interact_Implementation();
                         }
                     }
                    
                     if (IIDamageable* DamageableActor = Cast<IIDamageable>(HitObject)) {
                         DamageableActor->TakeDamage();
                     }
                    
                     if(AMushroomButtonActor* MushroomButton = Cast<AMushroomButtonActor>(HitObject)) {
                         MushroomButton->SpawnMushroom();
                     }
                    
                     if(AButtonSpawnActor* SpawnActorButton = Cast<AButtonSpawnActor>(HitObject)) {
                         SpawnActorButton->SpawnActor();
                     }
                }, bullet->Lifetime, false);
			}
		}
	}
}


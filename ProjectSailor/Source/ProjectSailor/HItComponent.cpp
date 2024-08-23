// Property of DaPaRy Games


#include "HItComponent.h"

#include "Baculo.h"
#include "ButtonSpawnActor.h"
#include "KeyBeach.h"
#include "MyAudioSubsystemActor.h"
#include "ObjectInteraction.h"
#include "Pickable_Object.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ICookInfo.h"

UHItComponent::UHItComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}



void UHItComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHItComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHItComponent::HitAbility(UCameraComponent* Camera, AActor* Player, ABulletVFXPlayerHit* bullet, APlayerController* PlayerController) {
	UWorld* World = GetWorld();
	// Get the player controller
	if (!PlayerController) return;

	// Get the player character
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;

	// Get player's view point
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Get player's forward vector and location
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector StartLocation = PlayerCharacter->StaffComponent->Octopus->GetComponentLocation();

	// Adjust the start location to be a bit in front of the player and a bit higher in the Y axis
	// TODO: Set value as a parameter in class
	FVector LineTraceStart = StartLocation + ForwardVector * 100.f;

	// Define the end location of the raycast based on camera direction
	FVector LineTraceEnd = LineTraceStart + CameraRotation.Vector() * 1500.f; // Adjust this value as needed

	// Setup collision parameters
	FCollisionQueryParams LineCollisionParams;
	LineCollisionParams.AddIgnoredActor(PlayerCharacter);
	
	// Perform the raycast
	FHitResult HitResult;	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,                      
	LineTraceStart,                 
	LineTraceEnd,                   
	ECollisionChannel::ECC_Visibility, 
	FCollisionQueryParams(TEXT("Trace"), false, PlayerCharacter)
	);

	// DrawDebugLine(
	// GetWorld(),
	// LineTraceStart,
	// LineTraceEnd,
	// FColor::Red,
	// false,
	// 1.0f,
	// 0,
	// 1.0f
	// );

	if(bHit) {
		AActor* HitObject = HitResult.GetActor();

		if(HitObject) {
			// Agregar delay de lifeTime bullet
			FTimerHandle HitTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(HitTimerHandle, [this, Camera, Player, HitObject]() {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Object: %s"), *HitObject->GetName()));

				 // Check if the hit object implements the InteractionInterface
				 if (HitObject->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass())) {
					 //sound Hit
					 AMyAudioSubsystemActor* AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
					 AudioSubsystemActor->PlaySFX2("tentaculo1");
					 // Cast the HitObject to KeyBeach and call ActivateKeyPhysics if the cast is successful
					 AKeyBeach* KeyBeachActor = Cast<AKeyBeach>(HitObject);
					 if(KeyBeachActor) {
						 KeyBeachActor->Interact_Implementation();
					 }
				 }
				
				 IIDamageable* DamageableActor = Cast<IIDamageable>(HitObject);
				 if (DamageableActor) {
					 DamageableActor->TakeDamage();
				 }

				 AMushroomButtonActor* MushroomButton = Cast<AMushroomButtonActor>(HitObject);
				 if(MushroomButton) {
					 MushroomButton->SpawnMushroom();
				 }

				 AButtonSpawnActor* SpawnActorButton = Cast<AButtonSpawnActor>(HitObject);
				 if(SpawnActorButton) {
					 SpawnActorButton->SpawnActor();
				 }
		   }, bullet->Lifetime, false);
		}
	}
}


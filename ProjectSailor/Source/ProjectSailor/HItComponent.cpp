// Property of DaPaRy Games


#include "HItComponent.h"

#include "KeyBeach.h"
#include "ObjectInteraction.h"
#include "Pickable_Object.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ICookInfo.h"

// Sets default values for this component's properties
UHItComponent::UHItComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHItComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHItComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHItComponent::HitAbility(UCameraComponent* Camera, AActor* Player)
{
	UWorld* World = GetWorld();
	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());
	if (!PlayerController) return;

	// Get the player character
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;

	// Get player's view point
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Add a vertical offset to the camera location
	CameraLocation.Z += 50.f;

	// Define the spherecast parameters
	float SphereRadius = 100.f;
	FVector SphereCastStart = CameraLocation;
	FVector SphereCastEnd = SphereCastStart + CameraRotation.Vector() * 1000.f;

	// Setup collision parameters
	FCollisionQueryParams SphereCollisionParams;
	SphereCollisionParams.AddIgnoredActor(PlayerCharacter);

	// Perform the spherecast
	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), SphereCastStart, SphereCastEnd, SphereRadius, UEngineTypes::ConvertToTraceType(ECC_Pawn),
													   false, { PlayerCharacter }, EDrawDebugTrace::ForDuration, HitResult, true);

	if(bHit)
	{
		AActor* HitObject = HitResult.GetActor();

		if(HitObject)
		{
			// FRotator ObjectRotation = FRotationMatrix::MakeFromZ(End).Rotator();
			// FVector ObjetLocation = HitScore.Location;
			//
			// UClass* BP_Bullet = nullptr; //Aqui coger el BP de la bala que vamos a Spawnear
			// AActor* actor = nullptr; //Aqui el actor de la bala que spawneamos
			// FActorSpawnParameters SpawnParams;
			// SpawnParams.Owner = actor;
			//
			// AActor* SpawnedActor = World->SpawnActor<AActor>(BP_Bullet, ObjetLocation, ObjectRotation, SpawnParams);

			// if(SpawnedActor)
			// {
			// 	
			// }

			// Check if the hit object has an ObjectInteraction component
			UActorComponent* ObjectInteractionComponent = HitObject->GetComponentByClass(UObjectInteraction::StaticClass());
			if(ObjectInteractionComponent)
			{
				// Check if the hit object's name is "BP_KeyBeach"
				if(HitObject->GetName().Contains(TEXT("BP_KeyBeach")))
				{
					// Cast the HitObject to KeyBeach and call ActivateKeyPhysics if the cast is successful
					AKeyBeach* KeyBeachActor = Cast<AKeyBeach>(HitObject);
					if(KeyBeachActor)
					{
						KeyBeachActor->ActivateKeyPhysics();
					}
					
				}
			}
			
			IIDamageable* DamageableActor = Cast<IIDamageable>(HitObject);
			if (DamageableActor)
			{
				DamageableActor->TakeDamage();
			}
		}
	}
}


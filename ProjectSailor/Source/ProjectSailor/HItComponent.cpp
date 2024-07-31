// Property of DaPaRy Games


#include "HItComponent.h"

#include "KeyBeach.h"
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

	// Get player's forward vector and location
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	// Define the spherecast parameters
	float SphereRadius = 150.f;

	// Adjust the start location to be a bit in front of the player and a bit higher in the Y axis
	// TODO: Set value as a parameter in class
	FVector SphereCastStart = PlayerLocation  + ForwardVector*100.f + FVector(0.f,0 , 100.f);

	// Define the end location of the spherecast based on camera direction
	FVector SphereCastEnd = SphereCastStart + CameraRotation.Vector() * 1000.f; // Adjust this value as needed

	// Setup collision parameters
	FCollisionQueryParams SphereCollisionParams;
	SphereCollisionParams.AddIgnoredActor(PlayerCharacter);
	
	// Perform the spherecast
	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), SphereCastStart, SphereCastEnd, SphereRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),false,
		{ PlayerCharacter }, EDrawDebugTrace::ForDuration, HitResult, true);

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

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Object: %s"), *HitObject->GetName()));

			// Check if the hit object implements the InteractionInterface
			if (HitObject->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{
				
					// Cast the HitObject to KeyBeach and call ActivateKeyPhysics if the cast is successful
					AKeyBeach* KeyBeachActor = Cast<AKeyBeach>(HitObject);
					if(KeyBeachActor)
					{
						KeyBeachActor->Interact_Implementation();
					}
					
				
			}
			
			IIDamageable* DamageableActor = Cast<IIDamageable>(HitObject);
			if (DamageableActor)
			{
				DamageableActor->TakeDamage();
			}

			AMushroomButtonActor* MushroomButton = Cast<AMushroomButtonActor>(HitObject);
			if(MushroomButton)
			{
				MushroomButton->SpawnMushroom();
			}
		}
	}
}


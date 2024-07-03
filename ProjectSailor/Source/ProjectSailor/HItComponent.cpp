// Property of DaPaRy Games


#include "HItComponent.h"

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
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());

	// //gets a reference of Player proyecto
	auto* player = Cast<AProjectSailorCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//gets a reference of
	if (!PlayerController) return;

	//if the player exists we make a reference of cameraLocation and Rotation
	FVector CameraLocation;
	FRotator CameraRotation;

	//returns the point of the view of the player on the variables cameraLocation and rotation
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Add a vertical offset to the camera location
	CameraLocation.Z += 50.f;

	//calculate the end of the raycast and makes it unitary
	FVector RaycastEnd = CameraLocation + CameraRotation.Vector() * 3000;

	//create hitResult
	FHitResult HitResult;

	//creates the variable
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(player);

	// Define the type of collision that is pawn
	ECollisionChannel TraceChannel = ECC_Pawn;

	// Convert to a valid argument of the LineTraceSingle
	ETraceTypeQuery TraceTypeQuery1 = UEngineTypes::ConvertToTraceType(TraceChannel);

	//Make parameters of collision
	bool bHit = UKismetSystemLibrary::LineTraceSingle(World, CameraLocation, RaycastEnd, TraceTypeQuery1, true, { player }, EDrawDebugTrace::ForDuration, HitResult, true);

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
			
			IIDamageable* DamageableActor = Cast<IIDamageable>(HitObject);
			if (DamageableActor)
			{
				DamageableActor->TakeDamage(100.f);
			}
			

			
		}
	}
}


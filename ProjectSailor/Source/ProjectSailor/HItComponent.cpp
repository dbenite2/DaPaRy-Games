// Property of DaPaRy Games


#include "HItComponent.h"

#include "Pickable_Object.h"
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
	FVector Start = Camera->GetComponentRotation().RotateVector(Player->GetActorLocation());
	FVector End = Start + Camera->GetForwardVector() * 1000.f;

	bool bHit = UKismetSystemLibrary::LineTraceSingle(World, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, HitScore, true,  FLinearColor::Red, FLinearColor::Green);

	if(bHit)
	{
		UPrimitiveComponent* HitObject = HitScore.GetComponent();

		if(HitObject)
		{
			FRotator ObjectRotation = FRotationMatrix::MakeFromZ(End).Rotator();
			FVector ObjetLocation = HitScore.Location;

			UClass* BP_Bullet = nullptr; //Aqui coger el BP de la bala que vamos a Spawnear
			AActor* actor = nullptr; //Aqui el actor de la bala que spawneamos
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = actor;
			
			AActor* SpawnedActor = World->SpawnActor<AActor>(BP_Bullet, ObjetLocation, ObjectRotation, SpawnParams);

			if(SpawnedActor)
			{
				if(HitObject->IsSimulatingPhysics())
				{
					if(HitObject->ComponentHasTag("Destructible"))
					{
						HitObject->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
					}
					else
					{
						HitObject->WakeRigidBody();
					}
				}
			}
		}
	}
}


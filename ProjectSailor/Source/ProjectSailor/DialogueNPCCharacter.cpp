// Property of DaPaRy Games


#include "DialogueNPCCharacter.h"


#include "DialogueNPCCharacter.h"
#include "ProjectSailorCharacter.h"


// Sets default values
ADialogueNPCCharacter::ADialogueNPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	// Create the trigger zone and attach it to the root component
	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->InitSphereRadius(300.0f);
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));

	// Bind the overlap event
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ADialogueNPCCharacter::OnOverlapBegin);
	// Bind the overlap event
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ADialogueNPCCharacter::OnOverlapEnd);
}

void ADialogueNPCCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is of class AProjectSailorCharacter
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		if (DialogueWidgetClass)
		{
			// Create the widget if it's not already created
			if (!DialogueWidget)
			{
				DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
			}
            
			// Add it to the viewport if it's valid
			if (DialogueWidget)
			{
				DialogueWidget->AddToViewport();
				DialogueWidget->UpdateText(FText::FromString(TEXT("Soy un aventurero")));
			}
		}
	}
}

void ADialogueNPCCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			if (DialogueWidget)
			{
				DialogueWidget->RemoveFromViewport();
				DialogueWidget = nullptr;
			}
		}
	}
	
}

// Called to bind functionality to input
void ADialogueNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


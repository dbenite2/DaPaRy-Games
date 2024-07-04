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
				SetWidget(true);
				DialogueWidget->UpdateText(DialogueTexts[CurrentTextIndex]);
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
				SetWidget(false);
			}
		}
	}
	
}

void ADialogueNPCCharacter::SetWidget(bool set)
{
	if(set)
	{
		DialogueWidget->AddToViewport();
	}
	else
	{
		//restart dialogue
		CurrentTextIndex = 0;
		if(DialogueWidget)
		{
			DialogueWidget->RemoveFromViewport();
			DialogueWidget = nullptr;
		}
		
	}
}

void ADialogueNPCCharacter::ChangeToNextText()
{
	if (DialogueTexts.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueTexts array is empty!"));
		return;
	}

	// Increment index
	CurrentTextIndex++;
	// Wrap around the index to stay within bounds
	CurrentTextIndex %= DialogueTexts.Num();

	
	// Update text on the widget
	if (DialogueWidget)
	{
		DialogueWidget->UpdateText(DialogueTexts[CurrentTextIndex]);
	}
}




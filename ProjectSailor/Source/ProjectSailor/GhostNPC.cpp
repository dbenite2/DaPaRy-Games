// Property of DaPaRy Games


#include "GhostNPC.h"

#include "InteractionComponent.h"
#include "ProjectSailorCharacter.h"

// Sets default values
AGhostNPC::AGhostNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->InitSphereRadius(300.0f);
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));

	// Bind the overlap event
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AGhostNPC::OnOverlapBegin);
	// Bind the overlap event
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AGhostNPC::OnOverlapEnd);
}

void AGhostNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is of class AProjectSailorCharacter
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		const FLevelStatus CurrentState = PlayerCharacter->GetLevelStatus();
		SetUpEventSubscription(PlayerCharacter);
		CurrentDialogSet.Empty();
		SetCurrentDialogSet(CurrentState);
		
		if (DialogueWidgetClass) {
			// Create the widget if it's not already created
			if (!DialogueWidget) {
				DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
				// Add it to the viewport if it's valid
				if (DialogueWidget && CurrentDialogSet.Num() > 0) {
					SetWidget(true);
					DialogueWidget->UpdateText(CurrentDialogSet[CurrentTextIndex]);
				}
			}
		}
	}
}

void AGhostNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			PlayerCharacter->InteractionComponent->OnInteract.RemoveDynamic(this, &AGhostNPC::ChangeToNextText);
			if (DialogueWidget) {
				SetWidget(false);
			}
		}
	}
	
}

void AGhostNPC::SetWidget(bool set)
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

void AGhostNPC::ChangeToNextText()
{
	if (CurrentDialogSet.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("DialogueTexts array is empty!"));
		return;
	}
	
	// Increment index
	CurrentTextIndex++;

	if (CurrentTextIndex >= CurrentDialogSet.Num()) {
		SetWidget(false);
		return;
	}
	// Wrap around the index to stay within bounds
	// CurrentTextIndex %= DialogueTextsSet1.Num();

	
	// Update text on the widget
	if (DialogueWidget) {
		DialogueWidget->UpdateText(CurrentDialogSet[CurrentTextIndex]);
	}
}

void AGhostNPC::SetCurrentDialogSet(FLevelStatus PlayerStatus) {
	if (PlayerStatus.bInitial) {
		if (Dialogs->ObjectsArray.IsValidIndex(0)) {
			CurrentDialogSet = Dialogs->ObjectsArray[0].Texts;
			return;
		}
	}
	if (PlayerStatus.bGoal1Complete && !PlayerStatus.bGoal2Complete) {
		if (Dialogs->ObjectsArray.IsValidIndex(1)) {
			CurrentDialogSet = Dialogs->ObjectsArray[1].Texts;
			return;
		}
	}
	if (PlayerStatus.bGoal2Complete) {
		if (Dialogs->ObjectsArray.IsValidIndex(2)) {
			CurrentDialogSet = Dialogs->ObjectsArray[2].Texts;
		}
	}
}

void AGhostNPC::SetUpEventSubscription(AProjectSailorCharacter* Player) {
	Player->InteractionComponent->OnInteract.AddUniqueDynamic(this, &AGhostNPC::ChangeToNextText);
}

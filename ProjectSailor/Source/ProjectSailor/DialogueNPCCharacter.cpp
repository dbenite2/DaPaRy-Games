// Property of DaPaRy Games


#include "DialogueNPCCharacter.h"

#include "DialogDataAsset.h"
#include "ProjectSailorCharacter.h"
#include "InteractionComponent.h"
#include "Kismet/GameplayStatics.h"

ADialogueNPCCharacter::ADialogueNPCCharacter() {
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the trigger zone and attach it to the root component
	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->InitSphereRadius(300.0f);
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
	
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ADialogueNPCCharacter::OnOverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ADialogueNPCCharacter::OnOverlapEnd);
	
}

void ADialogueNPCCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	// Check if the overlapping actor is of class AProjectSailorCharacter
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
	USailorInstance* GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
	if (PlayerCharacter && GameManager) {
		FString CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		const FLevelStatus CurrentState = GameManager->GetCurrentLevelStatus(CurrentLevelName);
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

void ADialogueNPCCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this)) {
		AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
		if (PlayerCharacter) {
			PlayerCharacter->InteractionComponent->OnInteract.RemoveDynamic(this, &ADialogueNPCCharacter::ChangeToNextText);
			if (DialogueWidget) {
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
			DialogueWidget->RemoveFromParent();
			DialogueWidget = nullptr;
		}
		
	}
}

void ADialogueNPCCharacter::ChangeToNextText() {
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

void ADialogueNPCCharacter::SetCurrentDialogSet(FLevelStatus PlayerStatus) {
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

void ADialogueNPCCharacter::SetUpEventSubscription(AProjectSailorCharacter* Player) {
	Player->InteractionComponent->OnInteract.AddUniqueDynamic(this, &ADialogueNPCCharacter::ChangeToNextText);
}


// Property of DaPaRy Games


#include "GhostNPC.h"

#include "InteractionComponent.h"
#include "ProjectSailorCharacter.h"
#include "SailorInstance.h"
#include "Kismet/GameplayStatics.h"

AGhostNPC::AGhostNPC() {
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->InitSphereRadius(300.0f);
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
	
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AGhostNPC::OnOverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AGhostNPC::OnOverlapEnd);
}

void AGhostNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor);
	USailorInstance* GameManager = Cast<USailorInstance>(UGameplayStatics::GetGameInstance(this));
	if (PlayerCharacter) {
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

void AGhostNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this)) {
		if (AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(OtherActor)) {
			PlayerCharacter->InteractionComponent->OnInteract.RemoveDynamic(this, &AGhostNPC::ChangeToNextText);
			if (DialogueWidget) {
				SetWidget(false);
			}
		}
	}
}

void AGhostNPC::SetWidget(bool set) {
	if(set) {
		DialogueWidget->AddToViewport();
	} else {
		CurrentTextIndex = 0;
		if(DialogueWidget) {
			DialogueWidget->RemoveFromParent();
			DialogueWidget = nullptr;
		}
	}
}

void AGhostNPC::ChangeToNextText() {
	if (CurrentDialogSet.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("DialogueTexts array is empty!"));
		return;
	}
	
	CurrentTextIndex++;

	if (CurrentTextIndex >= CurrentDialogSet.Num()) {
		SetWidget(false);
		return;
	}
	
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

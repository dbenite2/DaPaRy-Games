

#include "DialogueComponentNPC.h"

UDialogueComponentNPC::UDialogueComponentNPC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDialogueComponentNPC::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDialogueComponentNPC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(accessFunctionality)
	{
		//MAKE FUNCTIONALITY
		UE_LOG(LogTemp, Warning, TEXT("Interact with NPC DONE!"));
	}
}

void UDialogueComponentNPC::ActivateObject()
{
	accessFunctionality= true;
}

void UDialogueComponentNPC::Interact_Implementation()
{
	IInteractionInterface::Interact_Implementation();
	ActivateObject();
}

bool UDialogueComponentNPC::CanInteract_Implementation()
{
	return canMakeAction;
}

//returns the image initialized on the editor
UTexture2D* UDialogueComponentNPC::GetObjectImage_Implementation()
{
	
	return ObjectImage;
}


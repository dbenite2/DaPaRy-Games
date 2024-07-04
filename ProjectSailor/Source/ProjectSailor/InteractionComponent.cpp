
#include "InteractionComponent.h"
#include "DialogueComponentNPC.h"
#include "DialogueNPCCharacter.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    //reference to world
	World = GetWorld();
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	StartInterface();
	// TODO widget->SetVisibility(ESlateVisibility::Hidden);
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}




void UInteractionComponent::PerformRaycast()
{
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

    if (bHit)
    {
        // Get the actor that was hit by the spherecast
        AActor* HitActor = HitResult.GetActor();

        // Check if it's an ADialogueNPCCharacter
        ADialogueNPCCharacter* DialogueNPC = Cast<ADialogueNPCCharacter>(HitActor);
        if (DialogueNPC)
        {
            DialogueNPC->ChangeToNextText();
        }

        // Perform object interaction if E key is pressed
        if (pressedE)
        {
            UObjectInteraction* ObjectInteraction = Cast<UObjectInteraction>(HitActor->GetComponentByClass(UObjectInteraction::StaticClass()));
            if (ObjectInteraction)
            {
                InteractObject(ObjectInteraction);
            }
            pressedE = false;
        }
    }
    else
    {
        // Handle visibility or any other logic when no object is hit
    }
}

void UInteractionComponent::InteractNPC(UDialogueComponentNPC* dialogue)
{

		if(dialogue&& dialogue->CanInteract_Implementation())
		{
			dialogue->ActivateObject();
			dialogue->Interact_Implementation();
		}
}

void UInteractionComponent::InteractObject(UObjectInteraction* object)
{
	if (object && object->CanInteract_Implementation())
	{
			object->ActivateObject();
			object->Interact_Implementation();
	}
}

void UInteractionComponent::PressedE()
{
	pressedE = true;
}


void UInteractionComponent::StartInterface()
{
	//TODO add widget canvas
	// if(widgetTemplate)
	// {
	// 	auto * PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());
	// 	widget = CreateWidget<UInteractWidget>(PlayerController, widgetTemplate);
	// 	widget-> AddToViewport();
	// 	
	// }
}

void UInteractionComponent::UpdateImageOfCanvas(UTexture2D* NewImage)
{
	//we access to the widget or canvas and the script that is connect to their BP, interactWidget
	//where the image to change is located
	//TODO if (widget)
	// {
	// 	//access to canvas and his method passing as a parameter the image we want to change
	// 	widget->UpdateObjectImage(NewImage);
	// 	widget->SetVisibility(ESlateVisibility::Visible);
	// }
}




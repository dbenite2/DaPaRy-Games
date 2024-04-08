// Fill out your copyright notice in the Description page of Project Settings.
#include "InteractionComponent.h"
#include "InteractionInterface.h"
#include "DialogueComponentNPC.h"
#include "ProjectSailorCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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
	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//calls all the time to perform raycast
	
	// ...
}




void UInteractionComponent::PerformRaycast()
{
	//gets a reference of player
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

	//if raycast hit
	if (bHit)
	{
		//the actor that has hit the raycast
		AActor* HitActor = HitResult.GetActor();

		UDialogueComponentNPC* DialogueComponent = Cast<UDialogueComponentNPC>(HitActor->GetComponentByClass(UDialogueComponentNPC::StaticClass()));
		if (DialogueComponent)
		{
			// TODO widget->SetVisibility(ESlateVisibility::Visible);

			// control if the key E is pressed
			if (pressedE)
			{
				//interact with HitResult
				InteractNPC(DialogueComponent);
				pressedE = false;
			}
		}

		UObjectInteraction* object = Cast<UObjectInteraction>(HitActor->GetComponentByClass(UObjectInteraction::StaticClass()));
		if (object)
		{
			// TODO widget->SetVisibility(ESlateVisibility::Visible);

			// control if the key E is pressed
			if (pressedE)
			{
				//interact with HitResult
				InteractObject(object);
				pressedE = false;
			}
		}
	}
	else
	{
		// TODO widget->SetVisibility(ESlateVisibility::Hidden);
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




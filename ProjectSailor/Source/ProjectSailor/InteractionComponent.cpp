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
	// widget->SetVisibility(ESlateVisibility::Hidden);
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

	// Definir el tipo de traza como ECC_Pawn directamente
	ECollisionChannel TraceChannel = ECC_Pawn;

	// Convertir el tipo de traza a ETraceTypeQuery
	ETraceTypeQuery TraceTypeQuery1 = UEngineTypes::ConvertToTraceType(TraceChannel);

	// Realizar el trazado de línea con el tipo de traza y los parámetros de colisión
	bool bHit = UKismetSystemLibrary::LineTraceSingle(World, CameraLocation, RaycastEnd, TraceTypeQuery1, true, { player }, EDrawDebugTrace::ForDuration, HitResult, true);

	//si ha golpeado el raycast
	if (bHit)
	{
		//vemos el actor al que ha golpeado el raycast
		AActor* HitActor = HitResult.GetActor();

		UDialogueComponentNPC* DialogueComponent = Cast<UDialogueComponentNPC>(HitActor->GetComponentByClass(UDialogueComponentNPC::StaticClass()));
		if (DialogueComponent)
		{
			// widget->SetVisibility(ESlateVisibility::Visible);
			// control if the key E is pressed
			if (pressedE)
			{
				//interact with HitResult
				Interact(DialogueComponent);
				pressedE = false;
			}
		}
	}
	else
	{
		// widget->SetVisibility(ESlateVisibility::Hidden);
	}
		
	
	
	
    
}

void UInteractionComponent::Interact(UDialogueComponentNPC* dialogue)
{
	if (dialogue)
	{
		if(dialogue->CanInteract_Implementation())
		{
			dialogue->ActivateObject();
			dialogue->Interact_Implementation();
		}
	}
}

void UInteractionComponent::PressedE()
{
	pressedE = true;
}


void UInteractionComponent::StartInterface()
{
	//add widget canvas
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
	// if (widget)
	// {
	// 	//access to canvas and his method passing as a parameter the image we want to change
	// 	widget->UpdateObjectImage(NewImage);
	// 	widget->SetVisibility(ESlateVisibility::Visible);
	// }
}





#include "InteractionComponent.h"
#include "DialogueNPCCharacter.h"
#include "ProjectSailorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

UInteractionComponent::UInteractionComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	World = GetWorld();
}

void UInteractionComponent::BeginPlay() {
	Super::BeginPlay();
	StartInterface();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::PerformRaycast() {

	OnInteract.Broadcast();
	
    APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());
    if (!PlayerController) return;
	
    AProjectSailorCharacter* PlayerCharacter = Cast<AProjectSailorCharacter>(PlayerController->GetPawn());
    if (!PlayerCharacter) return;
	
    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	
    float SphereRadius = 100.f;

	FVector SphereCastStart = PlayerLocation  + ForwardVector*100.f + FVector(0.f,0 , 100.f);
	
	FVector SphereCastEnd = SphereCastStart + CameraRotation.Vector() * 1000.f;
	
    FCollisionQueryParams SphereCollisionParams;
    SphereCollisionParams.AddIgnoredActor(PlayerCharacter);
	
    FHitResult HitResult;
    bool bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), SphereCastStart, SphereCastEnd, SphereRadius,
    	UEngineTypes::ConvertToTraceType(ECC_Pawn),
    	false, { PlayerCharacter }, EDrawDebugTrace::None, HitResult, true);

    if (bHit) {
        AActor* HitActor = HitResult.GetActor();
    	
        if (pressedE) {
            UObjectInteraction* ObjectInteraction = Cast<UObjectInteraction>(HitActor->GetComponentByClass(UObjectInteraction::StaticClass()));
            if (ObjectInteraction) {
                InteractObject(ObjectInteraction);
            }
            pressedE = false;
        }
    }
}

void UInteractionComponent::InteractObject(UObjectInteraction* object) {
	if (object && object->CanInteract_Implementation()) {
			object->ActivateObject();
			object->Interact_Implementation();
	}
}

void UInteractionComponent::SetEKeyPressed(bool Value) {
	pressedE = Value;
}


void UInteractionComponent::StartInterface() {
	// TODO: add widget canvas
}

void UInteractionComponent::UpdateImageOfCanvas(UTexture2D* NewImage) {
	// TODO: IMPLEMENT CANVAS IMAGE
}

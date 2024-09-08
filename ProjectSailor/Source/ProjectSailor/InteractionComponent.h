
#pragma once

#include "CoreMinimal.h"
#include "ObjectInteraction.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

/**
 * Handles interactive functionalities for actors in the game. It manages
 * interaction logic, including raycasting to detect interactable objects and triggering interactions.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UInteractionComponent : public UActorComponent {
    GENERATED_BODY()

    UPROPERTY()
    UWorld* World{ nullptr };

    UPROPERTY() bool pressedE = false;
    
    UFUNCTION()
    void StartInterface();
    
    UFUNCTION()
    void UpdateImageOfCanvas(UTexture2D* NewImage);

    UFUNCTION() void InteractObject(UObjectInteraction* object);
    
protected:
    virtual void BeginPlay() override;

public:
    
    UInteractionComponent();
    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    UFUNCTION()
    void PerformRaycast();

    UPROPERTY()
    FOnInteract OnInteract;

    UFUNCTION()
    void SetEKeyPressed(bool Value);
    
};


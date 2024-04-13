
#pragma once

#include "CoreMinimal.h"
#include "ObjectInteraction.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSAILOR_API UInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UInteractionComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // TODO UPROPERTY(EditDefaultsOnly, Category= "Interaction") TSubclassOf<UInteractWidget> widgetTemplate;
    // TODO UPROPERTY()UInteractWidget *widget = nullptr;



public:	
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    UFUNCTION() void PerformRaycast();
private:
    UWorld* World{ nullptr };
   
    UFUNCTION() void InteractNPC(UDialogueComponentNPC* npc);

    UFUNCTION() void InteractObject(UObjectInteraction* object);

    UPROPERTY() bool pressedE = false;
    

    
    

public:

    //auxiliarMethods
    UFUNCTION() void PressedE();

private:
    UFUNCTION()
    void StartInterface();
    UFUNCTION()
    void UpdateImageOfCanvas(UTexture2D* NewImage);
};


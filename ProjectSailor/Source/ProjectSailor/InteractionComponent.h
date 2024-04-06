// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// #include "InteractionInterface.h"
// #include "InteractWidget.h"
// #include "MaterialSphere.h"
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

    // UPROPERTY(EditDefaultsOnly, Category= "Interaction") TSubclassOf<UInteractWidget> widgetTemplate;
    // UPROPERTY()UInteractWidget *widget = nullptr;



public:	
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    UFUNCTION() void PerformRaycast();
private:
    UWorld* World{ nullptr };
   
    UFUNCTION() void Interact(UDialogueComponentNPC* dialogue);

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


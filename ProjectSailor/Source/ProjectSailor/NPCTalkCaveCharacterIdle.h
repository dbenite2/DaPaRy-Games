// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCTalkCaveCharacterIdle.generated.h"

UCLASS()
class PROJECTSAILOR_API ANPCTalkCaveCharacterIdle : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCTalkCaveCharacterIdle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AnimationMontage;
};

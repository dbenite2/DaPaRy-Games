// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCTalkCaveCharacterIdle.generated.h"
/**
 * Defines a non-playable character (NPC) in the game, specifically designed
 * for idle interactions within cave environments in the ProjectSailor game. This class extends from ACharacter.
 */


UCLASS()
class PROJECTSAILOR_API ANPCTalkCaveCharacterIdle : public ACharacter {
	GENERATED_BODY()

public:
	ANPCTalkCaveCharacterIdle();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AnimationMontage;
};

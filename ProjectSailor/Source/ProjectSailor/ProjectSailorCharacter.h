// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Baculo.h"
#include "HItComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Pickable_Object.h"
#include "ProjectSailorCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT(BlueprintType)
struct FLevelStatus {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInitial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGoal1Complete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGoal2Complete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGoal3Complete;

	FLevelStatus() {
		bInitial = true;
		bGoal1Complete = false;
		bGoal2Complete = false;
		bGoal3Complete = false;
	}
	
};

UCLASS(config=Game)
class AProjectSailorCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Look Interaction or Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrapAndDrag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HitAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuInput;
	

public:
	AProjectSailorCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY()
	bool IsGrabbingObject = false;

	UPROPERTY()
	FHitResult HitScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY()
	bool IsHolding = false;

	UPROPERTY()
	bool HaveKeyBeach = false;

	UFUNCTION()
	bool GetHaveKeyBeach();

	UFUNCTION()
	void SetHaveKeyBeach(bool Value);

	UFUNCTION()
	void SetBaculoIsActive(bool Value);

	UFUNCTION()
	bool GetBaculoIsActive();

	UPROPERTY()
	APickable_Object* GrabbedObject = nullptr;

	UPROPERTY()
	UPrimitiveComponent* ObjectComponent;

	UPROPERTY()
	UHItComponent* hitComponent;

	UFUNCTION()
	FLevelStatus GetLevelStatus();

private:
	UPROPERTY()
	bool baculoIsActive{false};
	
	UFUNCTION()
	void InteractMethod();

	UFUNCTION()
	void GrapAndDragMethodPress();

	UFUNCTION()
	void HitComponentAbility();

	UPROPERTY()
	FLevelStatus LevelStatus;
	
};


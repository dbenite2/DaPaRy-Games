// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HItComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Pickable_Object.h"
#include "Blueprint/UserWidget.h"
#include "ProjectSailorCharacter.generated.h"

class UNiagaraSystem;
class ABaculo;
class APickable_Crosier;
class UMovementComponent;
class UInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AMyAudioSubsystemActor;
class ABulletVFXPlayerHit;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

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

	UPROPERTY(BlueprintReadOnly)
	bool IsHolding = false;
	
	UPROPERTY()
	bool HaveKeyBeach = false;

	UFUNCTION()
	bool GetHaveKeyBeach();

	UFUNCTION()
	void SetHaveKeyBeach(bool Value);

	UFUNCTION()
	void SetBaculoIsActive(bool Value);

	UFUNCTION(BlueprintCallable)
	bool GetBaculoIsActive();

	UPROPERTY()
	APickable_Object* GrabbedObject{nullptr};

	UPROPERTY()
	AKeyBeach* Key{nullptr};

	UPROPERTY()
	UPrimitiveComponent* ObjectComponent;

	UPROPERTY()
	UHItComponent* hitComponent;

	UPROPERTY()
	UInteractionComponent* InteractionComponent;

	UPROPERTY(BlueprintReadWrite)
	APickable_Crosier* Crosier{nullptr};

	UPROPERTY(BlueprintReadWrite)
	bool bIsJumping{false};

	void PlayCharacterMontage(UAnimMontage* MontageToPlay);

	UPROPERTY(BlueprintReadOnly)
	FVector LimbPosition;

	UPROPERTY(EditDefaultsOnly)
	ABaculo* StaffComponent{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UNiagaraSystem* GrabParticleSystem{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UNiagaraSystem* HitParticleSystem{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<ABulletVFXPlayerHit> BulletClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector positionBaculoCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY()
	UUserWidget* CrosshairWidget{nullptr};
	
	UFUNCTION()
	void CustomJumpingEvent();

	UFUNCTION()
	void CustomStopJumpingEvent();

	UFUNCTION()
	UCharacterMovementComponent* GetMovRef() const {return MoveCompRef;}

private:

	UPROPERTY()
	float timerToFinishCinematic = 10.0f;

	UFUNCTION()
	void StartLevel();
	
	UPROPERTY()
	bool baculoIsActive{false};
	
	UFUNCTION()
	void InteractMethod();

	UFUNCTION()
	void GrapAndDragMethodPress();

	UFUNCTION()
	void HitComponentAbility();

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AnimationMontage;

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY()
	UCharacterMovementComponent* MoveCompRef{nullptr};
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaculo> StaffClass;

	void CheckLevelAndAttachStaff();
	
};


// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectSailorCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractionComponent.h"
#include "MyAudioSubsystemActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "SailorController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectSailorCharacter

AProjectSailorCharacter::AProjectSailorCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	hitComponent = CreateDefaultSubobject<UHItComponent>(TEXT("HitComponent"));

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	
}

void AProjectSailorCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	SetActorTickEnabled(true);
	
	CheckLevelAndAttachStaff();

	MoveCompRef = GetCharacterMovement();
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	PlayCharacterMontage(AnimationMontage);
}

void AProjectSailorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(ObjectComponent)
	{
		FVector ActorLocation = StaffComponent->Octopus->GetComponentLocation();
		FVector CameraforwardVector = GetFollowCamera()->GetForwardVector() * 300.f;
		
		PhysicsHandle->SetTargetLocation(ActorLocation + CameraforwardVector);
		ObjectComponent->SetRelativeRotation(GetFollowCamera()->GetComponentRotation());
	}

	//if hit partycle system is ready
	if(HitParticleSystem_Cascade)
	{
	}
}

bool AProjectSailorCharacter::GetHaveKeyBeach() {
	return HaveKeyBeach;
}

void AProjectSailorCharacter::SetHaveKeyBeach(bool Value) {
	HaveKeyBeach = Value;
}

bool AProjectSailorCharacter::GetBaculoIsActive() {
	return baculoIsActive;
}

void AProjectSailorCharacter::SetBaculoIsActive(bool Value) {
	baculoIsActive = Value;
}

void AProjectSailorCharacter::CustomJumpingEvent() {
	Jump();
	bIsJumping = true;
}

void AProjectSailorCharacter::CustomStopJumpingEvent() {
	StopJumping();
	bIsJumping = false;
}


void AProjectSailorCharacter::InteractMethod() {

	if (!InteractionComponent) {
		UE_LOG(LogTemp, Warning, TEXT("InteractionComponent not found!"));
		return;
	}
	
	InteractionComponent->SetEKeyPressed(true);
	InteractionComponent->PerformRaycast();
}

void AProjectSailorCharacter::GrapAndDragMethodPress() {
	if(baculoIsActive)
	{
		if(!IsHolding)
		{
			UWorld* World = GetWorld();
			FVector Start = StaffComponent->Octopus->GetComponentLocation();
			FVector End = Start + GetFollowCamera()->GetForwardVector() * 1500;
			
			StaffComponent->PlayAnimMontage();

			FHitResult HitResult;	
			bool bHit = World->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECollisionChannel::ECC_Pawn,
				FCollisionQueryParams(TEXT("Trace"), false, this)
			);
			
			if(bHit)
			{
				GrabbedObject = Cast<APickable_Object>(HitResult.GetActor());
				//sound grab
				AMyAudioSubsystemActor* AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
				AudioSubsystemActor->PlaySFX1("grab");
				if(GrabbedObject)
				{
					ObjectComponent = HitResult.GetComponent();
					GrabbedObject->PickedObject();
					PhysicsHandle->GrabComponentAtLocation(ObjectComponent, EName::None, ObjectComponent->GetComponentLocation());
					IsHolding = true;
				}
			}
		}
		else
		{
			//sound drop
			AMyAudioSubsystemActor* AudioSubsystemActor = Cast<AMyAudioSubsystemActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyAudioSubsystemActor::StaticClass()));
			AudioSubsystemActor->PlaySFX2("drop");
			ObjectComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
			ObjectComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			
			PhysicsHandle->ReleaseComponent();
			GrabbedObject->DropObject(); 
			GrabbedObject = nullptr;
			ObjectComponent = nullptr;
			IsHolding = false;
		}
	}

	if(HitParticleSystem)
	{
		if(!StaffComponent && baculoIsActive)
		{
			FVector Start = StaffComponent->Octopus->GetComponentLocation();
			FVector End = Start + GetFollowCamera()->GetForwardVector() * 1000;
			End.Z = End.Z + 100;
			
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(),
							HitParticleSystem,
							End,
							FRotator::ZeroRotator,
							FVector(1.0f)
						);

			if (NiagaraComponent)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [NiagaraComponent]()
				{
					NiagaraComponent->Deactivate();
					NiagaraComponent->DestroyComponent();
				}, 1.0f, false);
			}
		}
		
	}
}

void AProjectSailorCharacter::HitComponentAbility() {
	if(baculoIsActive)
	{
		StaffComponent->PlayAnimMontage();
		UCameraComponent* camera = GetFollowCamera();
		AActor* player = GetOwner();
		hitComponent->HitAbility(camera, player);

		if(HitParticleSystem)
		{
			FVector Start = StaffComponent->Octopus->GetComponentLocation();
			FVector End = Start + GetFollowCamera()->GetForwardVector() * 1000;
			End.Z = End.Z + 100;

			//niagara effect
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(),
							HitParticleSystem,
							End,
							FRotator::ZeroRotator,
							FVector(1.0f)
						);

			if (NiagaraComponent)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [NiagaraComponent]()
				{
					NiagaraComponent->Deactivate();
					NiagaraComponent->DestroyComponent();
				}, 1.0f, false); 
			}
		}

		
		if(HitParticleSystem_Cascade)
		{
			FVector Start = StaffComponent->Octopus->GetComponentLocation();
			FVector End = Start + GetFollowCamera()->GetForwardVector() * 1000;
			End.Z = End.Z + 100;
			
			//cascade effect
			UParticleSystemComponent* CascadeComponent = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				HitParticleSystem_Cascade,
				Start,
				FRotator::ZeroRotator,
				FVector(1.0f)
			);

			if (CascadeComponent)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [CascadeComponent]()
				{
					CascadeComponent->Deactivate();
					CascadeComponent->DestroyComponent();
				}, 1.0f, false);
			}
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectSailorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	ASailorController* PlayerController = Cast<ASailorController>(GetController());
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::CustomJumpingEvent);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::CustomStopJumpingEvent);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectSailorCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectSailorCharacter::Look);

		// Interaction
		EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Triggered, this, &AProjectSailorCharacter::InteractMethod);

		// Grap & Drag
		EnhancedInputComponent->BindAction(GrapAndDrag, ETriggerEvent::Triggered, this, &AProjectSailorCharacter::GrapAndDragMethodPress);

		EnhancedInputComponent->BindAction(HitAbility, ETriggerEvent::Triggered, this, &AProjectSailorCharacter::HitComponentAbility);

		EnhancedInputComponent->BindAction(PauseMenuInput, ETriggerEvent::Triggered, PlayerController, &ASailorController::ShowPauseMenu);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectSailorCharacter::Move(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectSailorCharacter::Look(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectSailorCharacter::PlayCharacterMontage(UAnimMontage* MontageToPlay) {
	if(!MontageToPlay) return;
	
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance()) {
		AnimInstance->Montage_Play(MontageToPlay);
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AProjectSailorCharacter::OnMontageEnded);
		AnimInstance->Montage_SetEndDelegate(EndDelegate);
		if (MoveCompRef) {
			MoveCompRef->DisableMovement();
		}
	}
}

void AProjectSailorCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) {
	if (!MoveCompRef) return;
	MoveCompRef->SetMovementMode(MOVE_Walking);
}

void AProjectSailorCharacter::CheckLevelAndAttachStaff() {
	FString CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (CurrentLevelName == FString("Level_beach_01")) return;
	if (!StaffClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetInstigator();
			
	FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("WeaponSocket"));
	FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("WeaponSocket"));
	StaffComponent = GetWorld()->SpawnActor<ABaculo>(StaffClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (StaffComponent != nullptr) {
		StaffComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("WeaponSocket"));
		SetBaculoIsActive(true);
		StaffComponent->Player = this;
	}
	AnimationMontage = nullptr;
}

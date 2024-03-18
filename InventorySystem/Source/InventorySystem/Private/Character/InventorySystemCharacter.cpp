// Copyright Epic Games, Inc. All Rights Reserved.

//game
#include "Character/InventorySystemCharacter.h"


//engine 
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DrawDebugHelpers.h"


AInventorySystemCharacter::AInventorySystemCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Interaction time and distance
	InteractionCheckFrequency = 0.1;
	InteractionCheckDistance = 300.f;

	//LineTrace start location 
	BaseEyeHeight = 74.f;

}

void AInventorySystemCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime > InteractionCheckFrequency))
	{
		PerformInteractionCheck();
	}
}


void AInventorySystemCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AInventorySystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInventorySystemCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInventorySystemCharacter::Look);
		
		//Interacting
		EnhancedInputComponent->BindAction(BeginInteractAction, ETriggerEvent::Triggered, this, &AInventorySystemCharacter::BeginInteract);
		EnhancedInputComponent->BindAction(EndInteractAction, ETriggerEvent::Triggered, this, &AInventorySystemCharacter::EndInteract);

	}

}

void AInventorySystemCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart {GetPawnViewLocation()};
	FVector TraceEnd {TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance)};

	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	if (LookDirection > 0 )
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 2.f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{
				//
				if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
				{
					FoundInteractable(TraceHit.GetActor());
					return;
				}

				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}
			}
		}

		NoInteractableFound();
	}
}

void AInventorySystemCharacter::FoundInteractable(AActor* NewInteractable)
{
	//The check ensures that the previous interaction doesn't interfere with the new one. 
	if (IsInteracting()) 
	{
		EndInteract();
	}

	//The check ensures that the previous interaction doesn't interfere with the new one.
	if (InteractionData.CurrentInteractable) 
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	TargetInteractable->BeginFocus();
}

void AInventorySystemCharacter::NoInteractableFound()
{
	//resetting timer from previous interaction
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable) 
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		// TODO : hide interaction widget on the HUD

		//resetting InteractableItem
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;

	}
}

void AInventorySystemCharacter::BeginInteract()
{
	//It's safe check to make sure nothing hasn't been changed since beginning interaction (making sure we're looking at the same thing)
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable) 
	{
		if (IsValid(TargetInteractable.GetObject())) 
		{
			TargetInteractable->BeginInteract();

			//handling the delay for interactions 
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{	
				//If there's no InteractionDuration, we call Interact immediately  
				Interact();
			}
			else 
			{
				//If there's InteractionDuration, we call Interact after certain delay that greater than 0.1f 
				GetWorldTimerManager().SetTimer (
					TimerHandle_Interaction,
					this,
					&AInventorySystemCharacter::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false
				);
			}
		}
	}
}

void AInventorySystemCharacter::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AInventorySystemCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		//
		TargetInteractable->Interact(this);
	}
}

void AInventorySystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
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

void AInventorySystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}





// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/InteractionInterface.h"
#include "InventorySystemCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AInventorySystemHUD;

//Info about the interaction process
USTRUCT()
struct FInteractionData 
{
	GENERATED_USTRUCT_BODY()
	
	FInteractionData() : 
		CurrentInteractable(nullptr), 
		LastInteractionCheckTime(0.f)
	{
	
	}

	//It's an interactable that has recently been found 
	UPROPERTY()
	AActor* CurrentInteractable;

	//It's a duration that defines how ofter you shoot a line trace to interact with interactable 
	UPROPERTY()
	float LastInteractionCheckTime;
};

UCLASS(config=Game)
class AInventorySystemCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================


	//==================================================================================
	// FUNCTIONS
	//==================================================================================
	
	AInventorySystemCharacter();
	virtual void Tick(float DeltaSeconds) override;


protected:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BeginInteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* EndInteractAction;

	//
	//Reference to the HUD
	UPROPERTY()
	AInventorySystemHUD* HUD;

	//It's what we hitting and processing throught the line trace. The target we're looking for
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	//Frequency shoot a line trace
	float InteractionCheckFrequency;

	//Distance that defines how far the line trace is going to shoot from the character
	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================
	
	//This function is called in Tick. It shoots line trace
	void PerformInteractionCheck();
	
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

	virtual void BeginPlay();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	
	//==================================================================================
	// Getters and Setters
	//==================================================================================

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }
};


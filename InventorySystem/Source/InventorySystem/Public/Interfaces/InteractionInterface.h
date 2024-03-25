// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"


class AInventorySystemCharacter;

UENUM()
enum class EInteractableType: uint8 
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	Device UMETA(DisplayName = "Device"), //Could be door, gate or window
	Toggle UMETA(DisplayName = "Toggle"), //Could be a button, a switch, anything that activates some functionality 
	Container UMETA(DisplayName = "Container")
};

USTRUCT()
struct FInteractableData 
{
	GENERATED_USTRUCT_BODY()

	FInteractableData() :
		InteractableType(EInteractableType::Pickup),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.f)
	{
	
	}

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	//it's used only for pickups
	UPROPERTY(EditInstanceOnly)
	int32 Quantity;

	//it's used things like doors, gates, valves, etc. that needs an interaction timer
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

//Interface Usage: for anything that inherits this interface it's going to get its own copy of interactable data to that instance.

class INVENTORYSYSTEM_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================
	
	FInteractableData InteractableData;
	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================
	//It's used for notification that you're focusing on an object but you haven't done anything with it
	virtual void BeginFocus();

	//It's used for notification that you're not focusing on an object anymore
	virtual void EndFocus();

	//It's used for time interactions (opening door by holding button, etc.). It establishes beginning of interaction
	virtual void BeginInteract();
	
	//It's used for time interactions (opening door by holding button, etc.). It establishes ending of interaction
	virtual void EndInteract();
	
	//The interaction with objects happens right here.
	virtual void Interact(AInventorySystemCharacter* PlayerCharacter) = 0;

	
};

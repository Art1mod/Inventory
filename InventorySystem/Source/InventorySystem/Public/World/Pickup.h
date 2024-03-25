// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Pickup.generated.h"


class UDataTable;
class UItemBase;

UCLASS()
class INVENTORYSYSTEM_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	APickup();

	//pull all neccesary info from database 
	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);

	//pull all neccesary info from already existing item reference 
	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	virtual void BeginFocus() override;
	virtual void EndFocus() override;

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

	//Don't need to override BeginInteract or EndInteract, because there is no special interaction for it for now 


protected:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	FName DesiredItemID;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
	UItemBase* ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(VisibleInstanceOnly, Category = "Pickup | Interaction")
	FInteractableData InstanceInteractableData;


	//==================================================================================
	// FUNCTIONS
	//==================================================================================
	
	virtual void BeginPlay() override;

	virtual void Interact(AInventorySystemCharacter* PlayerCharacter) override;
	
	//Easy way to update interaction card for the pickup anytime something changes
	void UpdateInteractableData();

	void TakePickup(const AInventorySystemCharacter* Taker);


public:

	//==================================================================================
	// Getters and Setters
	//==================================================================================

	FORCEINLINE UItemBase* GetItemData() { return ItemReference; }

};

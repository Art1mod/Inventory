// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"


/**
 * 
 */

class AInventorySystemCharacter;
class UInventoryComponent;

//this class is more of data class. It will be stored into Inventory
UCLASS()
class INVENTORYSYSTEM_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public: 

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================
	
	// TO DO
	//UPROPERTY()
	//UInventoryComponent* OwningInventory;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity; 

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ItemID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData ItemAssetData;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	UItemBase();

	//this function's used for when you add an item to the inventory,
	//you need a possibility to create a brand new item copy to avoid bugs
	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const ;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * ItemNumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; }

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == ItemNumericData.MaximumStackSize; }

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(AInventorySystemCharacter* Character);


protected:
	
	//
	//it used in InventoryComponent to compare items
	bool operator == (const FName& OtherID) const;
	

};

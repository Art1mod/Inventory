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

	UPROPERTY(VisibleAnywhere, Category = "Item Data", meta = (UIMin=1, UIMax=100))
	int32 Quantity; 

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ItemID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
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
	
	bool operator == (const FName& OtherID) const;
	

};

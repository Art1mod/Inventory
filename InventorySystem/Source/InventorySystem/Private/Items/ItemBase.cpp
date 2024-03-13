// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

UItemBase::UItemBase()
{

}

UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());
	
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemID = this->ItemID;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemNumericData = this->ItemNumericData;
	ItemCopy->ItemAssetData = this->ItemAssetData;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaximumStackSize : 1);
		
		// TO DO
		//if (OwningInventory)
		//{
		//	if (Quantity <= 0) 
		//	{
		//		OwningInventory->RemoveItem(this);
		//	}
		//}
		
	}


}

void UItemBase::Use(AInventorySystemCharacter* Character)
{
}

bool UItemBase::operator==(const FName& OtherID) const
{
	return ItemID == OtherID;	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	return nullptr;
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	return FItemAddResult();
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemIn)
{
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{
	return int32();
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}




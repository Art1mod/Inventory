// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No item added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "Partial amount of item added"),
	IAR_AllItemAdded UMETA(DisplayName = "All of item added")
};

USTRUCT()
struct FItemAddResult
{
	GENERATED_USTRUCT_BODY()

	FItemAddResult() :
		ActualAmountAdded(0),
		OperationResult(EItemAddResult::IAR_NoItemAdded),
		ResultMessage(FText::GetEmpty()) 
	{};

	//Actual amount that was added to the inventory 
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;

	//Item add operation state
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;

	// Info message that you can pass with the result
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	//Automating the procces of adding item for classes

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		
		return AddedNoneResult;
	};

	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText) 
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = ErrorText;

		return AddedPartialResult;
	};
	
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message) 
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllResult.ResultMessage = Message;

		return AddedAllResult;
	};
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================


	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	UInventoryComponent();
	
	//It does pointer comparisson to find matching item 
	UItemBase* FindMatchingItem(UItemBase* ItemIn) const;

	//It compares item IDs 
	UItemBase* FindNextItemByID(UItemBase* ItemIn) const;

	
	UItemBase* FindNextPartialStack(UItemBase* ItemIn) const;

	FItemAddResult HandleAddItem(UItemBase* InputItem);

	//This completely deletes item form the array
	void RemoveSingleInstanceOfItem(UItemBase* ItemIn);

	//This is used to move partial stack from the array 
	int32 RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove);

	void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit);

protected:

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================


	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	virtual void BeginPlay() override;
		
};

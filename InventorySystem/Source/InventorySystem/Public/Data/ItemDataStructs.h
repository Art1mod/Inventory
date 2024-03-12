#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "Shoddy"),
	Common UMETA(DisplayName = "Common"),
	Quality UMETA(DisplayName = "Quality"),
	Masterwork UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster")
};

//If there is a need to hide specific information in the (HUD) regarding the item, this enumeration allows us to collapse such details.
UENUM()
enum class EItemType : uint8 
{
	Weapon UMETA(DisplayName = "Weapon"),
	Spell UMETA(DisplayName = "Spell"),
	Armor UMETA(DisplayName = "Armor"),
	Shield UMETA(DisplayName = "Shield"),
	Consumable UMETA(DisplayName = "Consumable"),
	Quest UMETA(DisplayName = "Quest"),
	Mundane UMETA(DisplayName = "Mundane")
};

USTRUCT()
struct FItemStatistics 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float DamageValue;
	
	UPROPERTY(EditAnywhere)
	float ArmorRating;
	
	UPROPERTY(EditAnywhere)
	float RestorationAmount;
	
	UPROPERTY(EditAnywhere)
	float SellValue;

};

//It's important for the HUD
USTRUCT()
struct FItemTextData 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description;
	
	UPROPERTY(EditAnywhere)
	FText InteractionText;
	
	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT()
struct FItemNumericData 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float Weight;

	UPROPERTY(EditAnywhere)
	int32 MaximumStackSize;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	//TODO Sounds

	//  When you pick up an item, it makes sounds
	// UPROPERTY(EditAnywhere)
	// USoundCue* PickupSound;
	
	// When you drop an item, it makes sounds
	// UPROPERTY(EditAnywhere)
	// USoundCue* DropSound;
};

USTRUCT()
struct FItemData : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()

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
	
};
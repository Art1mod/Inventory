// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class AInventorySystemCharacter;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//We need this pointer to call DropItem() on the charecter
	UPROPERTY()
	AInventorySystemCharacter* PlayerCharacter;

protected:

};

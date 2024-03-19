// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventorySystemHUD.generated.h"


class UMainMenu;
class UInteractionWidget;
struct FInteractableData;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AInventorySystemHUD : public AHUD
{
	GENERATED_BODY()

public: 
	

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	//It's a control variable for the HUD
	bool bIsMenuVisible;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	AInventorySystemHUD();
	
	void DisplayMenu();
	void HideMenu();

	//It's called by other classes when you gonna look at an interactable
	void ShowInteractionWidget();

	//It's called by other classes when you gonna look away of an interactable
	void HideInteractionWidget();

	void UpdateInteractionWidget(const FInteractableData* InteractableData);

protected:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================
	
	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	
	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	void BeginPlay() override;
};

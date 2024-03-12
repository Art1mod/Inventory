// Copyright Epic Games, Inc. All Rights Reserved.

#include "Framework/InventorySystemGameMode.h"
#include "Character/InventorySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventorySystemGameMode::AInventorySystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/InventorySystem/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

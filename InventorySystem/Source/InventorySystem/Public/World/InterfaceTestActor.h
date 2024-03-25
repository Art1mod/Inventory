// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InterfaceTestActor.generated.h"

UCLASS()
class INVENTORYSYSTEM_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	

	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================


	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	AInterfaceTestActor();
	virtual void Tick(float DeltaTime) override;

protected:
	
	//==================================================================================
	// PROPERTIES & VARIABLES
	//==================================================================================

	UPROPERTY(EditAnywhere, Category = "Test Actor")
	UStaticMeshComponent* Mesh;

	//Just for testing widget functionality 
	UPROPERTY(EditInstanceOnly, Category = "Test Actor")
	FInteractableData InstanceInteractableData;

	//==================================================================================
	// FUNCTIONS
	//==================================================================================

	virtual void BeginPlay() override;	

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;

	virtual void Interact(AInventorySystemCharacter* PlayerCharacter) override;



};

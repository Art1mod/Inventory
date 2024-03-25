// Fill out your copyright notice in the Description page of Project Settings.


#include "World/InterfaceTestActor.h"

// Sets default values
AInterfaceTestActor::AInterfaceTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

void AInterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();

	//setting it that way we provide info about interactable in the editor and set its c++ representation after it 
	InteractableData = InstanceInteractableData;

}

void AInterfaceTestActor::BeginFocus()
{
	if (Mesh) 
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInterfaceTestActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AInterfaceTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginInteract override on InterfaceTestActor is called"))
}

void AInterfaceTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("EndInteract override on InterfaceTestActor is called"))
}

void AInterfaceTestActor::Interact(AInventorySystemCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact override on InterfaceTestActor is called"))
}



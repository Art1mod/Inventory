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

}

void AInterfaceTestActor::BeginFocus()
{

}

void AInterfaceTestActor::EndFocus()
{

}

void AInterfaceTestActor::BeginInteract()
{

}

void AInterfaceTestActor::EndInteract()
{

}

void AInterfaceTestActor::Interact()
{

}



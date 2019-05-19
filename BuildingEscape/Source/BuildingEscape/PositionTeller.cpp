// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionTeller.h"
#include "BuildingEscape.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionTeller::UPositionTeller()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPositionTeller::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Hello there %s"), *ObjectName);
	
}


// Called every frame
void UPositionTeller::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


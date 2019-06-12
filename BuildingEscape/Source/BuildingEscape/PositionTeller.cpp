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
	/// ^^^ Find the owner and then Get its name ^^^

	FString ObjectPosition = GetOwner()->GetTransform().GetLocation().ToString();            
	/// ^^^  Alternate way : GetOwner()->GetActorLocation().ToString();  ^^^
	/// GetTransform gives us the three Trasnforms of unreal (location,rotation and scale).
	
	UE_LOG(LogTemp, Warning, TEXT("Hello there %s at %s"), *ObjectName, *ObjectPosition);

}


// Called every frame
void UPositionTeller::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


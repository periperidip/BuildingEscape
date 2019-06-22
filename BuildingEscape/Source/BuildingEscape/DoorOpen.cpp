 // Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "BuildingEscape.h"
#include "Components/PrimitiveComponent.h"


#define OUT


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();  /// This will set our actor to our default pawn itself
																		 /// This is a Top->Bottom Approach.We first find the World that has controller
																		 /// Then we find the actor/pawn held by the controller.
}

void UDoorOpen::OpenDoor()
{
	/*Owner = GetOwner();                                                  ///<- The door here is the owner
    FRotator NewRotation = FRotator(0.0f,OpenAngle, 0.0f);
    Owner->SetActorRotation(NewRotation);*/

	OnOpenRequest.Broadcast();

}

void UDoorOpen::CloseDoor()
{
	/*Owner = GetOwner();
	FRotator NewRotator = FRotator(0.f, 0.f, 0.f);
    Owner->SetActorRotation(NewRotator);*/
	OnCloseRequest.Broadcast();
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{OpenDoor();}

	else
	{CloseDoor();}
}

float UDoorOpen::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> ActorsOverlappingTrigger;
	PressurePlate->GetOverlappingActors(OUT ActorsOverlappingTrigger);

	for (auto* i : ActorsOverlappingTrigger)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *(i->GetName()));
		TotalMass += i->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}


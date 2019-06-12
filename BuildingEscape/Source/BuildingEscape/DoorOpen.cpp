 // Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "BuildingEscape.h"



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
	Owner = GetOwner();                                                  ///<- The door here is the owner
    FRotator NewRotation = FRotator(0.0f,OpenAngle, 0.0f);
    Owner->SetActorRotation(NewRotation);
}

void UDoorOpen::CloseDoor()
{
	Owner = GetOwner();
	FRotator NewRotator = FRotator(0.f, 0.f, 0.f);
    Owner->SetActorRotation(NewRotator);
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
	//if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	//{
	//	OpenDoor();
	//	LastDoorOpen = GetWorld()->GetTimeSeconds();    //TODO find exact meaning of GetTimeSeconds
	//}
	FHitResult Hit;

	FVector TriggerVolumeLocation = PressurePlate->GetActorLocation();
	FVector TriggerVolumeHeight = FVector(0.f, 0.f, 21.f);

	if (GetWorld()->LineTraceSingleByObjectType(OUT Hit, TriggerVolumeLocation, TriggerVolumeHeight,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner())))
	{
		OpenDoor();
		LastDoorOpen = GetWorld()->GetTimeSeconds();
	}

  /* else if ((GetWorld()->GetTimeSeconds()) - LastDoorOpen > GapTime)                    /// now my door closes exactly at GapTime i.e. 0.5 seconds
		CloseDoor();*/
	else
	{
		CloseDoor();
	}
	
	
	
	UE_LOG(LogTemp, Warning, TEXT(" trigger volume at %s"), *TriggerVolumeLocation.ToString());

}


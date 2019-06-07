// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "BuildingEscape.h"

#define OUT                   //to match our arguments with the function signature.


/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if (PhysicsHandle)
	{}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE NOT FOUND in %s ,GAME PHYSICS WILL NOT BE SIMULATED"),*(GetOwner()->GetName()));
	}
	
    PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PawnInput)
	{
		UE_LOG(LogTemp, Warning, TEXT("INPUT FOUND"));
		PawnInput->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction("Release", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("INPUT COMPONENT NOT FOUND in %s ,KEYBINDS WILL NOT BE SIMULATED"), *(GetOwner()->GetName()));
	}

}


/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	/* FVector PlayerLocation  = GetOwner()->GetActorLocation();
	FRotator PlayerRotation = GetOwner()->GetActorRotation(); */
	
	// ^^^ The above lines give accurate location but not accurate Rotation b/c the above lines define geometric rotation instead of camera eye angle^^^
	
	
	FVector  PlayerControllerLocation;
	FRotator PlayerControllerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerControllerLocation,OUT PlayerControllerRotation);  
	// ^^^ This edits the location and camera orientation(rotation) by itself and sets it to current value. ^^^
	
	UE_LOG(LogTemp, Warning, TEXT("Pawn is at %s and rotation %s"), *PlayerControllerLocation.ToString(), *PlayerControllerRotation.ToString());

	FVector LineTraceDirection = ((PlayerControllerRotation.Vector())*Reach);
	FVector LineTraceEnd = PlayerControllerLocation + LineTraceDirection;

	DrawDebugLine(GetWorld(), PlayerControllerLocation, LineTraceEnd, FColor(57.f, 255.f, 20.f), false, -1.f, 0.f, 15.f);
	//^^^  Draws a DebugLine on our Pawn ^^^

	FHitResult Hit;
	
	GetWorld()->LineTraceSingleByObjectType(OUT Hit,PlayerControllerLocation,LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),FCollisionQueryParams(FName(TEXT("")),false,GetOwner()));

   // ^^^ tells us whether our raycast(line-trace) is hitting any physics body or not and hence changes the value of "Hit". ^^^^

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)                                                            //<-- Sees if the pointer isnn't NULL i.e. the line-trace is pointing to something
	{
		UE_LOG(LogTemp, Warning, TEXT("WE ARE HITTING %s"), *(ActorHit->GetName()));
	}

	//^^^ GetOwner()->GetName() cannot be used because it gives the name of who is calling the code, Blueprint in this case.
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("MAIN AAGAYA"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("MAIN CHALA GAYA"));
}


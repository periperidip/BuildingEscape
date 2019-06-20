// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "BuildingEscape.h"
#include "Components/PrimitiveComponent.h"

#define OUT                   ///to match our arguments with the function signature.


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsComponent();

	KeyBinder();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector  PlayerControllerLocation;
	FRotator PlayerControllerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerControllerLocation, OUT PlayerControllerRotation);
	/// ^^^ This edits the location and camera orientation(rotation) by itself and sets it to current value. ^^^

	FVector LineTraceDirection = ((PlayerControllerRotation.Vector())*Reach);
	FVector LineTraceEnd = PlayerControllerLocation + LineTraceDirection;

	if(PhysicsHandle->GrabbedComponent)
	{   
		
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}


FHitResult UGrabber::PhysicsBodyHitChecker()
{	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, FinalLineStart(), FinalLineEnd(),
	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
    /// ^^^ tells us whether our raycast(line-trace) is hitting any physics body or not and hence changes the value of "Hit". ^^^^

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)                                                   ///<-- Sees if the pointer isnn't NULL i.e. the line-trace is pointing to something
	{
		UE_LOG(LogTemp, Warning, TEXT("WE ARE HITTING %s"), *(ActorHit->GetName()));
	}

	/// ^^^ GetOwner()->GetName() cannot be used because it gives the name of who is calling the code, Blueprint in this case.

   return Hit;
}


void UGrabber::FindPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE NOT FOUND in %s ,GAME PHYSICS WILL NOT BE SIMULATED"), *(GetOwner()->GetName()));}
}

void UGrabber::KeyBinder() 
{
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInput)
	{  	PawnInput->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction("Release", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{UE_LOG(LogTemp, Error, TEXT("INPUT COMPONENT NOT FOUND in %s ,KEYBINDS WILL NOT BE SIMULATED"), *(GetOwner()->GetName()));}
}


void UGrabber::Grab()
{	FHitResult HitResult = PhysicsBodyHitChecker();       
	/// ^^^ tells us who we hit,where we hit,etc. ^^^
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	/// ^^^ GetComponent() fucntion tells us who we hit,the mesh ^^^
	auto ActorHit = HitResult.GetActor();
	/// ^^^ GetComponent returns the component that was hit ^^^
	if (ActorHit)
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab
			, NAME_None
			, ComponentToGrab->GetOwner()->GetActorLocation()
			, true
			);
	}
}

void UGrabber::Release()
{PhysicsHandle->ReleaseComponent();}

FVector UGrabber::FinalLineEnd()
{
	///  FVector PlayerLocation  = GetOwner()->GetActorLocation();
	///  FRotator PlayerRotation = GetOwner()->GetActorRotation(); 

	/// ^^^ The above lines give accurate location but not accurate Rotation b/c the above lines define geometric rotation instead of camera eye angle^^^


	FVector  PlayerControllerLocation;
	FRotator PlayerControllerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerControllerLocation, OUT PlayerControllerRotation);
	/// ^^^ This edits the location and camera orientation(rotation) by itself and sets it to current value. ^^^
	/// ^^^ OUT values are the ones which will get edited by the function itself even though they had no intial values. ^^^

	FVector LineTraceDirection = ((PlayerControllerRotation.Vector())*Reach);
	FVector LineTraceEnd = PlayerControllerLocation + LineTraceDirection;

	return LineTraceEnd;
}

FVector UGrabber::FinalLineStart()
{   FVector  PlayerControllerLocation;
	FRotator PlayerControllerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerControllerLocation, OUT PlayerControllerRotation);
	return PlayerControllerLocation;
}
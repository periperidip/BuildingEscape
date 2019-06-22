// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 

	/// using private so that only member functions can access these

	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate=nullptr;             
	/// ^^^  used to see when an actor has entered this particular area and then give response  ^^^
	                                                          
	UPROPERTY(EditAnywhere) float TriggerMass=30.f;
	
	UPROPERTY(BlueprintAssignable)FDoorRequest OnOpenRequest;
	UPROPERTY(BlueprintAssignable)FDoorRequest OnCloseRequest;
	
	AActor* ActorThatOpens;
	AActor* Owner;
	float LastDoorOpen;
	float GetTotalMassOfActorsOnPlate();
};

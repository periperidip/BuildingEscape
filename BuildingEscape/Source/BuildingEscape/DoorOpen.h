// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"


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

	//using private so that functions can access these

	UPROPERTY(EditAnywhere) float OpenAngle = 90.0f;     

	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate;             
	//^^^  used to see when an actor has entered this particular area and then give response  ^^^
	                                                          
	UPROPERTY(EditAnywhere) float GapTime = 0.5f;
	
	AActor* ActorThatOpens;
	AActor* Owner;
	float LastDoorOpen;
};

// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{   GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    FHitResult PhysicsBodyHitChecker();

private: float Reach = 100.f;

		 UPhysicsHandleComponent* PhysicsHandle=nullptr;
         /// ^^^ To move physics objects around. ^^^
		 
		 UInputComponent* PawnInput = nullptr;
		 void Grab();
		 void Release();
		 FVector FinalLineEnd();
		 FVector FinalLineStart();
		 void KeyBinder();
		 void FindPhysicsComponent();
};

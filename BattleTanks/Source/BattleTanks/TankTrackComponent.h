// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
* TankTrackComponent is used to set max driving force, and apply forces to the tank
*/

UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANKS_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g acceleration

};

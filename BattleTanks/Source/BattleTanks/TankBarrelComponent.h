// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANKS_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.0f; // Sensible Default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40.0f; // Sensible Default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0.0f; // Sensible Default
	
};

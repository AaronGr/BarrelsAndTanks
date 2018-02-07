// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collisionn"))
class BATTLETANKS_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Turn(float RelativeSpeed);

public:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 15.0f;
	
};

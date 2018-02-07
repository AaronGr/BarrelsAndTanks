// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrelComponent;
class UTankTurretComponent;

// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrelComponent* BarrelToSet);
	void SetTurretReference(UTankTurretComponent* TurretToSet);
	void AimAt(FVector, float) const;
	void MoveBarrelTowards(FVector) const;
	void MoveTurretTowards(FVector) const;

private:	
	UTankBarrelComponent * Barrel = nullptr;
	UTankTurretComponent * Turret = nullptr;

};

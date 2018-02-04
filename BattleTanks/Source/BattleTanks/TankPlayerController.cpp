// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Controlling %s"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not get player controlled tank."))
	}
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}



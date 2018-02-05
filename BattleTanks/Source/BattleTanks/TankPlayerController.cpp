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

void ATankPlayerController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	FVector TmpHitLocation;
	GetSightRayHitLocation(TmpHitLocation);
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) {return;}

	FVector HitLocation; // OUT
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()))

		// TODO Tell controlled tank to aim at this point
	}
	
}

// Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &out_HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// De-project the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to max range)
	return true;
}

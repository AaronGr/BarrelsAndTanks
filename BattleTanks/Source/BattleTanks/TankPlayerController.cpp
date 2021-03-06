// Copyright Aaron Gravelle

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetPawn();

	if (ensure(ControlledTank)) {
		AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (AimingComponent) {
			FoundAimingComponent(AimingComponent);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"))
		}
	}	
}

void ATankPlayerController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	FVector HitLocation; // OUT
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	
	if (bGotHitLocation) {
		if (!ensure(AimingComponent)) { return; }
		AimingComponent->AimAt(HitLocation, AimingComponent->LaunchSpeed);
	}
	
}

// Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &out_HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, out_HitLocation);
	}
	else
	{
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& out_LookDirection) const {
	// De-project the screen position of the crosshair to a world direction
	FVector WorldLocation; // To be Discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		out_LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& out_HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams::DefaultQueryParam,
		FCollisionResponseParams::DefaultResponseParam
	)) {
		out_HitLocation = HitResult.Location;
		return true;
	}
	else {
		out_HitLocation = FVector(0);
		return false;
	}
}


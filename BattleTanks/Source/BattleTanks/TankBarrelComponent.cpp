// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"
#include "Engine/World.h"

void UTankBarrelComponent::Elevate(float RelativeSpeed)
{
	// Move the Barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}



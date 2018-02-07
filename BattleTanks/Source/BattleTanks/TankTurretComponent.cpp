// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "Engine/World.h"

void UTankTurretComponent::Turn(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// Given a max turn speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation =  RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}



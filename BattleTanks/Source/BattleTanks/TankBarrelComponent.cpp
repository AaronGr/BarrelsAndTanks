// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"

void UTankBarrelComponent::Elevate(float RelativeSpeed)
{
	// Move the Barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called at speed %f"), RelativeSpeed)
}



// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s player tank is in my sites"), *(PlayerTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not get player target tank."))
	}

	ATank* ControlledTank = GetAIControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s AI reporting for duty"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not get AI controlled tank."))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetAIControlledTank()) {return;}
	if (!GetPlayerTank()) {return;}

	GetAIControlledTank()->AimAt(GetPlayerTank()->GetTargetLocation());
}

ATank* ATankAIController::GetAIControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}



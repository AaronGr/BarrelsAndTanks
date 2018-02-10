// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* AIControlledTank = Cast<ATank>(GetPawn());
	if (AIControlledTank) {
		ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerTank) {  
			// Move towards the player
			MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
			AIControlledTank->AimAt(PlayerTank->GetTargetLocation());
			AIControlledTank->Fire(); // TODO Limit fire rate
		}
	}
	
}



// Copyright Aaron Gravelle

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (TankAimingComponent) {
		FoundAimingComponent(TankAimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find aiming component at Begin Play"))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(TankAimingComponent)) {return;}

	auto AIControlledTank = GetPawn();
	if (ensure(AIControlledTank)) {
		auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (ensure(PlayerTank)) {  
			// Move towards the player
			MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
			TankAimingComponent->AimAt(PlayerTank->GetTargetLocation(), TankAimingComponent->LaunchSpeed);
			TankAimingComponent->Fire(); // TODO Limit fire rate
		}
	}
	
}



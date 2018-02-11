// Copyright Aaron Gravelle

#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "Projectile.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();  
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	} 
}



void UTankAimingComponent::Initialize(UTankBarrelComponent * BarrelToSet, UTankTurretComponent * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	AimDirection = Barrel->GetForwardVector();
}



void UTankAimingComponent::AimAt(FVector HitTarget, float LaunchSpeed)
{
	if (!ensure(Barrel)) {return;}

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		LaunchVelocity,
		StartLocation,
		HitTarget,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	if (!ensure(Barrel && Turret)) {return;}

	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Turn(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) {return false;}
	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.1f));
}

void UTankAimingComponent::Fire()
{
		
		if (FiringState != EFiringState::Reloading) 
		{
			if (!ensure(Barrel)) {return;}
			if (!ensure(ProjectileBlueprint)) { return; }
			// Spawn a projectile at the socket location on the barrel
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
	
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
	
}





// Copyright Aaron Gravelle

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked, Aiming, Reloading, NoAmmo
};

// Forward Declaration
class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;

// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void BeginPlay() override;

	void AimAt(FVector, float);
	void MoveBarrelTowards(FVector) const;

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.f;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrelComponent* BarrelToSet, UTankTurretComponent* TurretToSet);

	UPROPERTY(BlueprintReadonly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	int32 AmmoCount = 5;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UTankBarrelComponent * Barrel = nullptr;
	UTankTurretComponent * Turret = nullptr;
	FVector AimDirection;
	double LastFireTime = 0;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving() const;

	
};

// Copyright Aaron Gravelle

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingCommponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()	

public:
	UFUNCTION()
	void OnTankDeath();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimComp);

	// How close can the AI tank get
	UPROPERTY(EditAnywhere, Category = "Movement")
	float AcceptanceRadius = 8000;

private:	
	UTankAimingComponent* TankAimingComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;
};

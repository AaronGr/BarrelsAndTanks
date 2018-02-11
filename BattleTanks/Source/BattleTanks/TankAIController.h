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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimComp);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AcceptanceRadius = 8000;

private:
	// How close can the AI tank get
	

	UTankAimingComponent* TankAimingComponent = nullptr;

};

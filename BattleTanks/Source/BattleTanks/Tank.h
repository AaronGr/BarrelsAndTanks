// Copyright Aaron Gravelle

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	float CurrentHealth = StartingHealth;
};

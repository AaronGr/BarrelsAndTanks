// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
* TankTrackComponent is used to set max driving force, and apply forces to the tank
*/

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrackComponent();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	void DriveTrack();

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 30000000; // Assume 40 tonne tank, and 1g acceleration

protected:
	virtual void BeginPlay() override;

	void ApplySidewaysForce();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			   UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
			   const FHitResult& Hit);
	float CurrentThrottle = 0;

};

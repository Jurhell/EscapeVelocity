// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GravityPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEVELOCITY_API AGravityPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PrimaryGravityDirection = FVector::DownVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator GravityRotation = FRotator::ZeroRotator;
public:
	UFUNCTION(BlueprintCallable)
	void UpdateGravityRotation();

	UFUNCTION(BlueprintCallable)
	void AddMovementInput(float Forward, float Right);

	UFUNCTION(BlueprintCallable)
	void AddRotationInput(float Yaw, float Pitch);

	UFUNCTION(BlueprintPure)
	static FRotator GetRelativeGravityRotation(FRotator Rotation, FVector GravityDirection);

	UFUNCTION(BlueprintPure)
	static FRotator GetWorldGravityRotation(FRotator Rotation, FVector GravityDirection);
};

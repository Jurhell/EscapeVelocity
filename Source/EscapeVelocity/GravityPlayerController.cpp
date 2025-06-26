// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"



void AGravityPlayerController::UpdateGravityRotation()
{
	//init GravityRotation
	if (GravityRotation == FRotator::ZeroRotator && PrimaryGravityDirection != FVector::ZeroVector)
		GravityRotation = GetWorldGravityRotation(GravityRotation, PrimaryGravityDirection);

	//update rotation by change in gravity
	if (bBound)
	{
		FQuat NewQuat;

		FVector LastGravityDirection = -UKismetMathLibrary::GetUpVector(GravityRotation);
		//rotate camera quat by gravity delta
		FQuat GravityDelta = FQuat::FindBetweenNormals(LastGravityDirection, PrimaryGravityDirection);

		//update rotation by gravity delta
		NewQuat = GravityDelta * FQuat(GravityRotation);
		GravityRotation = NewQuat.Rotator();
	}
}

void AGravityPlayerController::AddMovementInput(float Forward, float Right)
{
	FVector XMovement;
	FVector YMovement;
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawnOrSpectator());

	//move relative to current rotation
	YMovement = UKismetMathLibrary::GetForwardVector(GravityRotation);
	XMovement = UKismetMathLibrary::GetRightVector(GravityRotation);

	PlayerCharacter->AddMovementInput(YMovement, Forward, false);
	PlayerCharacter->AddMovementInput(XMovement, Right, false);
}

void AGravityPlayerController::AddRotationInput(float Yaw, float Pitch)
{
	FVector DownDirection = -UKismetMathLibrary::GetUpVector(GravityRotation);

	//get input relative to gravity
	GravityRotation = GetRelativeGravityRotation(GravityRotation, DownDirection);

	//rotate input
	GravityRotation.Yaw += Yaw;
	GravityRotation.Pitch += -Pitch;
	GravityRotation.Roll = 0;

	//set input relative to world
	GravityRotation = GetWorldGravityRotation(GravityRotation, DownDirection);
}

FRotator AGravityPlayerController::GetRelativeGravityRotation(FRotator Rotation, FVector GravityDirection)
{	
	FQuat RelativeRotation = FQuat::FindBetweenNormals(GravityDirection, FVector::DownVector);
	return(RelativeRotation * Rotation.Quaternion()).Rotator();
}

FRotator AGravityPlayerController::GetWorldGravityRotation(FRotator Rotation, FVector GravityDirection)
{
	FQuat WorldRotation = FQuat::FindBetweenNormals(FVector::DownVector, GravityDirection);
	return(WorldRotation * Rotation.Quaternion()).Rotator();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravitySource.generated.h"

UCLASS()
class ESCAPEVELOCITY_API AGravitySource : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* GravityCurve;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AGravitySource();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

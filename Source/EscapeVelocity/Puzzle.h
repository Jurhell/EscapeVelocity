// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EPuzzleType : uint8
{
	Switch,
	Timer
};

UCLASS(Blueprintable)
class ESCAPEVELOCITY_API APuzzle : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPuzzleType PuzzleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Countdown;

	UPROPERTY(VisibleAnywhere, meta =(AllowPrivateAccess = "true"))
	bool bCountdownStarted = false;

public:	
	// Sets default values for this actor's properties
	APuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnTriggerOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerOverlapEnd(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void BeginCountdown();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnPuzzleActivate();

	UFUNCTION(BlueprintNativeEvent)
	void OnPuzzleDeactivate();
};

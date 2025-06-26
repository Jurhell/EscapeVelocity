// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OxygenSystemComponent.generated.h"

class ACharacter;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEVELOCITY_API UOxygenSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	ACharacter* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Oxygen = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxOxygen = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DepletionRate = 0.1f;

	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	float DelayTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bPlayerOutOfOrbit;

	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	TArray<UPrimitiveComponent*> OverlappedComps;

public:	
	// Sets default values for this component's properties
	UOxygenSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void RefillPlayerOxygen(float DeltaTime);

	UFUNCTION()
	void DepletePlayerOxygen(float DeltaTime);

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION(BlueprintCallable)
	void TakeOxygenDamage(float DamageAmount = 25) { Oxygen -= DamageAmount; }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OxygenDepleted();
};

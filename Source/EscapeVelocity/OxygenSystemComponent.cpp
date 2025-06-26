// Fill out your copyright notice in the Description page of Project Settings.


#include "OxygenSystemComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOxygenSystemComponent::UOxygenSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOxygenSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	Oxygen = MaxOxygen;
	Player = (ACharacter*)GetOwner();
	UCapsuleComponent* PlayerCapsule = Player->GetCapsuleComponent();
	
	PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UOxygenSystemComponent::OnPlayerOverlap);
	PlayerCapsule->OnComponentEndOverlap.AddDynamic(this, &UOxygenSystemComponent::OnPlayerEndOverlap);
}


// Called every frame
void UOxygenSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Checking if player's oxygen should be depleted or refilled
	DepletePlayerOxygen(DeltaTime);
	RefillPlayerOxygen(DeltaTime);
}

void UOxygenSystemComponent::RefillPlayerOxygen(float DeltaTime)
{
	if (bPlayerOutOfOrbit)
		return;

	Oxygen += 14.f * DeltaTime;

	if (Oxygen >= MaxOxygen)
		Oxygen = MaxOxygen;
}

void UOxygenSystemComponent::DepletePlayerOxygen(float DeltaTime)
{
	if (!bPlayerOutOfOrbit)
		return;

	Oxygen -= DepletionRate * DeltaTime;
	
	if (Oxygen <= 0.f)
	{
		Oxygen = 0.f;

		DelayTimer += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

		if (DelayTimer >= 2.f)
		{
			OxygenDepleted();
			DelayTimer = 0.f;
		}
	}
}

void UOxygenSystemComponent::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("Atmosphere"))
	{
		bPlayerOutOfOrbit = false;
		OverlappedComps.Add(OtherComp);
	}
}

void UOxygenSystemComponent::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//When the player has stopped colliding with the atmosphere collider
	if (OverlappedComps.Contains(OtherComp))
		//Remove it from the array
		OverlappedComps.Remove(OtherComp);

	//Check if they are still in an atmosphere if not set them to be in orbit
	if (OverlappedComps.IsEmpty())
		bPlayerOutOfOrbit = true;
}

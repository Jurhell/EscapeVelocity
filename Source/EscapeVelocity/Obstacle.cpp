// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AObstacle::AObstacle()
{
	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	sceneComponent->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(sceneComponent);

	TriggerBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBounds->SetupAttachment(StaticMesh);
	TriggerBounds->SetRelativeScale3D({ 3.f, 3.f, 3.f });
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBounds->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnTriggerOverlap);
}

void AObstacle::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ObstacleType == EObstacleType::Spike)
		DamageOxygen();
}


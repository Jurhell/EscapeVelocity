// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


#define DELAY(time, block)\
{\
FTimerHandle TimerHandle;\
GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()block, time, false);\
}

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	sceneComponent->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(sceneComponent);
	StaticMesh->SetMobility(EComponentMobility::Stationary);
	StaticMesh->SetRelativeScale3D({ 1.f, 1.f, 0.1f });

	TriggerBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBounds->SetupAttachment(StaticMesh);
	TriggerBounds->SetMobility(EComponentMobility::Stationary);
	TriggerBounds->SetRelativeScale3D({ 3.f, 3.f, 5.f });
}

// Called when the game starts or when spawned
void APuzzle::BeginPlay()
{
	Super::BeginPlay();

	TriggerBounds->OnComponentBeginOverlap.AddDynamic(this, &APuzzle::OnTriggerOverlap);
	TriggerBounds->OnComponentEndOverlap.AddDynamic(this, &APuzzle::OnTriggerOverlapEnd);
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

} 

void APuzzle::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PuzzleType == EPuzzleType::Switch &&
		OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		OnPuzzleActivate();
	else if (PuzzleType == EPuzzleType::Timer)
		BeginCountdown();
}

void APuzzle::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PuzzleType == EPuzzleType::Switch)
		OnPuzzleDeactivate();
	else if (PuzzleType == EPuzzleType::Timer)
		return;
}

void APuzzle::BeginCountdown()
{
	if (bCountdownStarted)
		return;

	bCountdownStarted = true;
	OnPuzzleActivate();

	DELAY(Countdown, { OnPuzzleDeactivate(); bCountdownStarted = false; });
}

void APuzzle::OnPuzzleDeactivate_Implementation()
{
}

void APuzzle::OnPuzzleActivate_Implementation()
{
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	//get the owner of this component
	AActor* Owner = GetOwner();

	FVector ActorLocation = (*Owner).GetActorLocation();
	FVector ActorLocation2 = Owner->GetActorLocation();

	FString ActorLocationString = ActorLocation.ToCompactString();
	FString name = "oscar";

	UE_LOG(LogTemp, Display, TEXT("Actor Location is: %s"), name);

	UE_LOG(LogTemp, Display, TEXT("The address of the owner is %u"), Owner);
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//lof a test message to the output log
	// UE_LOG(LogTemp, Display, TEXT("Actor Tick Working!"));
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

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

	OriginalLocation = (*Owner).GetActorLocation();
	FString ActorName = Owner->GetActorNameOrLabel();

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = Owner->GetActorLocation();

	// Calculate the speed based on the distance to move and the time to move
	float Speed = FVector::Distance(OriginalLocation, (OriginalLocation + MoveOffset)) / MoveTime;

	if (ShouldMove){

		// Move the actor towards the target location at the calculated speed
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginalLocation + MoveOffset, DeltaTime, Speed);
		Owner->SetActorLocation(NewLocation);
	}
	else{
		
	}
	
}


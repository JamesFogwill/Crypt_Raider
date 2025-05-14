// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FRotator CurrentRotation = GetComponentRotation(); // Get the current rotation of the owners component
	FString CurrentRotationString = CurrentRotation.ToCompactString(); // Convert the rotation to a string for debugging

	UE_LOG(LogTemp, Display, TEXT("The current rotation of the component is: %s"), *CurrentRotationString);


	UWorld* World = GetWorld(); // Get the current world make a pointer to it
	float ElapsedWorldTime = World->GetTimeSeconds(); // Get the elapsed world time via the world pointer

	UE_LOG(LogTemp, Display, TEXT("Current time is: %f"), ElapsedWorldTime); // Log the elapsed world time


	FVector SweepStartVec = GetComponentLocation(); // Get the current location of the owners component
	FVector SweepEndVec = SweepStartVec + (GetForwardVector() * Reach); // Get the forward vector of the owners component and multiply it by 100 to get the end vector

	DrawDebugLine(GetWorld(), SweepStartVec, SweepEndVec, FColor::Red); // Draw a debug line from the start vector to the end vector


	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabberRadius); // Create a sphere with a radius of 10 to use for the sweep
	FHitResult OutHitResultStruct; // Create a hit result struct to be populated with results of the sweep ITS AN OUT PARAMETER
	bool HasHit = GetWorld()->SweepSingleByChannel(OutHitResultStruct,
		 SweepStartVec, 						// The start vector of the sweep
		 SweepEndVec,							// The end vector of the sweep
		 FQuat::Identity, 						// FQuat::Identity is the rotation of the sphere, it means no rotation
		 ECC_GameTraceChannel2, 				// ECC_GameTraceChannel2 is the collision channel to use, this is the Grabber channel
		 Sphere); 								// Create a sphere with a radius of 10 to use for the sweep		 
		
	if(HasHit){

		AActor* HitActor = OutHitResultStruct.GetActor(); // make a pointer to the actor that was hit by the sweep
		FString HitActorName = HitActor->GetActorNameOrLabel(); // de-reference the pointer the get the actor and use the GetActorNameOrLabel function to get the name of the actor that was hit by the sweep
		
		UE_LOG(LogTemp, Display, TEXT("You have hit: %s "), *HitActorName); // Log the name of the hit actor
	}

}


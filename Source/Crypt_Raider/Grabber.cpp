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

	UPhysicsHandleComponent* PhysicsHandlePtr = GetPhysicsHandle();

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandlePtr->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

	
}

void UGrabber::Grab(){

	UPhysicsHandleComponent* PhysicsHandlePtr = GetPhysicsHandle();
	

	/*FRotator CurrentRotation = GetComponentRotation(); // Get the current rotation of the owners component
	FString CurrentRotationString = CurrentRotation.ToCompactString(); // Convert the rotation to a string for debugging

	UE_LOG(LogTemp, Display, TEXT("The current rotation of the component is: %s"), *CurrentRotationString);


	UWorld* World = GetWorld(); // Get the current world make a pointer to it
	float ElapsedWorldTime = World->GetTimeSeconds(); // Get the elapsed world time via the world pointer

	UE_LOG(LogTemp, Display, TEXT("Current time is: %f"), ElapsedWorldTime); // Log the elapsed world time

	DrawDebugLine(GetWorld(), SweepStartVec, SweepEndVec, FColor::Red); // Draw a debug line from the start vector to the end vector
	DrawDebugSphere(GetWorld(), SweepEndVec, 10, 10, FColor::Red, false, 5); // draw debug sphere at end of grab reach*/

	FVector SweepStartVec = GetComponentLocation(); // Get the current location of the owners component
	FVector SweepEndVec = SweepStartVec + (GetForwardVector() * Reach); // Get the forward vector of the owners component and multiply it by 100 to get the end vector

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabberRadius); // Create a sphere with a radius of 10 to use for the sweep
	FHitResult OutHitResult; // Create a hit result struct to be populated with results of the sweep ITS AN OUT PARAMETER
	bool HasHit = GetWorld()->SweepSingleByChannel(OutHitResult,
		 SweepStartVec, 						// The start vector of the sweep
		 SweepEndVec,							// The end vector of the sweep
		 FQuat::Identity, 						// FQuat::Identity is the rotation of the sphere, it means no rotation
		 ECC_GameTraceChannel2, 				// ECC_GameTraceChannel2 is the collision channel to use, this is the Grabber channel
		 Sphere); 								// Create a sphere with a radius of 10 to use for the sweep		 
		
	if(HasHit){

		/* AActor* HitActor = OutHitResultStruct.GetActor(); // make a pointer to the actor that was hit by the sweep
		FString HitActorName = HitActor->GetActorNameOrLabel(); // de-reference the pointer the get the actor and use the GetActorNameOrLabel function to get the name of the actor that was hit by the sweep
		
		UE_LOG(LogTemp, Display, TEXT("You have hit: %s "), *HitActorName); // Log the name of the hit actor

		FVector HitLocation = OutHitResultStruct.Location;
		FVector HitImpact = OutHitResultStruct.ImpactPoint;

		DrawDebugSphere(GetWorld(), HitLocation, 10, 10, FColor::Blue,false,10);
		DrawDebugSphere(GetWorld(), HitImpact, 10, 10, FColor::Yellow, false, 10); // this is the one we want 
		*/

		PhysicsHandlePtr->GrabComponentAtLocationWithRotation(
			OutHitResult.GetComponent(),
			NAME_None,
			OutHitResult.ImpactPoint,
			GetComponentRotation()

		);
	};

}; 


void UGrabber::Release(){

	UE_LOG(LogTemp, Display, TEXT("RELEASED!"));
};


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{	
	UPhysicsHandleComponent* PhysicsHandlePtr = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandlePtr == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle - NullPtr"));
	}
	
	return PhysicsHandlePtr;
}

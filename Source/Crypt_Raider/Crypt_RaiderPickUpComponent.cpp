// Copyright Epic Games, Inc. All Rights Reserved.

#include "Crypt_RaiderPickUpComponent.h"

UCrypt_RaiderPickUpComponent::UCrypt_RaiderPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UCrypt_RaiderPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UCrypt_RaiderPickUpComponent::OnSphereBeginOverlap);
}

void UCrypt_RaiderPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ACrypt_RaiderCharacter* Character = Cast<ACrypt_RaiderCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}

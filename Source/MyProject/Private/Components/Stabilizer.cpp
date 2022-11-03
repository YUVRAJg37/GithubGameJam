// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Stabilizer.h"

#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

UStabilizer::UStabilizer() :
StabilizerRayDistance(10.0f),
StabilizerStrength(480000),
StabilizerDamping(10),
bIsInAir(false)
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UStabilizer::BeginPlay()
{
	Super::BeginPlay();
	
	BodyRef = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}


// Called every frame
void UStabilizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(BodyRef)
	{
		StabilizerRayCast();
	}
}

void UStabilizer::StabilizerRayCast()
{
	FHitResult HitResult;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, GetComponentLocation(),
		GetComponentLocation() + BodyRef->GetUpVector()*-1*StabilizerRayDistance, ECC_Visibility);

	if(HitResult.bBlockingHit)
	{
		bIsInAir = false;
		Compression = 1 - HitResult.Distance/StabilizerRayDistance;
		DrawDebugLine(GetWorld(), GetComponentLocation(), HitResult.ImpactPoint, FColor::Green);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5,5,5), FColor::Red);
		float SuspensionForce = StabilizerStrength*Compression - StabilizerDamping*GetSuspensionVelocity().Z;
		BodyRef->AddForceAtLocation(BodyRef->GetUpVector()*SuspensionForce, GetComponentLocation());
		DrawDebugString(GetWorld(), GetComponentLocation() , FString::Printf(TEXT("%.2f"), Compression), nullptr, FColor::White, 0, false, 2);
	}
	else
	{
		bIsInAir = true;
	}
}


FVector UStabilizer::GetSuspensionVelocity()
{
	FVector CurrentLocation = GetComponentLocation();
	FVector Velocity = (PreviousLocation - CurrentLocation) /GetWorld()->GetDeltaSeconds();
	PreviousLocation = CurrentLocation;
	
	return Velocity;
}

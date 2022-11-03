// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Stabilizer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UStabilizer : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStabilizer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stabilizer")
	float StabilizerRayDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float StabilizerStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float StabilizerDamping;
	FVector PreviousLocation;
	float Compression;
	bool  bIsInAir;
	
private:
	
	UPROPERTY()
	UPrimitiveComponent* BodyRef; //Reference to the Body on which this component is attached
	
	void StabilizerRayCast();
	FVector GetSuspensionVelocity();

		
};



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MagicDoor.generated.h"

UCLASS()
class UECPP_PRACTICE_API AMagicDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Magic Door")
	UStaticMeshComponent* DoorMesh = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Magic Door")
	float DoorOffsetValue = 3.0f;
	
	UPROPERTY(EditAnywhere, Category="Magic Door")
	UCurveFloat* TimeCurve = nullptr;

	
	FTimeline Timeline;

	void OpenDoorAction();

	void CloseDoorAction();

	UFUNCTION()
	void OpenDoorProcess(float Value);

	bool IsReverse;
	

};

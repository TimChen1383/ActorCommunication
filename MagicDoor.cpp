// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicDoor.h"

// Sets default values
AMagicDoor::AMagicDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scene Component"));
	DoorMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMagicDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up timeline interpolation and bind open door action action
	FOnTimelineFloat TimelineProgress;
	TimelineProgress.BindDynamic(this, &AMagicDoor::OpenDoorProcess);
	Timeline.AddInterpFloat(TimeCurve, TimelineProgress);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Begin play setup"));
	
}

// Called every frame
void AMagicDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);

}

void AMagicDoor::OpenDoorAction()
{
	//start playing timeline
	IsReverse = false;
	Timeline.PlayFromStart();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Open Door Action"));
}

void AMagicDoor::CloseDoorAction()
{
	//start playing timeline in opposite direction
	IsReverse = true;
	Timeline.PlayFromStart();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Close Door Action"));
	
}

void AMagicDoor::OpenDoorProcess(float Value)
{

	FVector const CurrentLocation = GetActorLocation();

	if(IsReverse == true)
	{
		FVector ZOffset = FVector(0,0,(Value*(-1)));
		FVector NewLocation = CurrentLocation + (ZOffset*DoorOffsetValue);
		DoorMesh->SetRelativeLocation(NewLocation);
	
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Door Open Process"));
	}
	else
	{
		FVector ZOffset = FVector(0,0,Value);
		FVector NewLocation = CurrentLocation + (ZOffset*DoorOffsetValue);
		DoorMesh->SetRelativeLocation(NewLocation);
	
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Door Open Process"));
	}
	
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorCommunication.h"

#include "LightBulb.h"
#include "MagicDoor.h"

// Sets default values
AActorCommunication::AActorCommunication()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	ControllerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Controller"));
	CollideSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collide Sphere"));
	ControllerMesh -> SetupAttachment(SceneComponent);
	CollideSphere -> SetupAttachment(SceneComponent);
	CollideSphere->SetSphereRadius(100.0f);
	
	CollideSphere->OnComponentBeginOverlap.AddDynamic(this, &AActorCommunication::OnSphereBeginOverlap);
	CollideSphere->OnComponentEndOverlap.AddDynamic(this, &AActorCommunication::OnSphereEndOverlap);

}

// Called when the game starts or when spawned
void AActorCommunication::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorCommunication::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorCommunication::OnSphereBeginOverlap(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(DoorActor != nullptr)
	{
		//Lit controller
		auto CurrentControlMat = ControllerMesh -> GetMaterial(1);
		auto DynamicMaterial = ControllerMesh->CreateDynamicMaterialInstance(1,CurrentControlMat);
		DynamicMaterial->SetScalarParameterValue("HighLight", 30.0f);
		ControllerMesh->SetMaterial(1, DynamicMaterial);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Material Highlighted"));

		//Cast to Magic Door and trigger door open action
		AMagicDoor* CommunicateDoor = Cast<AMagicDoor>(DoorActor);
		CommunicateDoor->OpenDoorAction();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Object Overlapped"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("No Door Found!"));
	}
	
}

void AActorCommunication::OnSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(DoorActor != nullptr)
	{
		//Un-Lit controller
		auto CurrentControlMat = ControllerMesh -> GetMaterial(1);
		auto DynamicMaterial = ControllerMesh->CreateDynamicMaterialInstance(1,CurrentControlMat);
		DynamicMaterial->SetScalarParameterValue("HighLight", 0.0f);
		ControllerMesh->SetMaterial(1, DynamicMaterial);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Unlit Material"));

		//Cast to Magic Door and trigger door open action
		AMagicDoor* CommunicateDoor = Cast<AMagicDoor>(DoorActor);
		CommunicateDoor->CloseDoorAction();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Object Left"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("No Door Found!"));
	}
}


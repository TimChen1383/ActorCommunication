// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ActorCommunication.generated.h"

UCLASS()
class UECPP_PRACTICE_API AActorCommunication : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorCommunication();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USceneComponent* SceneComponent = nullptr;
	
	USphereComponent* CollideSphere = nullptr;

	UPROPERTY(EditAnywhere, Category="ActorCommunication")
	AActor* DoorActor;

	UPROPERTY(EditAnywhere, Category="ActorCommunication")
	UStaticMeshComponent* ControllerMesh;
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

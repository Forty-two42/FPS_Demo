// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo_pick_M4A1.generated.h"

UCLASS()
class FPS_API AAmmo_pick_M4A1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo_pick_M4A1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Collison");
	class USphereComponent* Collision;
	UPROPERTY(EditAnywhere, Category = "Mesh");
	class UStaticMeshComponent* StaticMesh;
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

};

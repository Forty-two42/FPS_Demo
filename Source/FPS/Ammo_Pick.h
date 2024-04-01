// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo_Pick.generated.h"

UCLASS()
class FPS_API AAmmo_Pick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo_Pick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//静态网格体
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;
	//碰撞组件
	UPROPERTY(EditAnywhere, Category = "Collision")
		class USphereComponent* Collision;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
};

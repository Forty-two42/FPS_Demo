// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/SceneComponent.h"
#include"Components/SkeletalMeshComponent.h"
#include "Weapon.generated.h"

UCLASS()
class FPS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,Category="Mesh")
		USkeletalMeshComponent* SkeletalComp;
	//µ¯Ï»×Óµ¯
	UPROPERTY(VisibleAnywhere)
		int32 Ammo_C = 30;
	//±¸µ¯
	UPROPERTY(VisibleAnywhere)
		int32 Ammo_B = 100;

	//»»µ¯
	UFUNCTION()
		void Reloading();

	FORCEINLINE class USkeletalMeshComponent* GetWeaponMesh() { return SkeletalComp; }

};

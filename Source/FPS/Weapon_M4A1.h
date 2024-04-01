// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_M4A1.generated.h"

UCLASS()
class FPS_API AWeapon_M4A1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_M4A1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* SceneComp;
	UPROPERTY(EditAnywhere,Category="Mesh")
		class USkeletalMeshComponent* SkeletalComp;
	//µ¯Ï»×Óµ¯
	UPROPERTY(VisibleAnywhere)
		int32 Ammo_C = 50;
	//±¸µ¯
	UPROPERTY(VisibleAnywhere)
		int32 Ammo_B = 120;

	//»»µ¯
	UFUNCTION()
	void Reloading();
	FORCEINLINE class USkeletalMeshComponent* GetWeaponMesh() { return SkeletalComp; }
	
};

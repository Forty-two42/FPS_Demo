// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class FPS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// ������ײ�����
	UPROPERTY(EditAnywhere, Category = Projectile)
		class USphereComponent* CollisionComponent;
	// �������ƶ������
	UPROPERTY(EditAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovementComponent;
	// ������������
	UPROPERTY(EditAnywhere, Category = Projectile)
		class UStaticMeshComponent* ProjectileMeshComponent;
	// ��������Ч
	UPROPERTY(EditAnywhere, Category = Particle)
		class UParticleSystem* Particle;
	//����UI
	UPROPERTY(EditAnyWhere, Category = "Widget")
		TSubclassOf<UUserWidget>HitWidget;


	// ��ʼ����������Ϸ������ٶȵĺ�����
	void FireInDirection(const FVector& ShootDirection);
	// ���������������ʱ����õĺ�����
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};

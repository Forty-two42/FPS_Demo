// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include"Components/SphereComponent.h"
#include"Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"FPSCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"UObject/ConstructorHelpers.h"
#include"Enemy.h"
#include"Materials/MaterialInstanceDynamic.h"
#include"GameFramework/DamageType.h"
#include"Engine.h"
#include"Kismet/GameplayStatics.h"
#include"Components/WidgetComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// 用球体进行简单的碰撞展示。
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		RootComponent = CollisionComponent;
	}
	if (!ProjectileMovementComponent) {
		// 使用此组件驱动发射物的移动。
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementomponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
	// 3 秒后删除发射物。
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector & ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// 撞击后给个提示
	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	// 碰撞之后再也不发生碰撞事件
	HitComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 如果撞击的是敌人角色
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		//设置widget
		UUserWidget* Hit_Widget = CreateWidget<UUserWidget>(GetWorld(), HitWidget);
		if(Hit_Widget)Hit_Widget->AddToViewport();
		// 受伤害源OtherActor的TakeDamage()会被调用
		float DamageAmount = 0.2f; // 伤害值
		FPointDamageEvent DamageEvent(DamageAmount, Hit, NormalImpulse, UDamageType::StaticClass());
		OtherActor->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
		Destroy();
	}
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		//销毁子弹
		Destroy();
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Particle,this->GetTransform());
}


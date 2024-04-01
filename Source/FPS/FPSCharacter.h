// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class AProjectile;
UCLASS()
class FPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// FPS摄像机。
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	//UI
	UPROPERTY(EditAnywhere,Category="HUD")
		TSubclassOf<UUserWidget>FPS_Widget;
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<UUserWidget>Damage_Widget;
	//血条和盾
	UPROPERTY(BlueprintReadOnly)
		float health;
	UPROPERTY(BlueprintReadOnly)
		float armor;
	//是否受到伤害
	UPROPERTY(BlueprintReadOnly)
	bool damage = false;
	// 生成子弹。
	UPROPERTY(EditDefaultsOnly,Category="Fire")
	TSubclassOf<AProjectile> Bullet;
	//子弹偏移
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		FVector MuzzleOffset;
	FTimerHandle TimerHandle;
	//生成武器
	UPROPERTY()
		class AWeapon* AK_47;
	//生成武器
	UPROPERTY()
		class AWeapon_M4A1* M4A1;
	UPROPERTY(BlueprintReadOnly)
	bool isSprint=false;
	//开火频率
	UPROPERTY(EditAnywhere, Category = "Fire")
		float Firerate = 0.1f;
	//背包弹药
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
		int32 Ammo_B = 100;
	//弹匣弹药
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
		int32 Ammo_C= 30;
	FTimerHandle TimerHandle_BetweenShoot;
	//发射声音
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundCue* Shoot;
	//武器位置
	UPROPERTY(EditAnywhere, Category = "Weapon")
		USkeletalMeshComponent* Weapon_Loc;
	//第二个摄像机
	UPROPERTY(EditAnywhere)
		UCameraComponent* ADSCamera;
	//开火特效
	UPROPERTY(EditAnyWhere,Category="Particle")
		class UParticleSystem* ParticleComp;
	UPROPERTY(BlueprintReadOnly)
	bool Isreloading = false;
	FTimerHandle TimerHandle_Reload;
	//瞄准状态
	UPROPERTY(BlueprintReadOnly)
	bool Aiming = false;
	//发出声音
	UPROPERTY()
		class UPawnNoiseEmitterComponent* NoiseEmitter;
	//是否死亡
	bool IsDead=false;
	//目标文本
	UPROPERTY(BlueprintReadOnly, Category = "Object")
	FString ObjectText=TEXT("Progress Through the Level");
	//武器编号
	UPROPERTY(BlueprintReadOnly)
	int WeaponSelected = 1;



	//实现移动
	UFUNCTION()
		void MoveForward(float vlaue);
	UFUNCTION()
		void MoveRight(float value);
	//实现跳跃
	UFUNCTION()
		void Startjump();
	UFUNCTION()
		void Stopjump();
	//跑
	UFUNCTION()
		void Run();
	UFUNCTION()
		void EndRun();
	//蹲
	UFUNCTION()
		void MyCrouch();
	UFUNCTION()
		void EndCrouch();
	//受到攻击
	UFUNCTION(BlueprintCallable)
		void Ondamage();
	//延迟生成护盾
	void Recover();
	void Delay();
	//开火
	void Fire();
	UFUNCTION()
		void StartFire();
	UFUNCTION()
		void EndFire();
	//瞄准
	UFUNCTION()
		void ADS();
	UFUNCTION()
		void EndADS();
	//装弹
	UFUNCTION()
		void Reloading();
	UFUNCTION()
		void EndReload();
	//换武器
	UFUNCTION()
		void SelectPrimary();
	UFUNCTION()
		void SelectSecondary();
	//角色死亡
	UFUNCTION()
		void Dead();
};

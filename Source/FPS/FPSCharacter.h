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

	// FPS�������
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	//UI
	UPROPERTY(EditAnywhere,Category="HUD")
		TSubclassOf<UUserWidget>FPS_Widget;
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<UUserWidget>Damage_Widget;
	//Ѫ���Ͷ�
	UPROPERTY(BlueprintReadOnly)
		float health;
	UPROPERTY(BlueprintReadOnly)
		float armor;
	//�Ƿ��ܵ��˺�
	UPROPERTY(BlueprintReadOnly)
	bool damage = false;
	// �����ӵ���
	UPROPERTY(EditDefaultsOnly,Category="Fire")
	TSubclassOf<AProjectile> Bullet;
	//�ӵ�ƫ��
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		FVector MuzzleOffset;
	FTimerHandle TimerHandle;
	//��������
	UPROPERTY()
		class AWeapon* AK_47;
	//��������
	UPROPERTY()
		class AWeapon_M4A1* M4A1;
	UPROPERTY(BlueprintReadOnly)
	bool isSprint=false;
	//����Ƶ��
	UPROPERTY(EditAnywhere, Category = "Fire")
		float Firerate = 0.1f;
	//������ҩ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
		int32 Ammo_B = 100;
	//��ϻ��ҩ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
		int32 Ammo_C= 30;
	FTimerHandle TimerHandle_BetweenShoot;
	//��������
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundCue* Shoot;
	//����λ��
	UPROPERTY(EditAnywhere, Category = "Weapon")
		USkeletalMeshComponent* Weapon_Loc;
	//�ڶ��������
	UPROPERTY(EditAnywhere)
		UCameraComponent* ADSCamera;
	//������Ч
	UPROPERTY(EditAnyWhere,Category="Particle")
		class UParticleSystem* ParticleComp;
	UPROPERTY(BlueprintReadOnly)
	bool Isreloading = false;
	FTimerHandle TimerHandle_Reload;
	//��׼״̬
	UPROPERTY(BlueprintReadOnly)
	bool Aiming = false;
	//��������
	UPROPERTY()
		class UPawnNoiseEmitterComponent* NoiseEmitter;
	//�Ƿ�����
	bool IsDead=false;
	//Ŀ���ı�
	UPROPERTY(BlueprintReadOnly, Category = "Object")
	FString ObjectText=TEXT("Progress Through the Level");
	//�������
	UPROPERTY(BlueprintReadOnly)
	int WeaponSelected = 1;



	//ʵ���ƶ�
	UFUNCTION()
		void MoveForward(float vlaue);
	UFUNCTION()
		void MoveRight(float value);
	//ʵ����Ծ
	UFUNCTION()
		void Startjump();
	UFUNCTION()
		void Stopjump();
	//��
	UFUNCTION()
		void Run();
	UFUNCTION()
		void EndRun();
	//��
	UFUNCTION()
		void MyCrouch();
	UFUNCTION()
		void EndCrouch();
	//�ܵ�����
	UFUNCTION(BlueprintCallable)
		void Ondamage();
	//�ӳ����ɻ���
	void Recover();
	void Delay();
	//����
	void Fire();
	UFUNCTION()
		void StartFire();
	UFUNCTION()
		void EndFire();
	//��׼
	UFUNCTION()
		void ADS();
	UFUNCTION()
		void EndADS();
	//װ��
	UFUNCTION()
		void Reloading();
	UFUNCTION()
		void EndReload();
	//������
	UFUNCTION()
		void SelectPrimary();
	UFUNCTION()
		void SelectSecondary();
	//��ɫ����
	UFUNCTION()
		void Dead();
};

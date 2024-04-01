// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class FPS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//血量
	UPROPERTY(EditAnywhere, Category = "Health")
		float Health_Enemy;
	//血条
	UPROPERTY(VisibleAnywhere,Category=Mesh)
		class UWidgetComponent* HPBar;
	//感官组件
	UPROPERTY(EditAnywhere,Category=Mesh)
		class UPawnSensingComponent* SensingComp;
	//攻击组件
	UPROPERTY(EditAnywhere, Category = "Attack")
		class USphereComponent* AttackingComp;
	//是否攻击玩家
	UPROPERTY(BlueprintReadOnly)
		bool IsAttackPlayer = false;
	//AI
	UPROPERTY()
		class AEnemy_AIController* AIController;
	//敌人死亡控件
	UPROPERTY(EditAnyWhere, Category="Widget")
		TSubclassOf<UUserWidget>Kill_Popup;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//受伤
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//看见角色
	UFUNCTION()
		void SeePawn(APawn* Pawn);
	//听见枪声
	UFUNCTION()
		void OnHeardNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);
	UFUNCTION()
		void UpdateHPBarRotation(FVector SPLocation);

	//设置速度
	void SetMaxSpeed(float Speed);
	//死亡
	UFUNCTION()
		void OnDead();
	//攻击
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,    //触发时间的主体，通常是控制的人
			UPrimitiveComponent* OterComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	//停止攻击
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
private:
	//血条引用
	TSharedPtr<class SEnemyHPWidget> HPBarWidget;
};

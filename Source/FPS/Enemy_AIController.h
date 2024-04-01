// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AEnemy_AIController();
	
	//黑板组件
	UPROPERTY()
	class UBlackboardComponent* BlackboardComp;
	//行为树组件
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorComp;
	//行为树
	UPROPERTY(EditAnywhere,Category = "AI");
	class UBehaviorTree* BehaviorTree;
	//是否锁定玩家
	UPROPERTY()
	bool IsLockedPlayer;

	virtual void OnPossess(APawn* InPawn)override;

	virtual void OnUnPossess()override;

	//获取玩家位置
	UFUNCTION()
	FVector GetPlayerLocation() const;

	//玩家是否死亡
	UFUNCTION()
	bool IsPlayerDead();

	//看到玩家
	UFUNCTION()
	void OnSeePlayer();
	
	//听到玩家
	UFUNCTION()
		void OnHearPlayer();

	//攻击玩家
	UFUNCTION()
		void OnAttackPlayer();

	//丢失玩家
	UFUNCTION()
	void LosePlayerLocation();

	//获取玩家指针
	UFUNCTION()
		UObject* GetPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	//敌人
	UPROPERTY()
	class AEnemy* Enemy;
	//主角
	UPROPERTY()
	class AFPSCharacter* FPSCharacter;
};

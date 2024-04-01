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
	
	//�ڰ����
	UPROPERTY()
	class UBlackboardComponent* BlackboardComp;
	//��Ϊ�����
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorComp;
	//��Ϊ��
	UPROPERTY(EditAnywhere,Category = "AI");
	class UBehaviorTree* BehaviorTree;
	//�Ƿ��������
	UPROPERTY()
	bool IsLockedPlayer;

	virtual void OnPossess(APawn* InPawn)override;

	virtual void OnUnPossess()override;

	//��ȡ���λ��
	UFUNCTION()
	FVector GetPlayerLocation() const;

	//����Ƿ�����
	UFUNCTION()
	bool IsPlayerDead();

	//�������
	UFUNCTION()
	void OnSeePlayer();
	
	//�������
	UFUNCTION()
		void OnHearPlayer();

	//�������
	UFUNCTION()
		void OnAttackPlayer();

	//��ʧ���
	UFUNCTION()
	void LosePlayerLocation();

	//��ȡ���ָ��
	UFUNCTION()
		UObject* GetPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	//����
	UPROPERTY()
	class AEnemy* Enemy;
	//����
	UPROPERTY()
	class AFPSCharacter* FPSCharacter;
};

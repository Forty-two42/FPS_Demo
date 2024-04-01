// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "AIBlackboardData.generated.h"

/**
 * 
 */
 //����AI״̬
UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
	ES_Patrol       UMETA(DisplayName = "Patrol"),
	ES_Chase        UMETA(DisplayName = "Chase"),
	ES_Escape       UMETA(DisplayName = "Escape"),
	ES_Attack       UMETA(DisplayName = "Attack"),
	ES_Hurt         UMETA(DisplayName = "Hurt"),
	ES_Defence      UMETA(DisplayName = "Defence"),
	ES_Dead         UMETA(DisplayName = "Dead"),
};

UCLASS()
class FPS_API UAIBlackboardData : public UBlackboardData
{
	GENERATED_BODY()
	
public:
	UAIBlackboardData();
	UFUNCTION()
		virtual void PostLoad()override;
	//Ŀ�ĵ�
	FBlackboardEntry Destination;
	//����״̬
	FBlackboardEntry EnemyState;
	//�ȴ�ʱ��
	FBlackboardEntry WaitTime;
	//��������
	FBlackboardEntry Attack;
	//���ָ��
	FBlackboardEntry PlayerPawn;
	//�������
	FBlackboardEntry ProcessFinish;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBTTaskNode.h"
#include "AIBTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UAIBTTaskNode_Attack : public UAIBTTaskNode
{
	GENERATED_BODY()
protected:
	//��дִ�к���
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector EnemyState;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector AttackType;
};

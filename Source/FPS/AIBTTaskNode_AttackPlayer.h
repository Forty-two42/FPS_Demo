// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBTTaskNode.h"
#include "AIBTTaskNode_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UAIBTTaskNode_AttackPlayer : public UAIBTTaskNode
{
	GENERATED_BODY()
protected:
	//ÖØÐ´Ö´ÐÐº¯Êý
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector Playerpawn;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector Waittime;
};

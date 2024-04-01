// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode_AttackPlayer.h"
#include"Enemy.h"
#include"Enemy_AIController.h"
#include"NavigationSystem.h"
#include"AIBlackboardData.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"

EBTNodeResult::Type UAIBTTaskNode_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyE1ement(OwnerComp))return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Playerpawn.SelectedKeyName,SEController->GetPlayerPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(Waittime.SelectedKeyName,5.f);
	return EBTNodeResult::Succeeded;
}
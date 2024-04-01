// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode_Attack.h"
#include"Enemy.h"
#include"Enemy_AIController.h"
#include"NavigationSystem.h"
#include"AIBlackboardData.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"



EBTNodeResult::Type UAIBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!InitEnemyE1ement(OwnerComp))return EBTNodeResult::Failed;
	if (SEController->IsPlayerDead())
	{
		SEController->LosePlayerLocation();
		//ÐÞ¸Ä×´Ì¬ÎªÑ²Âß
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Attack);
		return EBTNodeResult::Failed;
	}
	//»ñÈ¡Íæ¼Ò¾àÀë
	float EPDistance = FVector::Distance(SECharacter->GetActorLocation(), SEController->GetPlayerLocation());
	if (EPDistance <=200.f)
	{
		//ÐÞ¸Ä×´Ì¬Îª¹¥»÷
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Attack);
		SEController->OnAttackPlayer();
		return EBTNodeResult::Succeeded;
	}
	if (EPDistance > 200.f)
	{
		//ÐÞ¸Ä×´Ì¬Îª×·Öð
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Chase);
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;

}

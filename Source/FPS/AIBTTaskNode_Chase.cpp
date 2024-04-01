// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode_Chase.h"
#include"Enemy.h"
#include"Enemy_AIController.h"
#include"NavigationSystem.h"
#include"AIBlackboardData.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"


UAIBTTaskNode_Chase::UAIBTTaskNode_Chase()
{
	ForceInstancing(true);
}
EBTNodeResult::Type UAIBTTaskNode_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UE_LOG(LogTemp, Warning, TEXT("chase"));
	if (!InitEnemyE1ement(OwnerComp))return EBTNodeResult::Failed;
	float EPDistance = FVector::Distance(SECharacter->GetActorLocation(),SEController->GetPlayerLocation());
	//如果距离<200攻击目标
	if (EPDistance < 200.f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Attack);
		return EBTNodeResult::Failed;
	}
	//如果距离>1500丢失目标
	if (EPDistance > 1500.f) {
		SEController->LosePlayerLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
		UE_LOG(LogTemp, Warning, TEXT("LosePlayer"));
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode_LocalSP.h"
#include"Enemy.h"
#include"Enemy_AIController.h"
#include"NavigationSystem.h"
#include"AIBlackboardData.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"

UAIBTTaskNode_LocalSP::UAIBTTaskNode_LocalSP() 
{
	ForceInstancing(true);
}
EBTNodeResult::Type UAIBTTaskNode_LocalSP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UE_LOG(LogTemp, Warning, TEXT("local"));
	if (!InitEnemyE1ement(OwnerComp))return EBTNodeResult::Failed;
	//范围
	const float ChaseRadius = 20.f;
	//获取敌人到玩家的单位向量
	FVector SPtoSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();
	SPtoSE.Normalize();
	//探索起点是玩家位置-敌人之间距离的一点点
	const FVector ChaseOrigin = SEController->GetPlayerLocation() - 100.f * SPtoSE;
	//保存随机位置
	FVector Desloc(0.f);
	//使用导航位置获得随机点
	UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(SEController, ChaseOrigin, Desloc, ChaseRadius);
	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName,Desloc);
	SECharacter->SetMaxSpeed(600.f);
	return EBTNodeResult::Succeeded;
}
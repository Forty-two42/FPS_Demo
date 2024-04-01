// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode_Wander.h"
#include"Enemy.h"
#include"Enemy_AIController.h"
#include"NavigationSystem.h"
#include"AIBlackboardData.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UAIBTTaskNode_Wander::UAIBTTaskNode_Wander() {
	ForceInstancing(true);
}

EBTNodeResult::Type UAIBTTaskNode_Wander::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if (!InitEnemyE1ement(OwnerComp))return EBTNodeResult::Failed;
	//if(SEController->IsLockedPlayer)return EBTNodeResult::Failed;
	UE_LOG(LogTemp, Warning, TEXT("Patrol"));
	//范围1000
	const float Radius = 1000.f;
	//起始位置
	const FVector WanderOrigin = SECharacter->GetActorLocation();
	//保存随机位置
	FVector Desloc(0.f);
	//获取随机点
	UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(SEController, WanderOrigin, Desloc, Radius);
	//距离<500重新获取
	while (FVector::Distance(Desloc, WanderOrigin) < 500) {
		//重新获取随机点
		UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(SEController, WanderOrigin, Desloc, Radius);
	}
	SECharacter->SetMaxSpeed(100.f);
	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, Desloc);
	//获取停顿时长
	float TotalWaitTime = 5.f;
	//修改等待时长
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, TotalWaitTime);
	return EBTNodeResult::Succeeded;
}
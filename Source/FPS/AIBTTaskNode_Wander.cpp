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
	//��Χ1000
	const float Radius = 1000.f;
	//��ʼλ��
	const FVector WanderOrigin = SECharacter->GetActorLocation();
	//�������λ��
	FVector Desloc(0.f);
	//��ȡ�����
	UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(SEController, WanderOrigin, Desloc, Radius);
	//����<500���»�ȡ
	while (FVector::Distance(Desloc, WanderOrigin) < 500) {
		//���»�ȡ�����
		UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(SEController, WanderOrigin, Desloc, Radius);
	}
	SECharacter->SetMaxSpeed(100.f);
	//�޸�Ŀ�ĵ�
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, Desloc);
	//��ȡͣ��ʱ��
	float TotalWaitTime = 5.f;
	//�޸ĵȴ�ʱ��
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, TotalWaitTime);
	return EBTNodeResult::Succeeded;
}
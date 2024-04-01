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
	//��Χ
	const float ChaseRadius = 20.f;
	//��ȡ���˵���ҵĵ�λ����
	FVector SPtoSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();
	SPtoSE.Normalize();
	//̽����������λ��-����֮������һ���
	const FVector ChaseOrigin = SEController->GetPlayerLocation() - 100.f * SPtoSE;
	//�������λ��
	FVector Desloc(0.f);
	//ʹ�õ���λ�û�������
	UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(SEController, ChaseOrigin, Desloc, ChaseRadius);
	//�޸�Ŀ�ĵ�
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName,Desloc);
	SECharacter->SetMaxSpeed(600.f);
	return EBTNodeResult::Succeeded;
}
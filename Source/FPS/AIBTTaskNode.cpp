// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode.h"
#include"Enemy_AIController.h"
#include"Enemy.h"

bool UAIBTTaskNode::InitEnemyE1ement(UBehaviorTreeComponent& OwnerComp) {
	//����Ѿ���ʼ���ˣ�ֱ��return�������ظ�����
	if (SECharacter && SEController) return true;
	//���и�ֵ
	SEController = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner());
	if (SEController) {
		SECharacter = Cast<AEnemy>(SEController->GetPawn());
		if (SECharacter) return true;
	}
	return false;
}
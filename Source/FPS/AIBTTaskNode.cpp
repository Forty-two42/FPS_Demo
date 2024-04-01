// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTTaskNode.h"
#include"Enemy_AIController.h"
#include"Enemy.h"

bool UAIBTTaskNode::InitEnemyE1ement(UBehaviorTreeComponent& OwnerComp) {
	//如果已经初始化了，直接return，避免重复调用
	if (SECharacter && SEController) return true;
	//进行赋值
	SEController = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner());
	if (SEController) {
		SECharacter = Cast<AEnemy>(SEController->GetPawn());
		if (SECharacter) return true;
	}
	return false;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UAIBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	//��ʼ���������ͽ�ɫ,���ɹ��ͷ���false
	bool InitEnemyE1ement(UBehaviorTreeComponent& OwnerComp);
	class AEnemy_AIController* SEController;
	class AEnemy* SECharacter;

};

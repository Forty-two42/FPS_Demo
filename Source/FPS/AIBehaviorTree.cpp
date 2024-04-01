// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviorTree.h"
#include"AIBlackboardData.h"

UAIBehaviorTree::UAIBehaviorTree() {
	Blackboard = NewObject<UAIBlackboardData>();
	if (!BlackboardAsset)
	{
		//ָ�Ϻڰ�
		BlackboardAsset = Cast<UBlackboardData>(Blackboard);
	}

}

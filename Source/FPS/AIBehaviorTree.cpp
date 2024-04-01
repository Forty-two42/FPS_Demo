// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviorTree.h"
#include"AIBlackboardData.h"

UAIBehaviorTree::UAIBehaviorTree() {
	Blackboard = NewObject<UAIBlackboardData>();
	if (!BlackboardAsset)
	{
		//Ö¸ÈÏºÚ°å
		BlackboardAsset = Cast<UBlackboardData>(Blackboard);
	}

}

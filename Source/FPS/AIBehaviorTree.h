// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIBehaviorTree.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UAIBehaviorTree : public UBehaviorTree
{
	GENERATED_BODY()
public:
	UAIBehaviorTree();
protected:
	//ºÚ°å
	class UAIBlackboardData* Blackboard;	
	//

};

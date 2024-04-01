// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include"FPSCharacter.h"



UAIBlackboardData::UAIBlackboardData() {
	/*Keys.SetNum(3);
	IsMove = NewObject<UBlackboardKeyType_Bool>();
	IsIdle = NewObject<UBlackboardKeyType_Bool>();
	MoveLocation = NewObject<UBlackboardKeyType_Vector>();
	if (IsMove)
	{
		Keys[0].EntryName = "IsMove";
		Keys[0].KeyType = IsMove;
		Keys[0].bInstanceSynced = false;
	}
	if (IsIdle)
	{
		Keys[1].EntryName = "IsIdle";
		Keys[1].KeyType = IsIdle;
		Keys[1].bInstanceSynced = false;
	}
	if (MoveLocation)
	{
		Keys[2].EntryName = "MoveLocation";
		Keys[2].KeyType = MoveLocation;
		Keys[2].bInstanceSynced = false;
	}*/
}

void UAIBlackboardData::PostLoad()
{
	Super::PostLoad();
	
	Destination.EntryName = FName("Destination");
	UBlackboardKeyType_Vector* DestinationKeyType = NewObject<UBlackboardKeyType_Vector>();
	Destination.KeyType = DestinationKeyType;
	
	EnemyState.EntryName = FName("EnemyState");
	UBlackboardKeyType_Enum* EnemyStateKeyType = NewObject<UBlackboardKeyType_Enum>();
	EnemyStateKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAIState"),true);
	EnemyState.KeyType = EnemyStateKeyType;
	
	WaitTime.EntryName = FName("WaitTime");
	UBlackboardKeyType_Float* WaitTimeType = NewObject<UBlackboardKeyType_Float>();
	WaitTime.KeyType = WaitTimeType;
	
	//玩家指针
	PlayerPawn.EntryName = FName("PlayerPawn");
	UBlackboardKeyType_Object* PlayerPawnType = NewObject<UBlackboardKeyType_Object>();
	PlayerPawnType->BaseClass = AFPSCharacter::StaticClass();
	PlayerPawn.KeyType = PlayerPawnType;

	//动作是否完成
	ProcessFinish.EntryName = FName("ProcessFinish");
	UBlackboardKeyType_Bool* ProcessFinishType = NewObject<UBlackboardKeyType_Bool>();
	ProcessFinish.KeyType = ProcessFinishType;

	Keys.Add(Destination);
	Keys.Add(EnemyState);
	Keys.Add(WaitTime);
	Keys.Add(PlayerPawn);
	Keys.Add(ProcessFinish);
}

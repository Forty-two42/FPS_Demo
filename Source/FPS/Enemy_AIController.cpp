 //Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include"AIBehaviorTree.h"
#include"AIBlackboardData.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"Kismet/GameplayStatics.h"
#include"FPSCharacter.h"
#include"Enemy.h"
#include"TimerManager.h"

AEnemy_AIController::AEnemy_AIController() 
{
	PrimaryActorTick.bCanEverTick = true;
	IsLockedPlayer = false;
}

void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();
	//��ʼ�����
	FPSCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	//��ʼ������
	if(!Enemy)
		Enemy = Cast<AEnemy>(GetPawn());
}


void AEnemy_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FPSCharacter&&Enemy)Enemy->UpdateHPBarRotation(FPSCharacter->GetActorLocation());
}


void AEnemy_AIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	//Possess����BeginPlay֮ǰ���У�����������ʵ����һ�½�ɫ
	Enemy = Cast<AEnemy>(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("AI"));
	//��ʼ����Ϊ��
	//UBehaviorTree* StaticBehaviorTree = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Enemy/AIBehaviorTree.AIBehaviorTree"));
	//UBehaviorTree* BehaviorTree = DuplicateObject<UBehaviorTree>(StaticBehaviorTree, NULL);
	if (!BehaviorTree)return;
	BlackboardComp = Blackboard;
	bool IsSuccess = true;
	//BehaviorTree->BlackboardAsset = DuplicateObject<UAIBlackboardData>((UAIBlackboardData*)StaticBehaviorTree->BlackboardAsset, NULL);
	if (BehaviorTree->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BehaviorTree->BlackboardAsset) == false)) {
		IsSuccess = UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp);
	}
	if (IsSuccess) {
		BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);
		if (!BehaviorComp) {
			BehaviorComp = NewObject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
			BehaviorComp->RegisterComponent();
		}
		BrainComponent = BehaviorComp;
		check(BehaviorComp != NULL);
		BehaviorComp->StartTree(*BehaviorTree, EBTExecutionMode::Looped);
		//����Ѳ��
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Patrol);
		//Enemy->SetMaxSpeed(100.f);
	}
}

void AEnemy_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	if(BehaviorComp)
		BehaviorComp->StopTree();
}

FVector AEnemy_AIController::GetPlayerLocation() const
{
	if (FPSCharacter)return FPSCharacter->GetActorLocation();
	return FVector::ZeroVector;
}

bool AEnemy_AIController::IsPlayerDead()
{
	if (FPSCharacter)return FPSCharacter->IsDead;
	return false;
}

void AEnemy_AIController::OnSeePlayer()
{
	if (IsLockedPlayer || IsPlayerDead())return;
	//�������
	UE_LOG(LogTemp, Warning, TEXT("See You"));
	IsLockedPlayer = true;
	//�޸�״̬Ϊ׷��
	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);
	//Enemy->SetMaxSpeed(300.f);
}

void AEnemy_AIController::OnHearPlayer()
{
	if (IsLockedPlayer || IsPlayerDead())return;
	//�������
	UE_LOG(LogTemp, Warning, TEXT("Hear You"));
	IsLockedPlayer = true;
	//�޸�״̬Ϊ׷��
	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);
	//Enemy->SetMaxSpeed(300.f);
}

void AEnemy_AIController::OnAttackPlayer()
{
	Enemy->IsAttackPlayer = true;
}

void AEnemy_AIController::LosePlayerLocation()
{
	//��ʧ���
	IsLockedPlayer = false;
	Enemy->IsAttackPlayer = false;
}

UObject * AEnemy_AIController::GetPlayerPawn()
{
	return FPSCharacter;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include"Engine.h"
#include"Perception/PawnSensingComponent.h"
#include"FPSCharacter.h"
#include"Enemy_AIController.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"Components/WidgetComponent.h"
#include"Components/SphereComponent.h"
#include "SEnemyHPWidget.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	AIControllerClass = AEnemy_AIController::StaticClass();
	//实例化感官
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
	//设置视觉
	SensingComp->OnSeePawn.AddDynamic(this, &AEnemy::SeePawn);
	//实例化血条
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->SetupAttachment(RootComponent);
	//实例化攻击组件
	AttackingComp= CreateDefaultSubobject<USphereComponent>(TEXT("Attack"));
	AttackingComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("AttackingCollision"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//设置AI
	AIController = Cast<AEnemy_AIController>(GetController());
	
	//设置听觉
	SensingComp->OnHearNoise.AddDynamic(this, &AEnemy::OnHeardNoise);
	//设置血条
	SAssignNew(HPBarWidget, SEnemyHPWidget);
	HPBar->SetSlateWidget(HPBarWidget);
	HPBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HPBar->SetDrawSize(FVector2D(100.f, 10.f));
	Health_Enemy = 1.0;
	HPBarWidget->ChangeColor(Health_Enemy);
	//绑定攻击组件
	AttackingComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnSphereOverlap);
	AttackingComp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnSphereEndOverlap);
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health_Enemy -= DamageAmount;
	HPBarWidget->ChangeColor(Health_Enemy);
	if (Health_Enemy <= 0) {
			OnDead();
	}
	return DamageAmount;
}

void AEnemy::SeePawn(APawn * Pawn)
{
	AFPSCharacter* FPSChracter = Cast<AFPSCharacter>(Pawn);
	if (FPSChracter)
	{
		if (AIController) {
			AIController->OnSeePlayer();
		}
	}
}

void AEnemy::OnHeardNoise(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	AFPSCharacter* FPSChracter = Cast<AFPSCharacter>(NoiseInstigator);
	if (FPSChracter)
	{
		//AIController = Cast<AEnemy_AIController>(GetController());
		if (AIController)
		{
			AIController->OnHearPlayer();
		}
	}
}

void AEnemy::UpdateHPBarRotation(FVector SPLocation)
{
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0.f);
	FVector EndPos(SPLocation.X,SPLocation.Y,0.f);
	HPBar->SetWorldRotation(FRotationMatrix::MakeFromX(EndPos - StartPos).Rotator());
}

void AEnemy::SetMaxSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AEnemy::OnDead()
{
	//设置widget
	UUserWidget* Dead_Widget = CreateWidget<UUserWidget>(GetWorld(), Kill_Popup);
	if (Dead_Widget)
	{
		Dead_Widget->AddToViewport();
	}
	Destroy();
}

void AEnemy::OnSphereOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFPSCharacter* AttackCharacter = Cast<AFPSCharacter>(OtherActor);
	if (IsAttackPlayer&&AttackCharacter)
	{
		AttackCharacter->Ondamage();
	}
}

void AEnemy::OnSphereEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AFPSCharacter* AttackCharacter = Cast<AFPSCharacter>(OtherActor);
	if (AttackCharacter)
	{
		AttackCharacter->Recover();
	}
}




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class FPS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Ѫ��
	UPROPERTY(EditAnywhere, Category = "Health")
		float Health_Enemy;
	//Ѫ��
	UPROPERTY(VisibleAnywhere,Category=Mesh)
		class UWidgetComponent* HPBar;
	//�й����
	UPROPERTY(EditAnywhere,Category=Mesh)
		class UPawnSensingComponent* SensingComp;
	//�������
	UPROPERTY(EditAnywhere, Category = "Attack")
		class USphereComponent* AttackingComp;
	//�Ƿ񹥻����
	UPROPERTY(BlueprintReadOnly)
		bool IsAttackPlayer = false;
	//AI
	UPROPERTY()
		class AEnemy_AIController* AIController;
	//���������ؼ�
	UPROPERTY(EditAnyWhere, Category="Widget")
		TSubclassOf<UUserWidget>Kill_Popup;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//����
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//������ɫ
	UFUNCTION()
		void SeePawn(APawn* Pawn);
	//����ǹ��
	UFUNCTION()
		void OnHeardNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);
	UFUNCTION()
		void UpdateHPBarRotation(FVector SPLocation);

	//�����ٶ�
	void SetMaxSpeed(float Speed);
	//����
	UFUNCTION()
		void OnDead();
	//����
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,    //����ʱ������壬ͨ���ǿ��Ƶ���
			UPrimitiveComponent* OterComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	//ֹͣ����
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
private:
	//Ѫ������
	TSharedPtr<class SEnemyHPWidget> HPBarWidget;
};

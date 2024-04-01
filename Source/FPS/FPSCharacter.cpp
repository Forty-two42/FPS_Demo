// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include"Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include"Components/SkeletalMeshComponent.h"
#include"Components/StaticMeshComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"TimerManager.h"
#include"Engine/SkeletalMeshSocket.h"
#include"Projectile.h"
#include"Weapon.h"
#include"Weapon_M4A1.h"
#include"Sound/SoundCue.h"
#include"Kismet/GameplayStatics.h"
#include"Particles/ParticleEmitter.h"
#include"Particles/ParticleSystemComponent.h"
#include"Components/PawnNoiseEmitterComponent.h"
#include"Components/WidgetComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//创建摄像机
	FPSCameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	check(FPSCameraComponent != NULL);
	//添加到头部组件
	FPSCameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Camera"));
	// 启用Pawn控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;
	//设置血条
	health = 1.0;
	armor = 1.0;
	//设置可以蹲下站起
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	//武器添加的位置
	Weapon_Loc = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon_Loc->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
	//瞄准镜位置
	ADSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCamera"));
	ADSCamera->AttachTo(Weapon_Loc);
	//噪声
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	//初始化UI
	UUserWidget* FPS_HUD = CreateWidget<UUserWidget>(GetWorld(),FPS_Widget);
	FPS_HUD->AddToViewport();
	//生成武器
	AK_47= GetWorld()->SpawnActor<AWeapon>();
	if (AK_47) {
		AK_47->GetWeaponMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
	}
	M4A1 = GetWorld()->SpawnActor<AWeapon_M4A1>();
	if (M4A1)
	{
		M4A1->GetWeaponMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
		M4A1->GetWeaponMesh()->SetVisibility(false, false);
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!damage&&armor < 1.0)
		armor=FMath::Clamp<float>(armor + 0.001, 0.0f, 1.0f);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//设置移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	//切换跑步
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AFPSCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFPSCharacter::EndRun);
	//切换蹲伏
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSCharacter::MyCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFPSCharacter::EndCrouch);
	//设置视角移动
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &AFPSCharacter::AddControllerPitchInput);
	//跳跃
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::Startjump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::Stopjump);
	//开火
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this,&AFPSCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::EndFire);
	//瞄准
	PlayerInputComponent->BindAction("AimDownSights", IE_Pressed, this, &AFPSCharacter::ADS);
	PlayerInputComponent->BindAction("AimDownSights", IE_Released, this, &AFPSCharacter::EndADS);
	//装弹
	PlayerInputComponent->BindAction("Reloading", IE_Pressed, this, &AFPSCharacter::Reloading);
	//切换武器
	PlayerInputComponent->BindAction("SelectPrimary", IE_Pressed, this, &AFPSCharacter::SelectPrimary);
	PlayerInputComponent->BindAction("SelectSecondary", IE_Pressed, this, &AFPSCharacter::SelectSecondary);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::Startjump()
{
	bPressedJump = true;
}

void AFPSCharacter::Stopjump()
{
	bPressedJump = false;
}

void AFPSCharacter::Run()
{
	if (Aiming == false) {
		isSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = 1200;
	}
}

void AFPSCharacter::EndRun()
{
	isSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AFPSCharacter::MyCrouch()
{
	Crouch();
	if (isSprint)isSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void AFPSCharacter::EndCrouch()
{
	UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AFPSCharacter::Ondamage()
{
	if (armor >= 0.3)armor -= 0.3;
	else if (armor > 0 && (health + armor)>= 0.3) {
		health -= (0.3 - armor);
		armor = 0.0f;
	}
	else if (health >= 0.3)
	{
		health -= 0.3;
		//初始化UI
		UUserWidget* Damage_HUD = CreateWidget<UUserWidget>(GetWorld(), Damage_Widget);
		Damage_HUD->AddToViewport();

	}
	else health = 0.0f;
	damage = true;
	if (health == 0.f)Dead();
}


void AFPSCharacter::Recover()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSCharacter::Delay, 3.0f, true);
}

void AFPSCharacter::Delay()
{
	damage = false;
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AFPSCharacter::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShoot, this, &AFPSCharacter::Fire, Firerate, true, 0.0f);
}

void AFPSCharacter::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShoot);
}

void AFPSCharacter::ADS()
{
	if (Isreloading == false) {
		FPSCameraComponent->Deactivate();
		ADSCamera->Activate();
		GetCharacterMovement()->MaxWalkSpeed = 100;
		Aiming = true;
		if (isSprint)EndRun();
	}
}

void AFPSCharacter::EndADS()
{
	FPSCameraComponent->Activate();
	ADSCamera->Deactivate();
	GetCharacterMovement()->MaxWalkSpeed = 600;
	Aiming = false;
}

void AFPSCharacter::Reloading()
{
	if (WeaponSelected == 1)
	{
		AK_47->Reloading();
		Ammo_C = AK_47->Ammo_C;
		Ammo_B = AK_47->Ammo_B;
	}
	if (WeaponSelected == 2)
	{
		M4A1->Reloading();
		Ammo_C = M4A1->Ammo_C;
		Ammo_B = M4A1->Ammo_B;
	}
	Isreloading = true;
	GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AFPSCharacter::EndReload, 1.0f,true, 3.3f);
	if (isSprint)EndRun();
	if (Aiming)EndADS();
}

void AFPSCharacter::EndReload()
{
	Isreloading = false;
	GetWorldTimerManager().ClearTimer(TimerHandle_Reload);
}

void AFPSCharacter::SelectPrimary()
{
	WeaponSelected = 1;
	Ammo_C = AK_47->Ammo_C;
	Ammo_B = AK_47->Ammo_B;
	M4A1->GetWeaponMesh()->SetVisibility(false,false);
	AK_47->GetWeaponMesh()->SetVisibility(true, true);
}

void AFPSCharacter::SelectSecondary()
{
	Ammo_C = M4A1->Ammo_C;
	Ammo_B = M4A1->Ammo_B;
	AK_47->GetWeaponMesh()->SetVisibility(false, false);
	M4A1->GetWeaponMesh()->SetVisibility(true, true);
	WeaponSelected = 2;

}

void AFPSCharacter::Dead()
{
	IsDead = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("YOU ARE DEAD"));
}

void AFPSCharacter::Fire()
{
	if (Ammo_C&&Isreloading==false&&isSprint==false)
	{
		//生成子弹
		if (Aiming)
		{
			if(WeaponSelected==1)
				GetWorld()->SpawnActor<AProjectile>(Bullet, AK_47->GetWeaponMesh()->GetSocketTransform("Bullet"));
			if(WeaponSelected==2)
				GetWorld()->SpawnActor<AProjectile>(Bullet, M4A1->GetWeaponMesh()->GetSocketTransform("Bullet"));
		}
		else
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);
			FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformFVector4(MuzzleOffset);
			FRotator MuzzleRotation = CameraRotation;
			GetWorld()->SpawnActor<AProjectile>(Bullet, MuzzleLocation, MuzzleRotation);
			CameraRotation.Pitch += 10;
		}
		//生成特效
		UParticleSystemComponent* Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleComp, AK_47->GetWeaponMesh()->GetSocketByName("Particle")->GetSocketTransform(AK_47->GetWeaponMesh()));
		FVector NewScale;
		NewScale.X = 0.25; NewScale.Y = 0.25; NewScale.Z = 0.25;
		Particle->SetWorldScale3D(NewScale);
		MakeNoise(1.0f, this, GetActorLocation());
		Shoot = LoadObject<USoundCue>(this, TEXT("SoundCue'/Game/Weapon/wav/Gun_1_1_Cue.Gun_1_1_Cue'"));
		UGameplayStatics::PlaySoundAtLocation(this, Shoot, GetActorLocation());
		Ammo_C--;
		if (WeaponSelected == 1)AK_47->Ammo_C--;
		if (WeaponSelected == 2)M4A1->Ammo_C--;
	}
}
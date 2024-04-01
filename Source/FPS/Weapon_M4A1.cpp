// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_M4A1.h"
#include"Components/SceneComponent.h"
#include"Components/SkeletalMeshComponent.h"

// Sets default values
AWeapon_M4A1::AWeapon_M4A1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//初始化网格体
	SceneComp=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;
	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalComp"));
	SkeletalComp->SetupAttachment(RootComponent); 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAssert(TEXT("SkeletalMesh'/Game/Weapon/Weapon/M4A1/M4A1_weapon002.M4A1_weapon002'"));
	SkeletalComp->SetSkeletalMesh(MeshAssert.Object);
	SkeletalComp->SetRelativeLocation(FVector(28.f, -37.f, -119.f));
	SkeletalComp->SetRelativeScale3D(FVector(8.75, 8.75, 8.75));
	SkeletalComp->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}
// Called when the game starts or when spawned
void AWeapon_M4A1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_M4A1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_M4A1::Reloading()
{
	if (Ammo_C < 50)
	{
		if (Ammo_B >= 50 - Ammo_C) {
			Ammo_B -= 50 - Ammo_C;
			Ammo_C = 50;
		}
		else
		{
			Ammo_C += Ammo_B;
			Ammo_B = 0;
		}
	}
}


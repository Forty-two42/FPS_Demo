// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include"Particles/ParticleSystemComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalComp1"));
	RootComponent = SkeletalComp;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAssert1(TEXT("SkeletalMesh'/Game/Weapon/Weapon/AK47/AK.AK'"));
	SkeletalComp->SetSkeletalMesh(MeshAssert1.Object);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Reloading()
{
	if (Ammo_C < 30)
	{
		if (Ammo_B >= 30 - Ammo_C) {
			Ammo_B -= 30 - Ammo_C;
			Ammo_C = 30;
		}
		else
		{
			Ammo_C += Ammo_B;
			Ammo_B = 0;
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo_pick_M4A1.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"
#include"FPSCharacter.h"
#include"Weapon_M4A1.h"

// Sets default values
AAmmo_pick_M4A1::AAmmo_pick_M4A1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(Collision);

}

// Called when the game starts or when spawned
void AAmmo_pick_M4A1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmo_pick_M4A1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmo_pick_M4A1::NotifyActorBeginOverlap(AActor * OtherActor)
{
	AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(OtherActor);
	if (FPSCharacter)
	{
		FPSCharacter->M4A1->Ammo_B += 30;
		FPSCharacter->Ammo_B = FPSCharacter->M4A1->Ammo_B;
		Destroy();
	}
}


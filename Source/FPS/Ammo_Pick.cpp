// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo_Pick.h"
#include"Components/StaticMeshComponent.h"
#include"FPSCharacter.h"
#include"Weapon.h"
#include"Components/SphereComponent.h"

// Sets default values
AAmmo_Pick::AAmmo_Pick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAmmo_Pick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmo_Pick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmo_Pick::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(OtherActor);
	if (FPSCharacter) {
		FPSCharacter->AK_47->Ammo_B += 30;
		FPSCharacter->Ammo_B = FPSCharacter->AK_47->Ammo_B;
		Destroy();
	}

}


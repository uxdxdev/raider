// Fill out your copyright notice in the Description page of Project Settings.

#include "Raider.h"
#include "Monster.h"


// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMonster::AMonster(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Speed = 20;
	HitPoints = 20;
	Experience = 0;
	BPLoot = NULL;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;
	SightSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
	SightSphere->AttachTo(RootComponent);
	AttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	APawn *avatar = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;
	FVector toPlayer = avatar->GetActorLocation() -	GetActorLocation();
	
	this->GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction

	float distanceToPlayer = toPlayer.Size();
	// If the player is not in the SightSphere of the monster,
	// go back
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		// If the player is out of sight,
		// then the enemy cannot chase
		return;
	}
	toPlayer /= distanceToPlayer; // normalizes the vector
	
	FRotator Rotation = toPlayer.Rotation();
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Speed * DeltaTime);

	// Actually move the monster towards the player a bit
	//AddMovementInput(toPlayer, Speed * DeltaTime);
	// At least face the target
	// Gets you the rotator to turn something
	// that looks in the `toPlayer` direction
	//FRotator toPlayerRotation = toPlayer.Rotation();
	//toPlayerRotation.Pitch = 0; // 0 off the pitch
	//RootComponent->SetWorldRotation(toPlayerRotation);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


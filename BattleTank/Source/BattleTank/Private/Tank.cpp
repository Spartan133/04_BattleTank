// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}


// Set default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	auto TankName = this->GetName();
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Tank Dead"), *TankName);  // TODO Comment out Log Message
		OnDeath.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("%s DamageAmount = %f, DamageToApply = %i, CurrentHealth = %i"), *TankName, DamageAmount, DamageToApply, CurrentHealth);

	return DamageToApply;
}

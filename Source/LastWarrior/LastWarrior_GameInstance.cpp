// Fill out your copyright notice in the Description page of Project Settings.


#include "LastWarrior_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULastWarrior_GameInstance::SetPlayerHP(int HP)
{
	PlayerHP = HP;
}

void ULastWarrior_GameInstance::AddDiamond(int Amount)
{
	DiamondCollectedCount += Amount;
}

void ULastWarrior_GameInstance::ChangeLevel(int LevelIndex)
{
	if (LevelIndex <= 0) return;
	
	CurrentLevelIndex = LevelIndex;
	
	FString LevelNameString = FString::Printf(TEXT("Level_%d"), LevelIndex);
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelNameString));
}
void ULastWarrior_GameInstance::RestartGame()
{
	PlayerHP = 100;
	DiamondCollectedCount = 0;
	IsDoubleJumpUnlocked = false;
	
	CurrentLevelIndex = 1;
	ChangeLevel(CurrentLevelIndex);
	
}
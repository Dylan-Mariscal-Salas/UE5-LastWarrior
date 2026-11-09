// Fill out your copyright notice in the Description page of Project Settings.


#include "LastWarrior_GameInstance.h"

void ULastWarrior_GameInstance::SetPlayerHP(int HP)
{
	PlayerHP = HP;
}

void ULastWarrior_GameInstance::AddDiamond(int Amount)
{
	DiamondCollectedCount += Amount;
}
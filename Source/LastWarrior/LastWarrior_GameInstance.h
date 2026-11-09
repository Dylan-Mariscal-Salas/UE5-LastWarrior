// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LastWarrior_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LASTWARRIOR_API ULastWarrior_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerHP = 100;
	
	void SetPlayerHP(int HP);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int DiamondCollectedCount = 0;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool IsDoubleJumpUnlocked = false;
	
	void AddDiamond(int Amount);
};

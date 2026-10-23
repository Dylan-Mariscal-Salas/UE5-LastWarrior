// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class LASTWARRIOR_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* HPText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* DiamondText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* LevelText;
	
	void SetHP(int NewHp);
	void SetDiamonds(int Amount);
	void SetLevel(int index);
};

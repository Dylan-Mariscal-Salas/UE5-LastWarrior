// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "Components/TextRenderComponent.h"
#include "PaperZDAnimInstance.h"
#include "Engine/TimerHandle.h"
#include "Components/BoxComponent.h"


#include "Enemy.generated.h"


/**
 * 
 */
UCLASS()
class LASTWARRIOR_API AEnemy : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* PlayerDetectorSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlayerCharacter* FollowTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* AttackCollisionBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StopDistanceToTarget = 100.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAlive = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsStunned = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperZDAnimSequence* AttackAnimationSequence;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextRenderComponent* HPText;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int HitPoints = 100;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanAttack = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttackDamage = 25;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackStunDuration = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackCooldownInSeconds = 1.5f;
	
	FZDOnAnimationOverrideEndSignature OnAttackOverrideDelegate;
	
	FTimerHandle StunTimer;
	FTimerHandle AttackCooldownTimer;
	
	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	bool ShouldMoveToTarget();
	void UpdateDirection(float MoveDirection);
	
	UFUNCTION()
	
	void DetectorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	UFUNCTION()
	void DetectorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void UpdateHP(int NewHP);
	
	void TakeDamage(int DamageAmount, float StunDuration);
	
	void Attack();
	void OnAttackCooldownTimerTimeout();
	void OnAttackOverrideAnimEnd(bool Completed);
	
	void Stun(float DurationInSeconds);
	void OnStunTimerTimeout();
	
	UFUNCTION()
	void AttackBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void EnableAttackCollisionBox(bool Enabled);
	
};

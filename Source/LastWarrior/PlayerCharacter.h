// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "PaperZDAnimInstance.h"
#include "Components/BoxComponent.h"
#include "Engine/TimerHandle.h"

#include "PlayerCharacter.generated.h"


/**
 * 
 */
UCLASS()
class LASTWARRIOR_API APlayerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperZDAnimSequence* AttackAnimationSequence;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* AttackCollisionBox;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAlive = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanMove = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanAttack = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsStunned = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int HitPoints = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttackDamage = 25;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackStunDuration = 0.3f;
	
	FTimerHandle StunTimer;
	
	FZDOnAnimationOverrideEndSignature OnAttackOverrideEndDelegate;
	
	APlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);
	void JumpStarted(const FInputActionValue& Value);
	void JumpEnded(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	
	void UpdateDirection(float MoveDirection);
	
	void OnAttackOverrideAnimEnd (bool Completed);
	
	UFUNCTION()
	void AttackBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void EnableAttackCollisionBox(bool Enabled);

	void TakeDamage(int DamageAmount, float StunDuration);
	void UpdateHp(int NewHP);
	
	void Stun(float DurationInSeconds);
	void OnStunTimerTimout();
};

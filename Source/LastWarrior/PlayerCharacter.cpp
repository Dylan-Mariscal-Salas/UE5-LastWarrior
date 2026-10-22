// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Enemy.h"
#include "Evaluation/IMovieSceneEvaluationHook.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionBox"));
	AttackCollisionBox->SetupAttachment(RootComponent);
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Adding input mapping context
	
	// Get PlayerController
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	// Verify if Player controller is not NULL
	if (PlayerController)
	{
		//Getting Subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()) ;
		if (Subsystem)
		{
			Subsystem -> AddMappingContext(InputMappingContext, 0);
		}
	}
	
	OnAttackOverrideEndDelegate.BindUObject(this, &APlayerCharacter::OnAttackOverrideAnimEnd);
	AttackCollisionBox->OnComponentBeginOverlap.AddDynamic(this,&APlayerCharacter::AttackBoxOverlapBegin);
	EnableAttackCollisionBox(false);
}
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up input action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,this,&APlayerCharacter::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::JumpEnded);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &APlayerCharacter::JumpEnded);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
		
	} 
}
	
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	float MoveActionValue = Value.Get<float>();
	
	if (IsAlive && CanMove && !IsStunned)
	{
		FVector Direction = FVector(1.0f,0.0f,0.0f);
		AddMovementInput(Direction,MoveActionValue);
		UpdateDirection(MoveActionValue);
	}
}

void APlayerCharacter::UpdateDirection(float MoveDirection)
{
	FRotator CurrentRotation = Controller->GetControlRotation();
	if (MoveDirection < 0.0f)
	{
		if (CurrentRotation.Yaw != 180.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch,180.0f,CurrentRotation.Roll));
		}
	}
	else if (MoveDirection > 0.0f)
	{
		if (CurrentRotation.Yaw != 0.0f)
		{
			Controller->SetControlRotation(FRotator(CurrentRotation.Pitch,0.0f,CurrentRotation.Roll));
		}
	}
	
}

void APlayerCharacter::JumpStarted(const FInputActionValue& Value)
{
	if (IsAlive && CanMove && !IsStunned)
	{
		Jump();
	}
}

void APlayerCharacter::JumpEnded(const FInputActionValue& Value)
{
	StopJumping();
}

void APlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (IsAlive && CanAttack && !IsStunned)
	{
		CanMove = false;
		CanAttack = false;
		
		GetAnimInstance()->PlayAnimationOverride(AttackAnimationSequence,
			FName("DefaultSlot"),1.0f,0.0f,OnAttackOverrideEndDelegate);
	}
}

void APlayerCharacter::OnAttackOverrideAnimEnd (bool Completed)
{
	CanMove = true;
	CanAttack = true;
	
}

void APlayerCharacter::AttackBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->TakeDamage(AttackDamage, AttackStunDuration);
		
	}
}

void APlayerCharacter::EnableAttackCollisionBox(bool Enabled)
{
	if (Enabled)
	{
		AttackCollisionBox -> SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AttackCollisionBox -> SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,
			ECR_Overlap);
	}
	else
	{
		AttackCollisionBox -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AttackCollisionBox -> SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,
			ECR_Ignore);
	}
}

void APlayerCharacter::TakeDamage(int DamageAmount, float StunDuration)
{
	if (!IsAlive) return ;
	Stun(StunDuration);
	
	UpdateHp(HitPoints - DamageAmount);
	
	if (HitPoints <= 0)
	{
		UpdateHp(0);
		
		CanAttack = false;
		CanMove = false;
		IsAlive = false;
		
		GetAnimInstance()->JumpToNode(FName("JumpDie"), FName("SamuraiStateMachine"));
		EnableAttackCollisionBox(false);
	}
	else
	{
		GetAnimInstance()->JumpToNode(FName("JumpTakeHit"),FName("SamuraiStateMachine"));
	}
}


void APlayerCharacter::UpdateHp(int NewHP)
{
	HitPoints = NewHP;
}


void APlayerCharacter::Stun(float DurationInSeconds)
{
	IsStunned = true;
	
	bool IsTimerActive = GetWorldTimerManager().IsTimerActive(StunTimer);
	
	if (IsTimerActive)
	{
		GetWorldTimerManager().ClearTimer(StunTimer);
	}

	
	GetWorldTimerManager().SetTimer(StunTimer, this, &APlayerCharacter::OnStunTimerTimout, 1.0f,
		false, DurationInSeconds);
	
	GetAnimInstance()->StopAllAnimationOverrides();
	
	EnableAttackCollisionBox(false);
	
}
void APlayerCharacter::OnStunTimerTimout()
{
	IsStunned = false;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/SPIRV-Headers/include/spirv/unified1/spirv.h>

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerDetectorSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectorSphere"));
	PlayerDetectorSphere->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerDetectorSphere->OnComponentBeginOverlap.AddDynamic(this,&AEnemy::DetectorOverlapBegin);
	PlayerDetectorSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::DetectorOverlapEnd);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsAlive && FollowTarget)
	{
		float MoveDirection = (FollowTarget -> GetActorLocation().X - GetActorLocation().X) > 0.0f ? 1.0 : -1.0f;
		UpdateDirection(MoveDirection);
		if (ShouldMoveToTarget())
		{
			if (CanMove)
			{
				FVector WorldDirection = FVector(1.0f,0.0f,0.0f);
				AddMovementInput(WorldDirection, MoveDirection);
			}
		}
		else
		{
			//Attack
		}
	}
}

void AEnemy::UpdateDirection(float MoveDirection)
{
	
	
	FRotator CurrentRotation = GetActorRotation();
	if (MoveDirection < 0.0f)
	{
		if (CurrentRotation.Yaw != 180.0f)
		{
			SetActorRotation(FRotator(CurrentRotation.Pitch,180.0f,CurrentRotation.Roll));
		}
	}
	else if (MoveDirection > 0.0f)
	{
		if (CurrentRotation.Yaw != 0.0f)
		{
			SetActorRotation(FRotator(CurrentRotation.Pitch,0.0f,CurrentRotation.Roll));
		}
	}
}


	

void AEnemy::DetectorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		FollowTarget = Player;
	}
}
	
	

void AEnemy::DetectorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		FollowTarget = NULL;
	}
}

bool AEnemy::ShouldMoveToTarget()
{
	bool Result= false;
	if (FollowTarget)
	{
		float DistanceToTarget = abs(FollowTarget->GetActorLocation().X - GetActorLocation().X);
		Result = DistanceToTarget > StopDistanceToTarget;
	}
	
	return Result;
}

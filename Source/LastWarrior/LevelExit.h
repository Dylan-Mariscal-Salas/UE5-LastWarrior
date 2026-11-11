

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundBase.h"
#include "Engine/TimerHandle.h"
#include "LastWarrior_GameInstance.h"


#include "LevelExit.generated.h"

UCLASS()
class LASTWARRIOR_API ALevelExit : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* DoorFlipbook;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PlayerEnterSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelIndex = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTimeInSeconds = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActive = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ULastWarrior_GameInstance* MyGameInstance;
	
	FTimerHandle WaitTimer;
	
	ALevelExit();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void AttackBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void OnWaitTimerTimeout();
};

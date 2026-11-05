#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "CollectibleItem.generated.h"

UENUM(BlueprintType)
enum class CollectableType :uint8
{
	Diamond,
	HealthPotion,
	DoubleJumpUpgrade
};

UCLASS()
class LASTWARRIOR_API ACollectibleItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectibleItem();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* ItemFlipbook;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CollectableType Type;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

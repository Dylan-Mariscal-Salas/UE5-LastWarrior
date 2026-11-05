


#include "CollectibleItem.h"
#include "PlayerCharacter.h"


ACollectibleItem::ACollectibleItem()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	
	ItemFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ItemFlipbook"));
	ItemFlipbook->SetupAttachment(RootComponent);
}

void ACollectibleItem::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComp -> OnComponentBeginOverlap.AddDynamic(this, &ACollectibleItem::OverlapBegin);
	
}

void ACollectibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectibleItem::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	
	if (Player && Player->IsAlive)
	{
		Player->CollectItem(Type);
		Destroy();
	}
}


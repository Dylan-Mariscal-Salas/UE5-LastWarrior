
#include "LevelExit.h"
#include "PlayerCharacter.h"
#include "LastWarrior_GameInstance.h"
#include "Kismet/GameplayStatics.h"



ALevelExit::ALevelExit()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComponent);
	
	DoorFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DoorFlipbook"));
	DoorFlipbook->SetupAttachment(RootComponent);
	
	DoorFlipbook->SetPlayRate(0.0f);
	DoorFlipbook->SetLooping(false);
}


void ALevelExit::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ALevelExit::AttackBoxOverlapBegin);
	
	DoorFlipbook->SetPlaybackPosition(0.0f, false);
	
	
	
}


void ALevelExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelExit::AttackBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	
	
	
	if(Player && Player->IsAlive)
	{
		if(IsActive)
		{
			IsActive = false;
			Player->Deactivate();
			
			DoorFlipbook->SetPlayRate(1.0f);
			DoorFlipbook->PlayFromStart();
			
			UGameplayStatics::PlaySound2D(GetWorld(),PlayerEnterSound);
		
			
			
			GetWorldTimerManager().SetTimer(WaitTimer,this,&ALevelExit::OnWaitTimerTimeout,1.0f,0,WaitTimeInSeconds);
		}
	}
}
	
void ALevelExit::OnWaitTimerTimeout()
{
	MyGameInstance = Cast<ULastWarrior_GameInstance>(GetGameInstance());
	if (MyGameInstance)
	{
		MyGameInstance->ChangeLevel(LevelIndex);
	}
	
	
}

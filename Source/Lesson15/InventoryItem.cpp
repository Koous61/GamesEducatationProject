#include "InventoryItem.h"

AInventoryItem::AInventoryItem()
{
	PrimaryActorTick.bCanEverTick = true;
	DistanceDrop = 300.0f;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInventoryItem::InteractItem(ALesson15Character* Character)
{
	
}



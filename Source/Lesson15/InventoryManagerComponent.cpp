#include "InventoryManagerComponent.h"

UInventoryManagerComponent::UInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryManagerComponent::AddItem(AInventoryItem* NewItem, int32 CountItem)
{
	NewItem->SetActorHiddenInGame(true);
	auto* CurrentCount = MapItem.Find(NewItem);
	if (MapItem.Find(NewItem) == nullptr)
	{
		MapItem.Add(NewItem, CountItem);
	}
	else
	{
		CurrentCount += CountItem;
	}
}

bool UInventoryManagerComponent::UseItem(AInventoryItem* SelectItem)
{
	if (SelectItem)
	{
		auto* Character = Cast<ALesson15Character>(GetOwner());
		auto* CurrentCount = MapItem.Find(SelectItem);
		if (Character)
		{
			if (*CurrentCount == 1)
			{
				MapItem.Remove(SelectItem);
			}
			else
			{
				CurrentCount -= 1;
			}
			SelectItem->InteractItem(Character);
			return true;
		}
	}
	return false;
}

void UInventoryManagerComponent::UseFirstItem()
{
	TArray<AInventoryItem*> Keys;
	MapItem.GetKeys(Keys);
	UseItem(Keys[0]);
}

void UInventoryManagerComponent::DropItem(AInventoryItem* SelectItem, int32 CountItem)
{
	auto* CurrentCount = MapItem.Find(SelectItem);
	if (*CurrentCount >= CountItem)
	{
		const auto* Owner = GetOwner();
		for (int i = 0; i < CountItem; i++)
		{
			const FVector LocationSpawn = Owner->GetActorLocation() + SelectItem->DistanceDrop;
			const FRotator RotatorSpawn = Owner->GetActorRotation();
			SelectItem->SetActorHiddenInGame(false);
			SelectItem->SetActorLocationAndRotation(LocationSpawn, RotatorSpawn);
		}
		CurrentCount -= CountItem;
		if (CurrentCount == 0)
		{
			MapItem.Remove(SelectItem);
		}
	}
}

void UInventoryManagerComponent::DropFirstItem()
{
	TArray<AInventoryItem*> Keys;
	MapItem.GetKeys(Keys);
	DropItem(Keys[0], *MapItem.Find(Keys[0]));
}

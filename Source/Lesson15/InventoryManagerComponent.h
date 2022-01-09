#pragma once
#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryManagerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(AInventoryItem* NewItem, int32 CountItem);

	UFUNCTION(BlueprintCallable)
	bool UseItem(AInventoryItem* SelectItem);

	UFUNCTION(BlueprintCallable)
	void UseFirstItem();

	UFUNCTION(BlueprintCallable)
	void DropItem(AInventoryItem* SelectItem, int32 CountItem);

	UFUNCTION(BlueprintCallable)
	void DropFirstItem();

	
private:
	UPROPERTY()
	TMap<AInventoryItem*, int32> MapItem;
};

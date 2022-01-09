#pragma once
#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Lesson15Character.h"
#include "HealthBag.generated.h"

UCLASS()
class AHealthBag : public AInventoryItem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void InteractItem(ALesson15Character* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	int32 Health;
};

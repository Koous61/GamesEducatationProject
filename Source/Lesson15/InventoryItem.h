#pragma once
#include "CoreMinimal.h"
#include "Lesson15Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS()
class AInventoryItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
public:	
	AInventoryItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void InteractItem(ALesson15Character* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceDrop;

};

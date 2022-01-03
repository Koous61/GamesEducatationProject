#pragma once
#include "CoreMinimal.h"

#include "BaseWeapon.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LESSON15_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponManagerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceToDropWeapon;

	UFUNCTION(BlueprintCallable)
	bool SetCurrentWeapon(ABaseWeapon* NewWeapon);

	UFUNCTION(BlueprintCallable)
	bool DropCurrentWeapon();

	UFUNCTION(BlueprintCallable)
	void InteractCurrentWeapon();
};

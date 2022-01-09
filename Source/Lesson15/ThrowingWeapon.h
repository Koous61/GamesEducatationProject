#pragma once
#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ThrowingWeapon.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractThrowingWeaponDynamic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractThrowingWeaponMulticast);

UCLASS()
class AThrowingWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	AThrowingWeapon();
	
	virtual void InteractWeapon() override;

	FTimerHandle TimerToBoom;

	UFUNCTION(Client, Unreliable)
	void InteractWeaponClient();

	UFUNCTION(Server, Unreliable)
	void InteractWeaponServer();

	UFUNCTION(NetMulticast, Unreliable)
	void InteractWeaponMulticast();

	void OnTimerToBoom();

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ParticleSystem;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	FInteractThrowingWeaponDynamic OnInteractThrowingWeaponDynamic;

	UPROPERTY(BlueprintAssignable)
	FInteractThrowingWeaponMulticast OnInteractThrowingWeaponMulticast;
};

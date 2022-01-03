#pragma once
#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "FireWeapon.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractFireWeaponDynamic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractFireWeaponMulticast);

UCLASS()
class LESSON15_API AFireWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:	
	AFireWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RateFire;

	UPROPERTY(Replicated)
	bool bIsReadyFire;

	FTimerHandle FireHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ParticleSystem;
	
	virtual void InteractWeapon() override;

	UFUNCTION(Client, Unreliable)
	void InteractWeaponClient();

	UFUNCTION(Server, Unreliable)
	void InteractWeaponServer();

	UFUNCTION(NetMulticast, Unreliable)
	void InteractWeaponMulticast();

	void ReadyFire();

	FInteractFireWeaponDynamic OnInteractFireWeaponDynamic;

	UPROPERTY(BlueprintAssignable)
	FInteractFireWeaponMulticast OnInteractFireWeaponMulticast;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

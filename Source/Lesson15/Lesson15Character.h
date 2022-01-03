#pragma once
#include "CoreMinimal.h"

#include "BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Lesson15Character.generated.h"

UCLASS(config=Game)
class ALesson15Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWeaponManagerComponent* WeaponManagerComponent;
public:
	ALesson15Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Damage);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void OnSetWeapon(ABaseWeapon* NewWeapon = nullptr);

protected:

	void OnResetVR();

	void OnFire();

	void OnDropWeapon();

	UFUNCTION(Server, Unreliable)
	void OnDropWeaponServer();

	UFUNCTION(NetMulticast, Unreliable)
	void OnDropWeaponMulticast();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void RespawnCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};


#include "Lesson15Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "InventoryManagerComponent.h"
#include "WeaponManagerComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"


ALesson15Character::ALesson15Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	MaxHealth = 100.f;
	Health = 100.0f;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("WeaponManager"));
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("InventoryManager"));
}

void ALesson15Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &ALesson15Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALesson15Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALesson15Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALesson15Character::LookUpAtRate);
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALesson15Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALesson15Character::TouchStopped);
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ALesson15Character::OnResetVR);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALesson15Character::OnFire);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &ALesson15Character::OnDropWeapon);
}


void ALesson15Character::ApplyDamage(float Damage)
{
	AddHealthServer(-1 * Damage);
}

void ALesson15Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALesson15Character, Health);
}

void ALesson15Character::AddHealthClient_Implementation(float NewValue)
{
	AddHealthServer(NewValue);
}

void ALesson15Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ALesson15Character::OnFire()
{
	WeaponManagerComponent->InteractCurrentWeapon();
}

void ALesson15Character::OnDropWeapon()
{
	OnDropWeaponServer();
}

void ALesson15Character::AddHealthServer_Implementation(float NewValue)
{
	Health += NewValue;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	if (FMath::IsNearlyEqual(Health, 0.0f))
	{
		RespawnCharacter();
	}
}

void ALesson15Character::OnSetWeapon(ABaseWeapon* NewWeapon)
{
	WeaponManagerComponent->CurrentWeapon = NewWeapon;
}

void ALesson15Character::OnDropWeaponServer_Implementation()
{
	OnDropWeaponMulticast();
}

void ALesson15Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ALesson15Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ALesson15Character::RespawnCharacter()
{
	Health = 100;
	SetActorLocation(FVector(0, 0, 0), false, nullptr, ETeleportType::TeleportPhysics);
}

void ALesson15Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALesson15Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALesson15Character::OnDropWeaponMulticast_Implementation()
{
	WeaponManagerComponent->DropCurrentWeapon();
}

void ALesson15Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALesson15Character::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

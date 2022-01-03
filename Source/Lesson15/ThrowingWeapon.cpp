#include "ThrowingWeapon.h"

#include "Lesson15Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AThrowingWeapon::AThrowingWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(GetBoxComponent());
	ProjectileMovementComponent->InitialSpeed = 300.0f;
	ProjectileMovementComponent->MaxSpeed = 500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.2f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void AThrowingWeapon::InteractWeapon()
{
	if (GetOwner())
	{
		auto* Character = Cast<ALesson15Character>(GetOwner());
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Character->OnSetWeapon();
		SetOwner(nullptr);
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(400,0,0));
		ProjectileMovementComponent->ProjectileGravityScale = 0.2f;
		GetWorld()->GetTimerManager().SetTimer(TimerToBoom, this, &AThrowingWeapon::OnTimerToBoom, 4.0f, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AThrowingWeapon::InteractWeapon Owner is nullptr"));
	}
}

void AThrowingWeapon::OnTimerToBoom()
{
	OnInteractThrowingWeaponMulticast.Broadcast();
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ParticleSystem,
		GetStaticMeshComponent()->GetSocketTransform("Fire", RTS_World),
		true,
		EPSCPoolMethod::AutoRelease,
		true
	);
	Destroy();
}

void AThrowingWeapon::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(0,0,0));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void AThrowingWeapon::InteractWeaponMulticast_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ParticleSystem,
		GetStaticMeshComponent()->GetSocketTransform("Fire", RTS_World),
		true,
		EPSCPoolMethod::AutoRelease,
		true
	);
}

void AThrowingWeapon::InteractWeaponServer_Implementation()
{
	OnInteractThrowingWeaponMulticast.Broadcast();

	InteractWeaponMulticast();
}

void AThrowingWeapon::InteractWeaponClient_Implementation()
{
}

#include "WeaponManagerComponent.h"
#include "Lesson15Character.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UWeaponManagerComponent::SetCurrentWeapon(ABaseWeapon* NewWeapon)
{
	if (!CurrentWeapon && !NewWeapon->GetOwner())
	{
		CurrentWeapon = NewWeapon;
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		auto* Character = Cast<ALesson15Character>(GetOwner());
		CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
									FName(TEXT("SocketWeapon")));
		return true;
	}
	return false;
}

bool UWeaponManagerComponent::DropCurrentWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(nullptr);
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		auto* Character = Cast<ALesson15Character>(GetOwner());
		FVector NewLocation = Character->GetMesh()->GetRightVector() * DistanceToDropWeapon + Character->
			GetMesh()->GetComponentLocation();
		NewLocation.Z += 200;
		FHitResult* OutSweepHitResult = nullptr;
		CurrentWeapon->SetActorLocation(NewLocation, false, OutSweepHitResult, ETeleportType::None);
		CurrentWeapon = nullptr;
		return true;
	}
	return false;
}


void UWeaponManagerComponent::InteractCurrentWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->InteractWeapon();
	}
}

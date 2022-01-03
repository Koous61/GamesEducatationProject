#include "FireWeapon.h"

#include "DrawDebugHelpers.h"
#include "Lesson15Character.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AFireWeapon::AFireWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bIsReadyFire = true;
	RateFire = 1.f;
}

void AFireWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AFireWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireWeapon::InteractWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractWeapon Client 1"));
	InteractWeaponServer();
}

void AFireWeapon::InteractWeaponClient_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractWeapon Client 2"));
	OnInteractFireWeaponMulticast.Broadcast();
	const FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Fire");
	const FVector LocationEnd = LocationSocket + GetStaticMeshComponent()->GetRightVector() * DistanceFire * -1;
	DrawDebugLine(
		GetWorld(),
		LocationSocket,
		LocationEnd,
		FColor(255, 0, 0),
		false,
		3,
		0,
		12.3
	);
}

void AFireWeapon::ReadyFire()
{
	bIsReadyFire = true;
}

void AFireWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireWeapon, bIsReadyFire);
}

void AFireWeapon::InteractWeaponMulticast_Implementation()
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

void AFireWeapon::InteractWeaponServer_Implementation()
{
	if (bIsReadyFire)
	{
		bIsReadyFire = false;
		InteractWeaponClient();
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &AFireWeapon::ReadyFire, RateFire);
		UE_LOG(LogTemp, Warning, TEXT("InteractWeapon Server"));
		FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Fire");
		FCollisionQueryParams RV_TraceParams;
		RV_TraceParams.bTraceComplex = true;
		FHitResult RV_Hit(ForceInit);
		FVector LocationEnd = LocationSocket + GetStaticMeshComponent()->GetRightVector() * DistanceFire * -1;
		InteractWeaponMulticast();
		GetWorld()->LineTraceSingleByChannel(
			RV_Hit,
			LocationSocket,
			LocationEnd,
			ECC_Pawn,
			RV_TraceParams
		);
		if (RV_Hit.bBlockingHit)
		{
			auto* Character = Cast<ALesson15Character>(RV_Hit.GetActor());
			if (Character)
			{
				Character->ApplyDamage(Damage);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
		}
	}
}

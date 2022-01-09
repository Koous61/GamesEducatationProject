#include "HealthBag.h"

void AHealthBag::InteractItem(ALesson15Character* Character)
{
	Super::InteractItem(Character);
	Character->AddHealthClient(Health);
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lesson15GameMode.h"
#include "Lesson15Character.h"
#include "UObject/ConstructorHelpers.h"

ALesson15GameMode::ALesson15GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

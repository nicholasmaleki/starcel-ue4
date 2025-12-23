// Copyright Epic Games, Inc. All Rights Reserved.

#include "Starcel9GameMode.h"
#include "Starcel9Character.h"
#include "UObject/ConstructorHelpers.h"

AStarcel9GameMode::AStarcel9GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

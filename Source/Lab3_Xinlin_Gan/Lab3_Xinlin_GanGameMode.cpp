// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab3_Xinlin_GanGameMode.h"
#include "Lab3_Xinlin_GanCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALab3_Xinlin_GanGameMode::ALab3_Xinlin_GanGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

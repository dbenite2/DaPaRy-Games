// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectSailorGameMode.h"
#include "ProjectSailorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectSailorGameMode::AProjectSailorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

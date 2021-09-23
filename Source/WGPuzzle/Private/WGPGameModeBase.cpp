// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "WGPGameModeBase.h"
#include "WGPHUD.h"
#include "WGPCharacter.h"
#include "WGPPlayerController.h"

AWGPGameModeBase::AWGPGameModeBase()
{
	HUDClass = AWGPHUD::StaticClass();
	DefaultPawnClass = AWGPCharacter::StaticClass();
	PlayerControllerClass = AWGPPlayerController::StaticClass();
}
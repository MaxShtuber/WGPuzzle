// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WGPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WGPUZZLE_API AWGPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWGPGameModeBase();

	void SetGameDifficulty(int32 NewGameDifficulty) { GameDifficulty = NewGameDifficulty; };
	void SetDifficultyIndex(int32 NewDifficultyIndex) { DifficultyIndex = NewDifficultyIndex; };

	int32 GetGameDifficulty() { return GameDifficulty; };
	int32 GetDifficultyIndex() { return DifficultyIndex; };
	int32 GetMaxDifficultyIndex() { return MaxDifficultyIndex; };
private:
	int32 GameDifficulty = 100;
	int32 DifficultyIndex = 1;
	int32 MaxDifficultyIndex = 3;
};

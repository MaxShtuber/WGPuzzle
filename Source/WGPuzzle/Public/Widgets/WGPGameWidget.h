// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WGPGameWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSwitchedSignature);

class UButton;
class UWrapBox;
class UTextBlock;
class UWGPOneBlockWidget;

/**
 * 
 */
UCLASS()
class WGPUZZLE_API UWGPGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnSwitchedSignature OnSwitched;

	UFUNCTION(BlueprintCallable)
	void SwitchTwoBlocks(UWGPOneBlockWidget* FirstBlock, UWGPOneBlockWidget* SecondBlock);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* WinExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* WinRestartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TutorialButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* DifficultyButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWrapBox* MainField;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWrapBox* UpperField;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WinText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TutorialText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DifficultyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OneBlockClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UpperRowClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName = "GameLevel";

	virtual void NativeOnInitialized() override;

private:
	bool IsGameStart = false;
	int32 FirstIndex = 0;
	int32 SecondIndex = 0;
	int32 ThirdIndex = 0;
	int32 GameDifficulty = 100;

	UFUNCTION()
	void OnExitLevel();

	UFUNCTION()
	void OnRestartGame();

	UFUNCTION()
	void OnChangeDifficulty();

	UFUNCTION()
	void TakeTwoSelectedBlocks();

	UFUNCTION()
	void OnWin();

	UFUNCTION()
	void SetTutorialVisibility();

	void InitializeButtonDelegates();
	void InitializeIndexes();
	void ClearChildrens();
	void GenerateGameField();
	void GenerateBlockIndexes();
	void OneShuffleGameField();
	void ShuffleGameField(int ShuffleTimes);
	
	void RemoveButtonDeletages();

	bool CanBeSwitched(UWGPOneBlockWidget* FirstBlock, UWGPOneBlockWidget* SecondBlock);
	bool IsWin();
	
};

// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "Widgets/WGPGameWidget.h"
#include "Widgets/UpperRowWidget.h"
#include "Widgets/WGPOneBlockWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "WGPGameModeBase.h"

void UWGPGameWidget::NativeOnInitialized()
{
	ClearChildrens();
	Super::NativeOnInitialized();
	
	InitializeIndexes();
	GenerateGameField();
	InitializeButtonDelegates();
	GenerateBlockIndexes();
	GameDifficulty = Cast<AWGPGameModeBase>(GetWorld()->GetAuthGameMode())->GetGameDifficulty();
	ShuffleGameField(GameDifficulty);
	IsGameStart = true;
	
}

void UWGPGameWidget::SetTutorialVisibility()
{
	if (TutorialText)
	{
		TutorialText->SetVisibility(TutorialText->IsVisible() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
}

void UWGPGameWidget::InitializeButtonDelegates()
{
	if (WinText)
	{
		WinText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (TutorialText)
	{
		TutorialText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (TutorialButton)
	{
		TutorialButton->OnClicked.AddDynamic(this, &UWGPGameWidget::SetTutorialVisibility);
	}

	if (DifficultyButton)
	{
		DifficultyButton->OnClicked.AddDynamic(this, &UWGPGameWidget::OnChangeDifficulty);
		if (DifficultyText)
		{
			if (GameDifficulty <= 10)
			{
				DifficultyText->SetText(FText::FromString("Easy"));
			}
			else if (GameDifficulty <= 100)
			{
				DifficultyText->SetText(FText::FromString("Medium"));
			}
			else
			{
				DifficultyText->SetText(FText::FromString("Hard"));
			}
		}
	}

	if (WinRestartButton)
	{
		WinRestartButton->OnClicked.AddDynamic(this, &UWGPGameWidget::OnRestartGame);
		WinRestartButton->SetVisibility(ESlateVisibility::Hidden);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UWGPGameWidget::OnRestartGame);
		RestartButton->SetVisibility(ESlateVisibility::Visible);
	}

	if (WinExitButton)
	{
		WinExitButton->OnClicked.AddDynamic(this, &UWGPGameWidget::OnExitLevel);
		WinExitButton->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UWGPGameWidget::OnExitLevel);
		ExitButton->SetVisibility(ESlateVisibility::Visible);
	}

	auto Childrens = MainField->GetAllChildren();
	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;
		Block->BlockButton->OnClicked.AddDynamic(this, &UWGPGameWidget::TakeTwoSelectedBlocks);
	}
	OnSwitched.AddUObject(this, &UWGPGameWidget::OnWin);
}

void UWGPGameWidget::RemoveButtonDeletages()
{
	if (TutorialButton)
	{
		TutorialButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::SetTutorialVisibility);
	}

	if (DifficultyButton)
	{
		DifficultyButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::OnChangeDifficulty);
	}

	if (WinRestartButton)
	{
		WinRestartButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::OnRestartGame);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::OnRestartGame);
	}

	if (WinExitButton)
	{
		WinExitButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::OnExitLevel);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::OnExitLevel);
	}

	auto Childrens = MainField->GetAllChildren();
	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;
		Block->BlockButton->OnClicked.RemoveDynamic(this, &UWGPGameWidget::TakeTwoSelectedBlocks);
	}
}

void UWGPGameWidget::OnChangeDifficulty()
{
	auto GameMode = Cast<AWGPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	auto DifficultyIndex = (GameMode->GetDifficultyIndex() + 1) % GameMode->GetMaxDifficultyIndex();
	GameMode->SetDifficultyIndex(DifficultyIndex);
	
	if (DifficultyIndex == 0)
	{
		GameMode->SetGameDifficulty(10);
		
	}
	else if (DifficultyIndex == 1)
	{
		GameMode->SetGameDifficulty(100);
	}
	else
	{
		GameMode->SetGameDifficulty(1000);
	}
	GameDifficulty = GameMode->GetGameDifficulty();
	UE_LOG(LogTemp, Display, TEXT("%d"), GameDifficulty);
	OnRestartGame();
}

void UWGPGameWidget::OnExitLevel()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UWGPGameWidget::InitializeIndexes()
{
	auto UpperWidget = CreateWidget<UUpperRowWidget>(GetWorld(), UpperRowClass);
	UpperField->AddChildToWrapBox(UpperWidget);
	UpperField->SetVisibility(ESlateVisibility::Visible);
	FirstIndex = UpperWidget->GetFirstIndex();
	SecondIndex = UpperWidget->GetSecondIndex();
	ThirdIndex = UpperWidget->GetThirdIndex();
}

void UWGPGameWidget::ClearChildrens()
{
	MainField->ClearChildren();
	UpperField->ClearChildren();
}

void UWGPGameWidget::GenerateGameField()
{
	auto MaxLeftFreeBlocks = 2;
	auto MaxLeftBlockedBlocks = 3;
	auto MaxRightFreeBlocks = 2;
	auto MaxRightBlockedBlocks = 3;

	for (auto i = 0; i < 25; i++)
	{
		auto OneBlock = CreateWidget<UWGPOneBlockWidget>(GetWorld(), OneBlockClass);
		if (!OneBlock) continue;
		if (i % 5 == 0)
		{
			auto SlateBrush = OneBlock->BlockMap.Find(FirstIndex);
			OneBlock->BlockImage->SetBrush(*SlateBrush);
		}
		else if (i % 5 == 2)
		{
			auto SlateBrush = OneBlock->BlockMap.Find(SecondIndex);
			OneBlock->BlockImage->SetBrush(*SlateBrush);
		}
		else if (i % 5 == 4)
		{
			auto SlateBrush = OneBlock->BlockMap.Find(ThirdIndex);
			OneBlock->BlockImage->SetBrush(*SlateBrush);
		}
		else if (i % 5 == 1)
		{
			auto Index = UKismetMathLibrary::RandomIntegerInRange(3, 4);
			if (Index == 3)
			{
				if (MaxLeftFreeBlocks > 0)
				{
					MaxLeftFreeBlocks--;
					auto SlateBrush = OneBlock->BlockMap.Find(Index);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}
				else
				{
					auto SlateBrush = OneBlock->BlockMap.Find(4);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}

			}
			else
			{
				if (MaxLeftBlockedBlocks > 0)
				{
					MaxLeftBlockedBlocks--;
					auto SlateBrush = OneBlock->BlockMap.Find(Index);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}
				else
				{
					auto SlateBrush = OneBlock->BlockMap.Find(3);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}
			}
		}
		else
		{
			auto Index = UKismetMathLibrary::RandomIntegerInRange(3, 4);
			if (Index == 3)
			{
				if (MaxRightFreeBlocks > 0)
				{
					MaxRightFreeBlocks--;
					auto SlateBrush = OneBlock->BlockMap.Find(Index);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}
				else
				{
					auto SlateBrush = OneBlock->BlockMap.Find(4);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}

			}
			else
			{
				if (MaxRightBlockedBlocks > 0)
				{
					MaxRightBlockedBlocks--;
					auto SlateBrush = OneBlock->BlockMap.Find(Index);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}
				else
				{
					auto SlateBrush = OneBlock->BlockMap.Find(3);
					OneBlock->BlockImage->SetBrush(*SlateBrush);
				}
			}
		}
		MainField->AddChildToWrapBox(OneBlock);
		MainField->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWGPGameWidget::SwitchTwoBlocks(UWGPOneBlockWidget* FirstBlock, UWGPOneBlockWidget* SecondBlock)
{
	if (FirstBlock->ReadyToSwitch() && SecondBlock->ReadyToSwitch())
	{
		FirstBlock->IsSelected = false;
		FirstBlock->SetFrameVisibility(FirstBlock->IsSelected);
		SecondBlock->IsSelected = false;
		SecondBlock->SetFrameVisibility(SecondBlock->IsSelected);

		if ((FirstBlock->IsFree() || SecondBlock->IsFree()) && (CanBeSwitched(FirstBlock, SecondBlock) || CanBeSwitched(SecondBlock, FirstBlock)))
		{
			auto FirstSlateBrush = FirstBlock->BlockImage->Brush;
			auto SecondSlateBrush = SecondBlock->BlockImage->Brush;

			FirstBlock->BlockImage->SetBrush(SecondSlateBrush);
			SecondBlock->BlockImage->SetBrush(FirstSlateBrush);
			OnSwitched.Broadcast();
		}

	}
}

void UWGPGameWidget::TakeTwoSelectedBlocks()
{
	auto Childrens = MainField->GetAllChildren();
	UWGPOneBlockWidget* FirstBlock = nullptr;
	UWGPOneBlockWidget* SecondBlock = nullptr;

	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;

		if (Block->ReadyToSwitch())
		{
			if (!FirstBlock)
			{
				FirstBlock = Block;
				continue;
			}
			else if (!SecondBlock)
			{
				SecondBlock = Block;
				SwitchTwoBlocks(FirstBlock, SecondBlock);
				SecondBlock = nullptr;
				FirstBlock = nullptr;
				break;
			}
		}
	}
}

void UWGPGameWidget::GenerateBlockIndexes()
{
	auto Childrens = MainField->GetAllChildren();
	auto RowCounter = 1;
	auto ColumnCounter = 0;
	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;

		ColumnCounter++;
		if (ColumnCounter == 6)
		{
			ColumnCounter = 1;
			RowCounter++;
		}
		Block->RowIndex = RowCounter;
		Block->ColumnIndex = ColumnCounter;
	}
}

void UWGPGameWidget::OnWin()
{
	if (IsWin())
	{
		MainField->SetVisibility(ESlateVisibility::Hidden);
		UpperField->SetVisibility(ESlateVisibility::Hidden);
		ExitButton->SetVisibility(ESlateVisibility::Hidden);
		RestartButton->SetVisibility(ESlateVisibility::Hidden);
		WinText->SetVisibility(ESlateVisibility::Visible);
		WinExitButton->SetVisibility(ESlateVisibility::Visible);
		WinRestartButton->SetVisibility(ESlateVisibility::Visible);
		
	}
}

void UWGPGameWidget::OneShuffleGameField()
{
	auto Childrens = MainField->GetAllChildren();
	TArray<UWGPOneBlockWidget*> WhiteBlocks;
	TArray<UWGPOneBlockWidget*> BlocksAroundWhiteBlock;
	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;

		if (Block->BlockImage->Brush == *Block->BlockMap.Find(3))
		{
			WhiteBlocks.Add(Block);
		}
	}
	auto RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, WhiteBlocks.Num()-1);
	auto WhiteBlock = WhiteBlocks[RandomIndex];
	WhiteBlock->IsSelected = true;
	WhiteBlock->SetFrameVisibility(WhiteBlock->IsSelected);

	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;

		if ((CanBeSwitched(WhiteBlock, Block) || CanBeSwitched(Block, WhiteBlock)) && Block->BlockImage->Brush != *Block->BlockMap.Find(4) && Block->BlockImage->Brush != *Block->BlockMap.Find(3))
		{
			BlocksAroundWhiteBlock.Add(Block);
		}
	}
	if (BlocksAroundWhiteBlock.Num() == 0)
	{
		WhiteBlock->IsSelected = false;
		WhiteBlock->SetFrameVisibility(WhiteBlock->IsSelected);
		return;
	}
	auto SecondRandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, BlocksAroundWhiteBlock.Num() - 1);
	auto SecondBlock = BlocksAroundWhiteBlock[SecondRandomIndex];
	SecondBlock->IsSelected = true;
	SecondBlock->SetFrameVisibility(SecondBlock->IsSelected);
	SwitchTwoBlocks(WhiteBlock, SecondBlock);
}

void UWGPGameWidget::ShuffleGameField(int ShuffleTimes)
{
	for (auto Iterator = 0; Iterator < ShuffleTimes; Iterator++)
	{
		OneShuffleGameField();
	}
}

void UWGPGameWidget::OnRestartGame()
{
	RemoveButtonDeletages();
	IsGameStart = false;
	ClearChildrens();

	InitializeIndexes();
	GenerateGameField();
	InitializeButtonDelegates();
	GenerateBlockIndexes();
	GameDifficulty = Cast<AWGPGameModeBase>(GetWorld()->GetAuthGameMode())->GetGameDifficulty();
	ShuffleGameField(GameDifficulty);
	IsGameStart = true;
}

bool UWGPGameWidget::CanBeSwitched(UWGPOneBlockWidget* FirstBlock, UWGPOneBlockWidget* SecondBlock)
{
	auto HorizontalCondition = FirstBlock->RowIndex == SecondBlock->RowIndex && SecondBlock->ColumnIndex - FirstBlock->ColumnIndex == 1;
	auto VerticalCondition = FirstBlock->ColumnIndex == SecondBlock->ColumnIndex && SecondBlock->RowIndex - FirstBlock->RowIndex == 1;
	return HorizontalCondition || VerticalCondition;
}

bool UWGPGameWidget::IsWin()
{
	auto Counter = 0;
	auto Childrens = MainField->GetAllChildren();
	for (auto Child : Childrens)
	{
		auto Block = Cast<UWGPOneBlockWidget>(Child);
		if (!Block) continue;
		if (Block->ColumnIndex == 1 && Block->BlockImage->Brush == *Block->BlockMap.Find(FirstIndex))
		{
			Counter++;
		}
		if (Block->ColumnIndex == 3 && Block->BlockImage->Brush == *Block->BlockMap.Find(SecondIndex))
		{
			Counter++;
		}
		if (Block->ColumnIndex == 5 && Block->BlockImage->Brush == *Block->BlockMap.Find(ThirdIndex))
		{
			Counter++;
		}
	}
	return Counter == 15 && IsGameStart;
}

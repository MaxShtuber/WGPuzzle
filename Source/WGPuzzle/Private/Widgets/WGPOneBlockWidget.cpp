// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "Widgets/WGPOneBlockWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/KismetArrayLibrary.h"

void UWGPOneBlockWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetFrameVisibility(IsSelected);
	if (BlockButton)
	{
		BlockButton->OnClicked.AddDynamic(this, &UWGPOneBlockWidget::OnClicked);
	}
}

void UWGPOneBlockWidget::OnClicked()
{
	auto SlateBrush = BlockMap.Find(4);
	if (BlockImage->Brush == *SlateBrush)
	{
		IsSelected = false;
		SetFrameVisibility(IsSelected);
		return;
	}
	IsSelected = IsSelected ? false : true;
	SetFrameVisibility(IsSelected);
}

void UWGPOneBlockWidget::SetFrameVisibility(bool Visible)
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
bool UWGPOneBlockWidget::ReadyToSwitch()
{
	return IsSelected;
}

bool UWGPOneBlockWidget::IsFree()
{
	auto SlateBrush = BlockMap.Find(3);
	return BlockImage->Brush == *SlateBrush;
}
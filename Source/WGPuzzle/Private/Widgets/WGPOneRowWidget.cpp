// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "Widgets/WGPOneRowWidget.h"
#include "Widgets/UpperRowWidget.h"
#include "Widgets/WGPOneBlockWidget.h"
#include "Components/HorizontalBox.h"

void UWGPOneRowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	OneRowBox->ClearChildren();
	for (auto i = 0; i < 5; i++)
	{
		auto OneBlock = CreateWidget<UWGPOneBlockWidget>(GetWorld(), OneBlockWidgetClass);
		if (!OneBlock) continue;
		OneRowBox->AddChildToHorizontalBox(OneBlock);
	}
}
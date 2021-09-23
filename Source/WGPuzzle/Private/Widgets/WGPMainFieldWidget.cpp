// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "Widgets/WGPMainFieldWidget.h"
#include "Components/VerticalBox.h"

void UWGPMainFieldWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FullField->ClearChildren();
	for (auto j = 0; j < 5; j++)
	{
		auto OneRow = CreateWidget<UUserWidget>(GetWorld(), OneRowWidgetClass);
		if (!OneRow) continue;
		FullField->AddChildToVerticalBox(OneRow);
	}

}
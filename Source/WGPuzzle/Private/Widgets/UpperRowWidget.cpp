// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "Widgets/UpperRowWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Styling/SlateBrush.h"


void UUpperRowWidget::NativeOnInitialized()
{
	GenerateIndex();
	Super::NativeOnInitialized();
	
}

void UUpperRowWidget::GenerateIndex()
{
	FirstIndex = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	SecondIndex = FirstIndex < 2 ? 2 : UKismetMathLibrary::RandomIntegerInRange(0, 1);
	ThirdIndex = 3 - FirstIndex - SecondIndex;
}
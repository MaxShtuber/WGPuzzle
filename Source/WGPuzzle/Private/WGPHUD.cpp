// This is the test puzzle game for Wargaming Academy. All rights reserved.

#include "WGPHUD.h"
#include "Blueprint/UserWidget.h"

void AWGPHUD::BeginPlay()
{
	Super::BeginPlay();

	auto MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	if (MainWidget)
	{
		MainWidget->AddToViewport();
	}

}
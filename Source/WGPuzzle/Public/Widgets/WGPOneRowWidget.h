// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WGPOneRowWidget.generated.h"

class UHorizontalBox;

/**
 * 
 */
UCLASS()
class WGPUZZLE_API UWGPOneRowWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OneBlockWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* OneRowBox;

	virtual void NativeOnInitialized() override;
};

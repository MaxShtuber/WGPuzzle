// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WGPMainFieldWidget.generated.h"

class UUserWidget;
class UHorizontalBox;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class WGPUZZLE_API UWGPMainFieldWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OneRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* FullField;

	virtual void NativeOnInitialized() override;
};

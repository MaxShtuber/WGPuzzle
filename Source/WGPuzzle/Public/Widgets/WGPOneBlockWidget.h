// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WGPOneBlockWidget.generated.h"

class UButton;
class UImage;

/**
 * 
 */
UCLASS()
class WGPUZZLE_API UWGPOneBlockWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	bool IsSelected = false;

	UPROPERTY(meta = (BindWidget))
	UImage* BlockImage;

	UPROPERTY(meta = (BindWidget))
	UButton* BlockButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap <int32, FSlateBrush> BlockMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RowIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ColumnIndex = 0;

	UFUNCTION(BlueprintCallable)
	bool ReadyToSwitch();

	UFUNCTION(BlueprintCallable)
	bool IsFree();

	void SetFrameVisibility(bool IsSelected);
protected:

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BlockCombinations;

	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	void OnClicked();


};

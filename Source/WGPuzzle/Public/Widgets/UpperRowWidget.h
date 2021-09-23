// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpperRowWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class WGPUZZLE_API UUpperRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	int GetFirstIndex() const { return FirstIndex; };

	UFUNCTION(BlueprintCallable)
	int GetSecondIndex() const { return SecondIndex; };

	UFUNCTION(BlueprintCallable)
	int GetThirdIndex() const { return ThirdIndex; };

	UFUNCTION(BlueprintCallable)
	void GenerateIndex();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap <int32, FSlateBrush> BlockMap;

	UPROPERTY(meta = (BindWidget))
	UImage* FirstImage;

	UPROPERTY(meta = (BindWidget))
	UImage* SecondImage;

	UPROPERTY(meta = (BindWidget))
	UImage* ThirdImage;

	virtual void NativeOnInitialized() override;
private:
	UPROPERTY()
	int FirstIndex = 0;
	UPROPERTY()
	int SecondIndex = 0;
	UPROPERTY()
	int ThirdIndex = 0;

};

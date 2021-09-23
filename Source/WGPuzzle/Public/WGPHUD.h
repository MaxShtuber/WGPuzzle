// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WGPHUD.generated.h"

/**
 * 
 */
UCLASS()
class WGPUZZLE_API AWGPHUD : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainWidgetClass;

	virtual void BeginPlay() override;
};

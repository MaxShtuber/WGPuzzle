// This is the test puzzle game for Wargaming Academy. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WGPCharacter.generated.h"

UCLASS()
class WGPUZZLE_API AWGPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWGPCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
};

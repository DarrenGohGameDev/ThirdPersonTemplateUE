// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UPlayerInputComponent;

/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public :

	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

protected :

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "InputComponent")
	UPlayerInputComponent * playerInputComponent;

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void EnterCrouch();

	void FinishCrouch();

	void Sprint(const FInputActionValue& value);

	void Interact();

	//virtual void Jump() override;

private :

	void InitPlayerCharacter();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class THIRDPERSONGAMEPLUGIN_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,  Category = "Attribute")
	UCharacterAttributeSet* characterAttribute;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float actionSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float  movementSpeedMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float runSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float walkSpeed = 300.f;

private:	
	

};

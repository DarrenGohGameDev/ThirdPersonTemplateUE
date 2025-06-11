// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Player/PlayerInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enums/InputActionEnums.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanJump = false;
	playerInputComponent = CreateDefaultSubobject<UPlayerInputComponent>(TEXT("PlayerInputComponent"));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitPlayerCharacter();

	
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	

	const FVector2D MovementVector = (value.Get<FVector2D>() * movementSpeedMultiplier) * actionSpeed;
	UE_LOG(LogTemp, Warning, TEXT("move speed multi %f"), movementSpeedMultiplier);
	//if (ActionState != EActionState::EAS_Unoccupied) return;
	if (GetController())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Forward, MovementVector.Y);

		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Right, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookAxisValue = value.Get<FVector2D>();

	

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void APlayerCharacter::EnterCrouch()
{
	Crouch();
	movementSpeedMultiplier = 0.5f;
}

void APlayerCharacter::FinishCrouch()
{
	UnCrouch();
	movementSpeedMultiplier = 1.0f;
}

void APlayerCharacter::Sprint(const FInputActionValue& value)
{
	bool isSprinting = value.Get<bool>();

	if (isSprinting)
	{
		movementSpeedMultiplier = 3.5f;
		UE_LOG(LogTemp, Warning, TEXT("sprint Pressed"));
	}
	else
	{
		movementSpeedMultiplier = 1.0f;
		UE_LOG(LogTemp, Warning, TEXT("sprint Released"));
	}
	
}

void APlayerCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact is being pressed"));
}

//void APlayerCharacter::Jump()
//{
//	Super::Jump();
//}

void APlayerCharacter::InitPlayerCharacter()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::WalkInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::CrouchInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::EnterCrouch);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::CrouchInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::FinishCrouch);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::SprintInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Sprint);

	//playerInputComponent->SetupInputBinding(playerController, InputActionEnum::JumpInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::LookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::InteractInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Player/PlayerInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Enums/InputActionEnums.h"
#include "CharacterTrajectoryComponent.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanJump = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	playerInputComponent = CreateDefaultSubobject<UPlayerInputComponent>(TEXT("PlayerInputComponent"));

	TrajectoryComponent = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("TrajectoryComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);
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

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Forward, MovementVector.Y);

	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Right, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookAxisValue = value.Get<FVector2D>();

	AddControllerYawInput(LookAxisValue.X);
	AddControllerPitchInput(LookAxisValue.Y);
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

void APlayerCharacter::EnterSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed * actionSpeed;
}

void APlayerCharacter::ExitSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed * actionSpeed;
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

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::SprintInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::EnterSprint);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::SprintInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::ExitSprint);

	//playerInputComponent->SetupInputBinding(playerController, InputActionEnum::JumpInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::LookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::InteractInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
}



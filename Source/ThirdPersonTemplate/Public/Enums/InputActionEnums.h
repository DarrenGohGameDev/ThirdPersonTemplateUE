#pragma once

UENUM(BlueprintType)
enum class InputActionEnum : uint8
{
	WalkInputAction UMETA(DisplayName = "WalkInputAction"),
	SprintInputAction UMETA(DisplayName = "SprintInputAction"),
	CrouchInputAction UMETA(DisplayName = "CrouchInputAction"),
	LookInputAction UMETA(DisplayName = "LookInputAction"),
	JumpInputAction UMETA(DisplayName = "JumpInputAction"),
	AttackInputAction UMETA(DisplayName = "AttackInputAction"),
	InteractInputAction UMETA(DisplayName = "InteractInputAction"),
};
#pragma once

UENUM(BlueprintType)
enum class InputActionEnum : uint8
{
	WalkInputAction UMETA(DisplayName = "WalkInputAction"),
	AttackInputAction UMETA(DisplayName = "AttackInputAction"),
	LookInputAction UMETA(DisplayName = "LookInputAction"),
	InteractInputAction UMETA(DisplayName = "InteractInputAction"),
};
#pragma once

#include "CoreMinimal.h"
#include "ChatboxData.generated.h"


USTRUCT(BlueprintType)
struct FChatboxData
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere,Category = "Chatbox Data")
	FString speakerName;

	UPROPERTY(EditAnywhere, Category = "Chatbox Data")
	FString message;
};

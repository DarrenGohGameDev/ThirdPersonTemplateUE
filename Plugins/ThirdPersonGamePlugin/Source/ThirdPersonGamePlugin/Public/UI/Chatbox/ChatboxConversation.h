// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatboxConversation.generated.h"


struct FChatboxData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONGAMEPLUGIN_API UChatboxConversation : public UActorComponent 
{
	GENERATED_BODY()

public:	
	UChatboxConversation();

	TArray<FChatboxData> GetConversationArray();

protected:

	UPROPERTY(EditAnywhere, Category = "Converesation")
	TArray<FChatboxData> conversationArray;
};

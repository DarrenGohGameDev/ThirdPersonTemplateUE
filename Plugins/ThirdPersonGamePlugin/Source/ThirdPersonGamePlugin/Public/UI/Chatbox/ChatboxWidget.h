// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatboxWidget.generated.h"

/**
 * 
 */

class UEditableTextBox;
class UVerticalBox;
struct FChatboxData;

UCLASS()
class THIRDPERSONGAMEPLUGIN_API UChatboxWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	UChatboxWidget(const FObjectInitializer& ObjectInitializer);

	void StartChatting(TArray<FChatboxData> chatboxData);

	void StopChatting();

	void NextChat();
	
private :

	UPROPERTY(EditAnywhere);
	UVerticalBox * chatbox;

	UPROPERTY(EditAnywhere);
	UEditableTextBox* chatboxMessageText;

	UPROPERTY(EditAnywhere);
	UEditableTextBox* chatboxTittleText;

	int currentConversationCounter = 0;

	TArray<FChatboxData> currentConversationArray;

	void SetChatboxText(FString tittle ,FString msg);

	void ToggleChatbox(bool toggle);
};

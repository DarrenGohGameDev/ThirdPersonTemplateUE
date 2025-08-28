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
class USoundBase;
struct FChatboxData;

UCLASS()
class THIRDPERSONGAMEPLUGIN_API UChatboxWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	UChatboxWidget(const FObjectInitializer& ObjectInitializer);

protected :

	UPROPERTY(EditAnywhere);
	UVerticalBox* chatbox;

	UPROPERTY(EditAnywhere);
	UEditableTextBox* chatboxMessageText;

	UPROPERTY(EditAnywhere);
	UEditableTextBox* chatboxTittleText;

	UPROPERTY(EditAnywhere)
	float typeWriterEffectSpeed = 0.05f;

	UPROPERTY(EditAnywhere)
	USoundBase * typeWritterEffectSfx;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
private :

	int currentConversationCounter = 0;

	TArray<FChatboxData> currentConversationArray;

	FTimerHandle typeWriterEffectTimer;

	int currentLetterIndex = 0;

	FString currentTypeWriterEffectText;

	TArray<FString> typeWriterEffectLetterArray;

	void StartChatting(TArray<FChatboxData> chatboxData);

	void StopChatting();

	void NextChat();

	void SetChatboxText(FString tittle ,FString msg);

	void ToggleChatbox(bool toggle);

	void StartTypeWriterEffectOnChatboxText(FString msg);

	void ShowNextLetter();

	void StopTypeWriterEffect();
};

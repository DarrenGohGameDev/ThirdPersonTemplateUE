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
class UButton;
struct FChatboxData;
class APlayerCharacter;

UCLASS()
class THIRDPERSONGAMEPLUGIN_API UChatboxWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	UChatboxWidget(const FObjectInitializer& ObjectInitializer);

protected :

	UPROPERTY(meta = (BindWidget));
	UEditableTextBox* chatboxMessageText;

	UPROPERTY(meta = (BindWidget));
	UEditableTextBox* chatboxTittleText;

	UPROPERTY(EditAnywhere)
	float typeWriterEffectSpeed = 0.05f;

	UPROPERTY(EditAnywhere)
	float typeWriterEffectSfxVolume = 1.0f;

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

	APlayerCharacter* chatboxOwner;

	void StartChatting(APlayerCharacter* player ,TArray<FChatboxData> chatboxData);

	void StopChatting(APlayerCharacter* player);

	void NextChat(APlayerCharacter* player);

	void SetChatboxText(FString tittle ,FString msg);

	void ToggleChatbox(bool toggle);

	void StartTypeWriterEffectOnChatboxText(FString msg);

	void ShowNextLetter();

	void StopTypeWriterEffect();

	void ResetChatbox();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/Interactable.h"
#include "BaseTalkableCharacter.generated.h"


class UChatboxConversation;
class UWorldObjectInteractableDetectionComponent;
/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API ABaseTalkableCharacter : public ABaseCharacter, public IInteractable
{
	GENERATED_BODY()
	
public :
	ABaseTalkableCharacter();

protected :
	UPROPERTY(EditAnywhere , Category = "Conversation")
	UChatboxConversation* chatBoxConversationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractDetection")
	UWorldObjectInteractableDetectionComponent* interactableDetectionComponent;

	virtual void Interact() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};

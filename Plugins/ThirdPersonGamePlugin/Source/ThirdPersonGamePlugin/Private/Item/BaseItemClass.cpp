// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItemClass.h"
#include "Item/ItemAttributeSet.h"
#include "AbilitySystemComponent.h"

// Sets default values
ABaseItemClass::ABaseItemClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemAttribute = CreateDefaultSubobject<UItemAttributeSet>(TEXT("ItemAttribute"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->AddAttributeSetSubobject(itemAttribute);

}

// Called when the game starts or when spawned
void ABaseItemClass::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItemClass::ToggleItemUi(bool toggle)
{

}

// Called every frame
void ABaseItemClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItemClass::Interact()
{

}

void ABaseItemClass::UseItem()
{

}

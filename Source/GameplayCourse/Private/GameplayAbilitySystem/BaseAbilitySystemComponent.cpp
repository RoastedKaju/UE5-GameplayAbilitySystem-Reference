// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/BaseAbilitySystemComponent.h"

#include "GameplayAbilitySystem/BaseCharacter.h"


// Sets default values for this component's properties
UBaseAbilitySystemComponent::UBaseAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwner()))
	{
		// Character->SendAbilitiesChangedGameplayEvent();
	}
}
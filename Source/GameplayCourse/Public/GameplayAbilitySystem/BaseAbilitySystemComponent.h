// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEPLAYCOURSE_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseAbilitySystemComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnRep_ActivateAbilities() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.h"
#include "Attributes/BasicAttributeSet.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GAMEPLAYCOURSE_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void RemoveAbilities(const TArray<FGameplayAbilitySpecHandle>& AbilitiesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void SendAbilitiesChangedGameplayEvent();

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	UBaseAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	UBasicAttributeSet* BasicAttributeSet;

	/**
	 * Documentation recommends Mixed for player characters and minimal for AI characters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
	EGameplayEffectReplicationMode AbilitySystemReplicationMode = EGameplayEffectReplicationMode::Mixed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
};

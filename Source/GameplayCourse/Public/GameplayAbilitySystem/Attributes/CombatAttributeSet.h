// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYCOURSE_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCombatAttributeSet();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes", ReplicatedUsing=OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes", ReplicatedUsing=OnRep_MaxStrength)
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, MaxStrength);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes", ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes", ReplicatedUsing=OnRep_MaxArmor)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, MaxArmor);

protected:
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, Strength, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxStrength(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, MaxStrength, OldValue);
	}

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, Armor, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UCombatAttributeSet, MaxArmor, OldValue);
	}

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};

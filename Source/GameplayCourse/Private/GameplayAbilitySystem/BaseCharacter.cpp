// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilitySystem/BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Add the ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(AbilitySystemReplicationMode);

	// Add the basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));

	// Set size for collision
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);

	// Don't rotate when the controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 580.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// For AI
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantAbilities(StartingAbilities);
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For players
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

TArray<FGameplayAbilitySpecHandle> ABaseCharacter::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return TArray<FGameplayAbilitySpecHandle>();
	}

	TArray<FGameplayAbilitySpecHandle> Handles;

	for (const TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		Handles.Add(AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, this)));
	}

	return Handles;
}

void ABaseCharacter::RemoveAbilities(const TArray<FGameplayAbilitySpecHandle>& AbilitiesToRemove)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return;
	}

	for (const auto AbilitySpecHandle : AbilitiesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
	}
}

void ABaseCharacter::SendAbilitiesChangedGameplayEvent()
{
	const FGameplayTag EventTag = FGameplayTag::RequestGameplayTag("Event.Abilities.Changed");
	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = this;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventTag, EventData);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

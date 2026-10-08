# Gameplay Ability System Training Ground
After spending 2 years away from GAS/Gameplay related projects, I created this repository as a reference to quickly find solutions to some common GAS related problems and general tips plus cook recipies for some types of abilities.

## Major Components of Gameplay Ability System
A gameplay ability system is usually made up of the following components working together:
- Gameplay Ability
- Gameplay Effect
- Gameplay Cue
- Gameplay Attributes

All these combined let us define data, action and visual feedback related a certain ability, not all abilities are action based they can be totally passive as well.

## Adding Gameplay Ability System Component
Before we create our character class, we need to enable `Gameplay Abilities` plugin and restart our editor, then open the solution file and add the following modules in our game module.

```cpp
PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTasks", "GameplayTags" });
```
This will now allow us to use gameplay ability system related classes in our project without causing linker errors.

### Character Class
Create a base character class that holds your ability system component.
```cpp
class GAMEPLAYCOURSE_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
```

You will need the following include files:
```cpp
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
```

Now that we have added a public interface called `IAbilitySystemInterface` to our base character class, we need to overridee a virtual function.
```cpp
virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
```

```cpp
UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
```

All it does is return our ability system component which you also need to add in your members in the header file.
```cpp
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
UAbilitySystemComponent* AbilitySystemComponent;
```

While we are at it also add the following two functions:
```cpp
virtual void PossessedBy(AController* NewController) override;
virtual void OnRep_PlayerState() override;
```
These are needed so we can initialize our ability component system by providing avatar info, which in our case will be our character reference.

Also add replication mode variable so you can change it for players and AI.
```cpp
/**
 * Documentation recommends Mixed for player characters and minimal for AI characters
*/
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
EGameplayEffectReplicationMode AbilitySystemReplicationMode = EGameplayEffectReplicationMode::Mixed;
```

### Constructor
This is how you create the default sub-object of your ability system component in your source file inside the constructor.
```cpp
// Add the ability system component
AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
AbilitySystemComponent->SetIsReplicated(true);
AbilitySystemComponent->SetReplicationMode(AbilitySystemReplicationMode);
```

### On Possess And Player State Replicated
All we need to do here is call the `init` function of our ASC.
```cpp
void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// For AI
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
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
```

## Abilities
 - [Dash Ability](Docs/Dash/Dash.md)
 - [Area Trigger Ability](Docs/Area/Area.md)
 - [Health/Stamina Widget](Docs/Widgets/Widgets.md)
# Ability Tags
When you create a new gameplay ability, in the details panel you have a few tag containers, in this article we well be looking what are these for and how to use them to block certain abilities, grant tags to owner (which is the player character) and more.

## Types
- **Asset Tag**: Identifies the ability itself, other systems can check this.
- **Cancel Abilities With Tag**: Cancels currently active abilities whose ability tags match the specified tags.
- **Block Abilities With Tag**: Prevents abilities with matching ability tags from activating while this ability is active.
- **Activation Owned Tags**: Grants these tags to the owning Ability System Component (ASC) while the ability is active.
- **Activation Required Tags**: The owner must have all specified tags for this ability to activate.
- **Activation Blocked Tags**: The owner must not have any of these tags for this ability to activate.
- **Source Required Tags**: The source of the ability activation must have all specified tags.
- **Source Blocked Tags**: Blocks activation if the source has any of the specified tags.
- **Target Required Tags**: The target must have all specified tags for the ability's target-related activation checks.
- **Target Blocked Tags**: Blocks the ability's target-related activation checks if the target has any specified tags.

## Example
Imagine a Fireball ability:
- Asset Tags: `Ability.Ranged`
- Activation Required Tags: `State.CanCast`
- Activation Blocked Tags: `State.Stunned`
- Activation Owned Tags: `State.Casting`
- Block Abilities with Tag: `Ability.Movement`
- Cancel Abilities with Tag: `Ability.Channeling`

This means the Fireball needs State.CanCast, cannot activate while stunned, grants State.Casting while running, blocks movement abilities during its execution, and cancels channeling abilities when it activates.

>Tags are identifiers, not automatic gameplay logic. GAS uses them according to each container's rules, and some source/target checks depend on how your ability is implemented.
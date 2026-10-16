# Tips
Some tips and pit-falls you need to be aware about when working with Gameplay ability system.

## Always Prefer Tasks When Inside Ability
Use tasks with `clock` symbol on top right in abilities, these include for things like playing montage, root movement and even spawning actors.

## Authority Check
Abilities are only granted on server and are replicated to clients, similarly when using abilities make sure that you do things like spawning when inside ability only on server.

## Always Modify Attributes Through Effects
Although you can modify attributes directly but for a multiplayer project it is always recommended to modify the attributes through gameplay effects.

<p align="center">
<img src="AlwaysModifyAttributesThruEffects.jpg" alt="Header"/>
</p>

Here is an example of applying gameplay effect in a trigger actor to anyone who overlaps, you need a data tag as well in order to send custom magnitude.

This also means that in your attribute set class make sure to override functions for callbacks such as: `PreAttributeChange`, `PostAttributeChange`, `PreGameplayEffect` and `PostGameplayEffect`.

In these functions you can do a simple `if` check to see which attribute was modified and changed then you can perform clamping or even broadcast events.

## Death Is An Ability
What happens when your attribute for health goes below `0`? We activate the death ability, death is a passive ability granted at start which applies an infinite gameplay effect to the owner.

Here is how `Death Ability` looks like:

<p align="center">
<img src="DeathAbilityAppliesPermaDeathEffect.jpg" alt="Header"/>
</p>

And thsi is how we activate it:

<p align="center">
<img src="DeathIsAbility.jpg" alt="Header"/>
</p>

You need to listen for attribute change you can do this on begin play in your character class and when the value is below `0` try to activate the death ability.

<p align="center">
<img src="DeathEffect.jpg" alt="Header"/>
</p>

A Death effect is an infinite effect that adds `Status.Dead` tag.

## Targeting
GAS provides useful nodes for targeting data, it is called `Wait Target Data` and this can be instant or user confirmed, user confirmed requires you to call the `Target Confirm` Node.

<p align="center">
<img src="UserConfirmAbilityForAOE.jpg" alt="Header"/>
</p>

>Targeting Nodes crash on AI pawns for AI pawns use `Set Focus` on AI controller to rotate them to target and manually shoot projectile.

Since AI can also not confirm input you need to manually setup your other combo abilities in such a fashion that they support both players and NPCs.


## Cooldowns
You can assign a cooldown class inside your ability blueprint.
<p align="center">
<img src="Cooldown.jpg" alt="Header"/>
</p>

## Gameplay Cues
Here is how you can call a gameplay cue when inside an ability blueprint.
<p align="center">
<img src="CueInsideAbility.jpg" alt="Header"/>
</p>

Similarly if your cue needs some information like the location where particles will be spawned you should use the parameters option.
<p align="center">
<img src="CueWithParamsInsideAbility.jpg" alt="Header"/>
</p>

## Combos
Some abilities in your game would be massive like combos that play different animations and require input to progress.
<p align="center">
<img src="ComboWaitForEvents.jpg" alt="Header"/>
</p>

You should create an anim notify and send tags through it and wait for those gameplay events inside your ability.

Same goes for input:
<p align="center">
<img src="ComboWaitForInput.jpg" alt="Header"/>
</p>

And inside your character class on input you can send another gameplay event that tells your ability that input has been pressed.
<p align="center">
<img src="ComboInCharacterInputEvent.jpg" alt="Header"/>
</p>
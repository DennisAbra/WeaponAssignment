HOW TO USE:

Located the folder called "MyBlueprints". In there you'll find a folder called "Weapon_BP".
That is the base blueprint which you should use to create new weapons.

You simply pull the blueprint out to the world and you'll have some setting to adjust. Depending on what weapon you would like to make you have a few different settings to change. You'll find most of them under "Shooting".

When you have set up the base you need to add some components for the weapon to shoot.
There are 2 main components.
First one being "Hitscan". This allows you to shoot a linetrace bullet from your weapon and outwards.
The second one is Projectile. This allows you to shoot a projectile of choice (must be a blueprint) with an x amount of force added to it. 

We have created a blueprint base for projectiles one might want to create. The base is called "Projectile_BP".
For examples on what you can create with the base, please check the "Projectiles" folder.

Additionally you have 2 components that changes something with the weapon. 
There is the recoil component that adds recoil when you shoot. You can ofcourse tweak some values on the component to get a stronger/weaker/longer recoil effect.
The second one is a scope. We have connected it to an "Aim" input. When you press the preassigned button you'll zoom in if your weapon have a scope. When you release the button it will zoom out.

Everything except the Scope should be drag and drop to play and you can play around with different things to create weapons. 
For example: To make a shotgun you can choose the FireType on the base weapon to be BurstFire. Set a short time on TimeBetweenBurst and then add a spread on the hitscan component. 

To make a grenade launcher, choose your own settings on the weapon base. Make a copy of Projectile_BP, set bIsExplosiveBullet to true and don't forget to add an explosion effect in the preexisting particle system. BOOM you have a grenade launcher. 


Refrence:

Starting of we didn't really agree on a refrence, but as we came longer into the project we realized that we're building a system very similar to the older Call of Duty's. 
They mostly have Hitscan weapons, but also have projectile weapons like grenade launcher or rocket launchers. We think we achieved our goal in creating a system that would allow us to create weapons similar to the ones in Call of Duty. 

Alkimini scripts: ScopeComponent.h, ScopeComponent.cpp, DamageableInterface.h, DamageableInterface.cpp, (I have also done my own weapon system from which i borrowed the scope componenet from).

Dennis scripts: I've mostly worked on HitscanComponent, MyProjectCharacter, Projectile, ProjectileComponent, DamageableInterface, RecoilComponent and Weapon.

Antonios script: I have worked on BulletHoleDecal, DamageDisplay, Target, TargetManager, DamageableInterface, MyprojectCharacter (Armorysystem).

Controls:

Pick up weapon - Walk to it
Scroll weapon - Scrool Mousewheel
Use Scope - Right Mouse Button
Throw weapon - Q

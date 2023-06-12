#include "Weapon.h"

void Weapon::WeaponAnimationDeclaration()
{
	// Prehistoric

		// Rustic Stone Axe

			for (int i = 0; i < 4; i++) {

				rusticStoneAxe_idle.PushBack({ rusticStoneAxe_idle_width * i, 0, rusticStoneAxe_idle_width, rusticStoneAxe_idle_height });

			}
			rusticStoneAxe_idle.loop = true;
			rusticStoneAxe_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 6; i++) {

				rusticStoneAxe_attack.PushBack({ rusticStoneAxe_attack_width * i, 0, rusticStoneAxe_attack_width, rusticStoneAxe_attack_height });

			}
			rusticStoneAxe_attack.loop = false;
			rusticStoneAxe_attack.speed = rusticStoneAxe_attack_speed;

		// Tribal Lance

			for (int i = 0; i < 4; i++) {

				tribalLance_idle.PushBack({ tribalLance_idle_width * i, 0, tribalLance_idle_width, tribalLance_idle_height });

			}
			tribalLance_idle.loop = true;
			tribalLance_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 26; i++) {

				tribalLance_attack.PushBack({ tribalLance_attack_width * i, 0, tribalLance_attack_width, tribalLance_attack_height });

			}
			tribalLance_attack.loop = false;
			tribalLance_attack.speed = tribalLance_attack_speed;

		// Chief's Bow

			for (int i = 0; i < 4; i++) {

				chiefsBow_idle.PushBack({ chiefsBow_idle_width * i, 0, chiefsBow_idle_width, chiefsBow_idle_height });

			}
			chiefsBow_idle.loop = true;
			chiefsBow_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 25; i++) {

				chiefsBow_attack.PushBack({ chiefsBow_attack_width * i, 0, chiefsBow_attack_width, chiefsBow_attack_height });

			}
			chiefsBow_attack.loop = false;
			chiefsBow_attack.speed = chiefsBow_attack_speed;

	// Medieval
	
		// Fallen Blade

			for (int i = 0; i < 4; i++) {

				fallenBlade_idle.PushBack({ fallenBlade_idle_width * i, 0, fallenBlade_idle_width, fallenBlade_idle_height });

			}
			fallenBlade_idle.loop = true;
			fallenBlade_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 10; i++) {

				fallenBlade_attack.PushBack({ fallenBlade_attack_width * i, 0, fallenBlade_attack_width, fallenBlade_attack_height });

			}
			fallenBlade_attack.loop = false;
			fallenBlade_attack.speed = fallenBlade_attack_speed;

		// Ascendant Twins

			for (int i = 0; i < 4; i++) {

				ascendantTwins_idle.PushBack({ ascendantTwins_idle_width * i, 0, ascendantTwins_idle_width, ascendantTwins_idle_height });

			}
			ascendantTwins_idle.loop = true;
			ascendantTwins_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 14; i++) {

				ascendantTwins_attack.PushBack({ ascendantTwins_attack_width * i, 0, ascendantTwins_attack_width, ascendantTwins_attack_height });

			}
			ascendantTwins_attack.loop = false;
			ascendantTwins_attack.speed = ascendantTwins_attack_speed;

		// Mr. Flail

			for (int i = 0; i < 4; i++) {

				mrFlail_idle.PushBack({ mrFlail_idle_width * i, 0, mrFlail_idle_width, mrFlail_idle_height });

			}
			mrFlail_idle.loop = true;
			mrFlail_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 6; i++) {

				mrFlail_attack.PushBack({ mrFlail_attack_width * i, 0, mrFlail_attack_width, mrFlail_attack_height });

			}
			mrFlail_attack.loop = false;
			mrFlail_attack.speed = mrFlail_attack_speed;

	// Cyberpunk
	
		// Chainsword

			for (int i = 0; i < 4; i++) {

				chainsword_idle.PushBack({ chainsword_idle_width * i, 0, chainsword_idle_width, chainsword_idle_height });

			}
			chainsword_idle.loop = true;
			chainsword_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 14; i++) {

				chainsword_attack.PushBack({ chainsword_attack_width * i, 0, chainsword_attack_width, chainsword_attack_height });

			}
			chainsword_attack.loop = false;
			chainsword_attack.speed = chainsword_attack_speed;

		// Uraniumshell

			for (int i = 0; i < 4; i++) {

				uraniumshell_idle.PushBack({ uraniumshell_idle_width * i, 0, uraniumshell_idle_width, uraniumshell_idle_height });

			}
			uraniumshell_idle.loop = true;
			uraniumshell_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 15; i++) {

				uraniumshell_attack.PushBack({ uraniumshell_attack_width * i, 0, uraniumshell_attack_width, uraniumshell_attack_height });

			}
			uraniumshell_attack.loop = false;
			uraniumshell_attack.speed = uraniumshell_attack_speed;

		// Ionized Rifle

			for (int i = 0; i < 4; i++) {

				ionizedRifle_idle.PushBack({ ionizedRifle_idle_width * i, 0, ionizedRifle_idle_width, ionizedRifle_idle_height });

			}
			ionizedRifle_idle.loop = true;
			ionizedRifle_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 14; i++) {

				ionizedRifle_attack.PushBack({ ionizedRifle_attack_width * i, 0, ionizedRifle_attack_width, ionizedRifle_attack_height });

			}
			ionizedRifle_attack.loop = false;
			ionizedRifle_attack.speed = ionizedRifle_attack_speed;

	// Apocalypse

		// Grafted Claws

			for (int i = 0; i < 4; i++) {

				graftedClaws_idle.PushBack({ graftedClaws_idle_width * i, 0, graftedClaws_idle_width, graftedClaws_idle_height });

			}
			graftedClaws_idle.loop = true;
			graftedClaws_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 6; i++) {

				graftedClaws_attack.PushBack({ graftedClaws_attack_width * i, 0, graftedClaws_attack_width, graftedClaws_attack_height });

			}
			graftedClaws_attack.loop = false;
			graftedClaws_attack.speed = graftedClaws_attack_speed;

		// Agony

			for (int i = 0; i < 4; i++) {

				agony_idle.PushBack({ agony_idle_width * i, 0, agony_idle_width, agony_idle_height });

			}
			agony_idle.loop = true;
			agony_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 17; i++) {

				agony_attack.PushBack({ agony_attack_width * i, 0, agony_attack_width, agony_attack_height });

			}
			agony_attack.loop = false;
			agony_attack.speed = agony_attack_speed;

		// Eyebull

			for (int i = 0; i < 4; i++) {

				eyebull_idle.PushBack({ eyebull_idle_width * i, 0, eyebull_idle_width, eyebull_idle_height });

			}
			eyebull_idle.loop = true;
			eyebull_idle.speed = weaponIdleSpeed;

			for (int i = 0; i < 6; i++) {

				eyebull_attack.PushBack({ eyebull_attack_width * i, 0, eyebull_attack_width, eyebull_attack_height });

			}
			eyebull_attack.loop = false;
			eyebull_attack.speed = eyebull_attack_speed;

}

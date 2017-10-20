#ifndef ENUMS_HPP
#define ENUMS_HPP

/*!
	\file Enums.hpp
	\brief definition of enums needed in game
	\author Friday
*/

typedef unsigned char uc;

/*!
    \namespace Game_n
	\brief contains all game's things
*/
namespace Game_n {

	/*!
        \namespace Enums
		\brief contains all enums of Game
	*/
	namespace Enums {

		/*!
		\enum State

		\brief different states of Game
		*/
		enum class State {
			Idle,/*!< waiting players*/
			Start,/*!< in progress*/
			End,/*!< end of match*/
		};

		/*!
			\enum Buildings
			\brief contains all buildings in game
		*/
		enum class Buildings {
			CC,
			CCS,
			Supplying,
			Drill,
			Factory,
			Barrack,
			Armory,
			Bunker,
			Laboratory,
			Barricade,
			Wall,
			Door,
			GroundDefense,
			AirDefense,
			Foundry,
			CyberFactory,
			UltimateWeapon,
			Airport,
		};

		/*!
			\enum Units
			\brief contains all units in game
		*/
		enum class Units {
			LightSoldier,
			HeavySoldier,
			CleaningSoldier,
			LightVehicle,
			HeavyVehicle,
			LightPlane,
			HeavyPlane,
			VCS,
			Medics,
		};

		/*!
			\enum Colors
			\brief contains all colors in game
		*/
		enum class Colors {
			Red,
			Blue,
			Green,
			Yellow,
			Purple,
		};

		/*!
			\enum Races
			\brief contains all races in game
		*/
		enum class Races {
			Humans,
			Aliens,
		};

		/*!
			\enum Opti
			\brief contains all optimisations in game
		*/
		enum class Opti {
			Opti1,/*!< details 1*/
			Opti2,/*!< details 2*/
			Opti3,/*!< details 3*/
		};
	}
}

#endif

#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T16:36:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Conquerors
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    FenPrincipale.cpp \
	Game/Game.cpp \
	Game/Player.cpp \
	ServerSide/Handler.cpp \
    CommunicationProtocols/Errors.cpp \
    CommunicationProtocols/Sockets.cpp \
    CommunicationProtocols/Messages.cpp \
    CommunicationProtocols/TCP/Client.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Airport.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/AirTurret.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Armory.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Barrack.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Barricade.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Building.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Bunker.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/CyberFactory.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/DefenseBuilding.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/DrillingMachine.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Factory.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Gate.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/GroundTurret.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Headquarter.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Laboratory.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/ProductionBuilding.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/ProtectionBuilding.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Refueling.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/ResearchBuilding.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/SecondaryHeadquarter.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/TrainingBuilding.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/TrainingNResearchBuilding.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/UltimateWeapon.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Wall.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Researches/ChargedWeapon.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Researches/CyberSuspension.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Researches/HealthImprovement.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Researches/Research.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Researches/StimPistol.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Researches/TungstenAmmunition.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/BattleUnit.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/CleaningInfantry.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/Harvester.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/HeavyAviation.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/HeavyInfantry.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/HeavyVehicle.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/LightAviation.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/LightInfantry.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/LightVehicle.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/Medic.cpp \
    UnitsAndBuildings/UnitsAndBuildings/Units/Unit.cpp \
    

HEADERS += \
    FenPrincipale.h \
    Game/Enums.hpp \
    Game/Game.hpp \
	Game/Player.hpp \
	ServerSide/Handler.h \
    CommunicationProtocols/commsock.h \
	CommunicationProtocols/TCP/Client.hpp \
    CommunicationProtocols/Errors.hpp \
    CommunicationProtocols/Messages.hpp \
    CommunicationProtocols/Sockets.hpp \
    CommunicationProtocols/Utils.hpp \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Airport.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/AirTurret.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Armory.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Barrack.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Barricade.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Building.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Bunker.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/CyberFactory.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/DefenseBuilding.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/DrillingMachine.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Factory.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Gate.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/GroundTurret.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Headquarter.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Laboratory.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/ProductionBuilding.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/ProtectionBuilding.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Refueling.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/ResearchBuilding.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/SecondaryHeadquarter.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/TrainingBuilding.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/TrainingNResearchBuilding.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/UltimateWeapon.h \
    UnitsAndBuildings/UnitsAndBuildings/Buildings/Wall.h \
    UnitsAndBuildings/UnitsAndBuildings/Researches/ChargedWeapon.h \
    UnitsAndBuildings/UnitsAndBuildings/Researches/CyberSuspension.h \
    UnitsAndBuildings/UnitsAndBuildings/Researches/HealthImprovement.h \
    UnitsAndBuildings/UnitsAndBuildings/Researches/Research.h \
    UnitsAndBuildings/UnitsAndBuildings/Researches/StimPistol.h \
    UnitsAndBuildings/UnitsAndBuildings/Researches/TungstenAmmunition.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/BattleUnit.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/CleaningInfantry.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/Harvester.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/HeavyAviation.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/HeavyInfantry.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/HeavyVehicle.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/LightAviation.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/LightInfantry.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/LightVehicle.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/Medic.h \
    UnitsAndBuildings/UnitsAndBuildings/Units/Unit.h \
   

FORMS += \

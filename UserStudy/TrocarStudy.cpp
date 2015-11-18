//
//  TrocarStudy.cpp
//  Isis
//
//  Created by Adam Kohl on 1/16/13.
//
//

#include "TrocarStudy.h"
#include "VolumeController.h"

void isisUserStudy::TrocarStudy::placeTrocarAtPosition (isisColor whichTrocar, double x, double y, double z)
{
    if (whichTrocar == RED)
    {
        _redTrocarPos[0] = x;
        _redTrocarPos[1] = y;
        _redTrocarPos[2] = z;
        
        isisCore::VolumeController::instance()->setTrocarPosition(RED,
                                                                  _redTrocarPos[0],
                                                                  _redTrocarPos[1],
                                                                  _redTrocarPos[2]);
    }
    else if (whichTrocar == GREEN)
    {
        _greenTrocarPos[0] = x;
        _greenTrocarPos[1] = y;
        _greenTrocarPos[2] = z;
        
        isisCore::VolumeController::instance()->setTrocarPosition(GREEN,
                                                                  _greenTrocarPos[0],
                                                                  _greenTrocarPos[1],
                                                                  _greenTrocarPos[2]);
    }
    else if (whichTrocar == BLUE)
    {
        _blueTrocarPos[0] = x;
        _blueTrocarPos[1] = y;
        _blueTrocarPos[2] = z;
        
        isisCore::VolumeController::instance()->setTrocarPosition(BLUE,
                                                                  _blueTrocarPos[0],
                                                                  _blueTrocarPos[1],
                                                                  _blueTrocarPos[2]);
    }
}




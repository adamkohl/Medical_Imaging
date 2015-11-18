//
//  TrocarStudy.h
//  Isis
//
//  Created by Adam Kohl on 1/16/13.
//
//

#ifndef __Isis__TrocarStudy__
#define __Isis__TrocarStudy__
#endif /* defined(__Isis__TrocarStudy__) */

namespace isisUserStudy {

class TrocarStudy {
        
public:
  
    void placeTrocarAtPosition(isisColor whichTrocar, double x, double y, double z);

private:
    
    double     _redTrocarPos[3];
    double     _greenTrocarPos [3];
    double     _blueTrocarPos [3];
    
    vtkRenderer*		_renderer;
	vtkCamera*          _camera;
	vtkRenderWindow*	_renderWindow;
    
};

}
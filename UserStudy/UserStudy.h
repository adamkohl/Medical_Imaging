//
//  UserStudy.h
//  Isis
//
//  Created by Adam Kohl on 1/23/13.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#ifndef _USER_STUDY_H_
#define _USER_STUDY_H_
#include "MainWindow.h"

namespace isisUserStudy {

class UserStudy : public aq::KVObserver
{
    
public:
    
    // KVO 
	void didChangeValueForKey (boost::any value, aq::String key);
    
    void start(void);
    void stop(void);
    bool reset(void);
    
    void nextDataset(void);
    void prevDataset(void);
    
    void captureSubjectSelection(int key);
    
    void setUIParameters(void);
    
    void writeTextToSceen(std::string text);
    void renderTextInBlack(bool isRenderBlack);
    
    void incrementTimeElapsed(void);
    void resetTimeElapsed(void);
    
    void getStudyParameters(void);
    void setInitialPosition(void);
    void setTask(void);
    
    void updateRenderWindow(void);
    
    void resultToFile(std::string value);
    
    QDomDocument getDomDocFromFile(aq::String filepath);
    
//    QDomDocument getDomDocFromFile(aq::String filepath);
    
    
protected:
    
    UserStudy();
    ~UserStudy();
    
private:
    
    int          _userSliderMax, _userSliderMin;
    int          _timeElapsed;
    bool         _studyModeEnabled;
    bool         _leftPanelFrame;
    bool         _rightPanelFrame;
    bool         _tissueSliderGridFrame;
    
    isisCore::MainWindowController* _mainWindowController;
    time_t timer;
    
    vtkSmartPointer<vtkTextActor>   _textActor;
    std::vector<std::string> _tasks;
    
    double     _cameraPosition[3];
    double     _zoomSagittal[3];
    double     _zoomCoronal[3];
    double     _viewPosition[3];
    
    vtkRenderer*		_renderer;
	vtkCamera*          _camera;
	vtkRenderWindow*	_renderWindow;
    
    std::string         _results;

    bool        _cylinderStudy;
    bool        _kinectStudy;


};

}


#endif

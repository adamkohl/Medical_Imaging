//
//  StereoMono.h
//  Isis
//
//  Created by Eric Foo on 1/23/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#ifndef _STEREO_MONO_H_
#define _STEREO_MONO_H_
#include "DoubleSlider.h"
#include "TrocarWidget.h"

namespace isisUserStudy {

    /**
     * This class stores information for each task 
     */
class StudyTask
{
public:
    int                         taskNum;
    std::string                 subjectName;
    std::string                 testDate;
    
    std::string                 datasetName;
    std::string                 filepath;
    std::vector<std::string>    listOfFiles; // if we only use one set, then we don't need this
    
    int redTrocarPos[3];
    int greenTrocarPos [3];
    int blueTrocarPos [3];
    
    isisColor trocarSelected;
    int         timeTaken;
    
    int         windowMin;
    int         windowMax;
    
    double      cameraPos[3];
};
    
class StereoMono : public aq::KVObserver
{

    
public:
    static StereoMono* instance() {static StereoMono sm; return &sm;}
    
    void start (void);
    
    void stop (void);
    
    bool reset (void);
    
    void importSetting (std::string filename);
    void exportResults (std::string filename);
    
    void nextDataset (void);
    void prevDataset (void);
        
    void placeTrocarAtPosition (isisColor whichTrocar, double x, double y, double z);
    
    void orientVolume (double rotX, double rotY, double rotZ);

    void captureSubjectSelection (int key);
        
    inline void setSubjectName (std::string name) { _subjectName = name; }
    
    inline int getSecondsRemaining (void) { return _secondsRemaining; }
    inline int getCurrentSetNumber (void) { return _currentSetNumber; }
    
    inline bool isStudyModeEnabled (void) { return _studyModeEnabled; }
    
    
    void resultToFile(std::string);
    
    // Draw text on screen
    void writeTextToSceen (std::string text);
    void renderTextInBlack (bool isRenderBlack);
    
    // KVO 
    void didChangeValueForKey (boost::any value, aq::String key);
    
    void incrementTimeElapsed (void);
    void resetTimeElapsed (void);
    inline int getTimeElapsed (void) {return _timeElapsed;}
    
    void setTasks();
    void setNextTask();
    
    //Kinect Study
    void getUserSliderMin(void);
    void getUserSliderMax(void);
    
protected:
    StereoMono();
    ~StereoMono();
    
private:
    //std::vector<StudyTask>    _listOfTasks;
    
    int _secondsRemaining;
    int _currentSetNumber;
    
    std::string _subjectName;
    int _datasetNumber;
    int _settingsNumber;
    
    double _redTrocarPos[3];
    double _greenTrocarPos [3];
    double _blueTrocarPos [3];
    
    QFile _inputFile;
    QFile _outputFile;
    
    vtkSmartPointer<vtkTextActor>   _textActor;
    
    bool    _studyModeEnabled;
    
    std::vector <std::string> _tasks;
    
    int     _timeElapsed;
    
    int _userSliderMax, _userSliderMin;
};
    

	
}



#endif

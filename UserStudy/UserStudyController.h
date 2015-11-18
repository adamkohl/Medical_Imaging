//
//  UserStudyController.h
//  Isis
//
//  Created by Eric Foo on 1/23/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#ifndef _USER_STUDY_CONTROLLER_H_
#define _USER_STUDY_CONTROLLER_H_

#include "StudyConfirmationWidget.h"
#include "StudySelectionWidget.h"

namespace isisUserStudy {
    
enum StudyType
{
    STEREO_MONO,
    TWO_D_THREE_D,
    FUZZY_SEG,
    PROB_SEG,
    COLOR_SEG
};

class UserStudyController :  public QObject, public aq::KVObserver
{
    Q_OBJECT
    
public:
    static UserStudyController* instance() {static UserStudyController usc; return &usc;}
    
    void setUpMenuBarItems(void);
    void setUpUserInterface(void);
    void toggleStudySelectionWidget (bool toggle);
    
    void initializeStudyParam (void);
    void selectStudy (void);
    void createStudy (QString st);

    // KVO 
	void didChangeValueForKey (boost::any value, aq::String key);
    
public slots:
    void onUserStudySelect (void);
    void onUserStudySetup (void);
    void onUserStudyEnable (void);
    void onUserStudyDisable (void);
    void onUserStudyStart (void);
    void onUserStudyStop (void);
    void onUserStudyPause (void);
    
protected:
    UserStudyController();
    ~UserStudyController();
    
private:
    StudyConfirmationWidget*    _studyConfirmationWidget;
    StudySelectionWidget*       _studySelectionWidget;
    
    QMenu*      _userStudyMenu;
    StudyType   _studyToRun;
    bool        _isUserStudyEnabled;
    bool        _isUserStudyPaused;
    bool        _isUserStudyStarted;
    
    QAction* _userStudyEnable;
    QAction* _userStudyDisable;
    QAction* _userStudySelect;
    QAction* _userStudySetup;
    QAction* _userStudyStart;
    QAction* _userStudyStop;
    QAction* _userStudyPause;
    
    // original menu items
    QAction *userStudyHideUI;
    QAction *userStudyStereo;
    QAction *userStudyShowTimer;
    QAction *userStudyPrevious;
    QAction *userStudyNext;
    QAction *userStudyTrocars;
    QAction *userStudyShowTrocarControls;
    QAction *userStudyCamera;
    
    // Study Parameters
    StudyType       _studyType;
    std::string     _studyDateTime;
    std::string     _studyLocation;
    std::string     _participantID;
    std::string     _studySet;
};
    

	
}



#endif

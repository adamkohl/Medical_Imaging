//
//  UserStudyController.cpp
//  Isis
//
//  Created by Eric Foo on 1/23/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#include "UserStudyController.h"
#include "MainWindow.h"
#include "DicomController.h"
#include "VolumeController.h"

isisUserStudy::UserStudyController::UserStudyController (void)
{
    _isUserStudyEnabled = FALSE;
    _isUserStudyPaused = FALSE;
    _isUserStudyStarted = FALSE;
    
    // set up UI
    _studySelectionWidget = new isisUserStudy::StudySelectionWidget(0);
    _studyConfirmationWidget = new isisUserStudy::StudyConfirmationWidget(0);
    setUpMenuBarItems();
    
    // Tell Volume Controller to add the necessary objects
    
    
    // Register KVO updates
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::UserStudyController::createStudy");
}

isisUserStudy::UserStudyController::~UserStudyController (void)
{
    
    
}

void isisUserStudy::UserStudyController::setUpMenuBarItems(void)
{
    std::cout << "Set up user interface for user study" << std::endl;
    
    QMenuBar* mmb = boost::any_cast< QMenuBar* > 
    (GET_VALUE_FOR_KEY("isisCore::MainWindow::getMainMenuBar"));
    
    _userStudyMenu = new QMenu(mmb);
    _userStudyMenu->setTitle("User Study 2");
    
    _userStudyEnable = new QAction(mmb);
    _userStudyEnable->setText("Enable");
    
    _userStudyDisable = new QAction(mmb);
    _userStudyDisable->setText("Disable");
    
    _userStudySelect = new QAction(mmb);
    _userStudySelect->setText("Select");
    
    _userStudySetup = new QAction(mmb);
    _userStudySetup->setText("Setup");
    
    _userStudyStart = new QAction(mmb);
    _userStudyStart->setText("Start");
    
    _userStudyStop = new QAction(mmb);
    _userStudyStop->setText("Stop");
    
    _userStudyPause = new QAction(mmb);
    _userStudyPause->setText("Pause");
        
    _userStudyMenu->addAction(_userStudySelect);
    _userStudyMenu->addAction(_userStudySetup);
    _userStudyMenu->addAction(_userStudyEnable);
    _userStudyMenu->addAction(_userStudyDisable);
    _userStudyMenu->addAction(_userStudyStart);
    _userStudyMenu->addAction(_userStudyStop);
    _userStudyMenu->addAction(_userStudyPause);
    
    _userStudyDisable->setEnabled(FALSE);
    _userStudyStart->setEnabled(FALSE);
    _userStudyStop->setEnabled(FALSE);
    _userStudyPause->setEnabled(FALSE);
        
    mmb->addMenu(_userStudyMenu);
    
    connect(_userStudySelect, SIGNAL(triggered()), this, SLOT(onUserStudySelect()));
    connect(_userStudySetup, SIGNAL(triggered()), this, SLOT(onUserStudySetup()));
    connect(_userStudyEnable, SIGNAL(triggered()), this, SLOT(onUserStudyEnable()));
    connect(_userStudyDisable, SIGNAL(triggered()), this, SLOT(onUserStudyDisable()));
    connect(_userStudyStart, SIGNAL(triggered()), this, SLOT(onUserStudyStart()));
    connect(_userStudyStop, SIGNAL(triggered()), this, SLOT(onUserStudyStop()));
    connect(_userStudyPause, SIGNAL(triggered()), this, SLOT(onUserStudyPause()));

}


void isisUserStudy::UserStudyController::toggleStudySelectionWidget(bool toggle)
{
    // show selection widget
    if (toggle)
    {
        
    }
    
    // hide selection widget
    else
    {
        
    }
}

void isisUserStudy::UserStudyController::initializeStudyParam(void)
{
    // grab all values from the StudySelectionWidget
    
    //
}

void isisUserStudy::UserStudyController::selectStudy(void)
{
    
}

void isisUserStudy::UserStudyController::createStudy (QString st)
{    
    if (st == "Stereo vs Mono")
    {
        std::cout << "Creating Stereo-Mono Study" << std::endl;
    }
    else if (st == "2D vs 3D")
    {
        std::cout << "Creating 2D-3D Study" << std::endl;
    }
    else if (st == "Fuzzy Segmentation")
    {
        std::cout << "Creating Fuzzy Seg Study" << std::endl;
    }
    else if (st == "Probabilistic Segmentation")
    {
        std::cout << "Creating Prob Seg Study" << std::endl;
    }
    else if (st == "Colorization")
    {
        std::cout << "Creating Color Seg Study" << std::endl;
    }
    else
    {
        // invalid selection
        std::cout << "Invalid choice" << std::endl;
    }
    
}

void isisUserStudy::UserStudyController::didChangeValueForKey(boost::any value, aq::String key)
{
    if (key == "isisUserStudy::UserStudyController::createStudy")
    {
        QString val = boost::any_cast< QString >(value);
        createStudy(val); 
    }
    else
    {
        
    }
}

////////////////////////////////
// QT Slots
////////////////////////////////

void isisUserStudy::UserStudyController::onUserStudySelect (void)
{
    if (!_isUserStudyEnabled)
    {
        _isUserStudyEnabled = TRUE;
        
        _userStudyDisable->setEnabled(TRUE);
        _userStudyStart->setEnabled(TRUE);
        _userStudyStop->setEnabled(TRUE);
        _userStudyPause->setEnabled(TRUE);
    }

    _studySelectionWidget->show();
}

void isisUserStudy::UserStudyController::onUserStudySetup (void)
{
    if (!_isUserStudyEnabled)
    {
        _isUserStudyEnabled = TRUE;
        
        _userStudyDisable->setEnabled(TRUE);
        _userStudyStart->setEnabled(TRUE);
        _userStudyStop->setEnabled(TRUE);
        _userStudyPause->setEnabled(TRUE);
    }
    
    _studySelectionWidget->show();
}

void isisUserStudy::UserStudyController::onUserStudyEnable (void)
{
    if (!_isUserStudyEnabled)
    {
        _isUserStudyEnabled = TRUE;
        
        _userStudyDisable->setEnabled(TRUE);
        _userStudyStart->setEnabled(TRUE);
        _userStudyStop->setEnabled(TRUE);
        _userStudyPause->setEnabled(TRUE);

    }
    
    _studySelectionWidget->show();
}

void isisUserStudy::UserStudyController::onUserStudyDisable (void)
{
    if (_isUserStudyEnabled)
    {
        _isUserStudyEnabled = FALSE;
    
        _userStudyDisable->setEnabled(FALSE);
        _userStudyStart->setEnabled(FALSE);
        _userStudyStop->setEnabled(FALSE);
        _userStudyPause->setEnabled(FALSE);
    }
}

void isisUserStudy::UserStudyController::onUserStudyStart (void)
{
    _isUserStudyStarted = TRUE;
}

void isisUserStudy::UserStudyController::onUserStudyStop (void)
{
    _isUserStudyStarted = FALSE;
}

void isisUserStudy::UserStudyController::onUserStudyPause (void)
{
    _isUserStudyPaused = TRUE;
}





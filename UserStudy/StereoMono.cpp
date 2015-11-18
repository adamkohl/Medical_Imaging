//
//  StereMono.cpp
//  Isis
//
//  Created by Eric Foo on 1/23/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#include "StereoMono.h"

#include "DicomController.h"
#include "VolumeController.h"

isisUserStudy::StereoMono::StereoMono (void)
{
    _textActor = vtkSmartPointer<vtkTextActor>::New();
    _textActor->GetTextProperty()->SetFontSize ( 24 );
    _textActor->SetPosition2 ( 10, 40 );
    _textActor->GetTextProperty()->SetColor ( 1.0,1.0,1.0 );
    
    
    // I'm not sure why are we using KVO for this, this function is in our class I think we should call it directly - MME
    ADD_OBSERVER_WITH_KEY(this, "UserStudy::StereoMono::saveResults");
    
    // Recieving slider bar values
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::StereoMono::recieveMaxUserSlider");
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::StereoMono::recieveMinUserSlider");

    _timeElapsed = 0;
    
    _studyModeEnabled = FALSE;
}

isisUserStudy::StereoMono::~StereoMono (void)
{
    
    
}

void isisUserStudy::StereoMono::resultToFile(std::string value)
{
    std::ofstream file;
    
    file.open("/Users/adamkohl/Documents/VRAC/IsisDesktop/studies/Kinect/Results.txt", ios::app);
    if (file.is_open())
    {
        file << value << "\n";
        file.close();
    }

    
}

void isisUserStudy::StereoMono::didChangeValueForKey(boost::any value, aq::String key)
{
    if (key == "isisUserStudy::StereoMono::recieveMaxUserSlider")
    {
        _userSliderMax = boost::any_cast<int>(value);
    }
    else if (key == "isisUserStudy::StereoMono::recieveMinUserSlider")
    {
        _userSliderMin = boost::any_cast<int>(value);
    }
//    printf("I GET TO LINE %i\n", __LINE__);
//    if (key == "UserStudy::StereoMono::saveResults")
//    {
//        aq::String result = boost::any_cast<aq::String>(value);
//        
//        std::ofstream file;
//
//        file.open("/Users/marisol/Documents/isis/results.txt", ios::app);
//        if (file.is_open())
//        {
//            file << result << "\n";
//            file.close();
//        }
//    }
}

void isisUserStudy::StereoMono::start (void)
{
    _studyModeEnabled = TRUE;
    writeTextToSceen("User Study Started");
    
    // this is where the first dataset/setting is opened - MM
    setTasks();
    setNextTask();
    
    DID_UPDATE_VALUE_FOR_KEY(NULL,"isisCore::MainWindow::startTimer");
    
    std::ofstream file;
    
    // Edited by Adam Kohl
    file.open("/Users/adamkohl/Documents/VRAC/IsisDesktop/studies/Kinect/Results.txt", ios::app);
    if (file.is_open())
    {
        file << "\n\n\n================================== NEW USER STUDY at " 
                << QDateTime::currentDateTime().toString().toStdString() << "\n";
        file.close();
    }
}

void isisUserStudy::StereoMono::stop (void)
{
    _studyModeEnabled = FALSE;
    writeTextToSceen("User Study Completed");
    DID_UPDATE_VALUE_FOR_KEY(NULL,"isisCore::MainWindow::stopTimer");
    
    std::ofstream file;
    
    file.open("/Users/adamkohl/Documents/VRAC/IsisDesktop/studies/Kinect/Results.txt", ios::app);
    if (file.is_open())
    {
        file << "\n================================== END at " 
                    << QDateTime::currentDateTime().toString().toStdString() << "\n";
        file.close();
    }
}

bool isisUserStudy::StereoMono::reset (void)
{
    return TRUE;
}

void isisUserStudy::StereoMono::importSetting (std::string filename)
{
    QFile input( filename.c_str() );
}

void isisUserStudy::StereoMono::exportResults (std::string filename)
{
    QFile output( filename.c_str() );
}

void isisUserStudy::StereoMono::nextDataset (void)
{
    setNextTask();
    
    // call to restart the timer once a new set of trocars are placed
    DID_UPDATE_VALUE_FOR_KEY(NULL, "isisCore::MainWindow::restartTimer");
   
    writeTextToSceen("");
}

void isisUserStudy::StereoMono::prevDataset (void)
{
    writeTextToSceen("");
}

void isisUserStudy::StereoMono::placeTrocarAtPosition (isisColor whichTrocar, double x, double y, double z)
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

void isisUserStudy::StereoMono::orientVolume (double rotX, double rotY, double rotZ)
{
    
}

void isisUserStudy::StereoMono::captureSubjectSelection(int key)
{
//    if (key == "g" || key == "G")
//    {
//        writeTextToSceen("You selected GREEN");
//        
//        aq::String temp (getTimeElapsed());
//        temp.prepend("GREEN\t");
//        resultToFile(temp);
//        
//        //DID_UPDATE_VALUE_FOR_KEY(temp, "isisCore::StereoMono::saveResults");
//    }
//    else if (key == "b" || key == "B")
//    {
//        writeTextToSceen("You selected BLUE");
//
//        aq::String temp (getTimeElapsed());
//        temp.prepend("BLUE\t");
//        
//        resultToFile(temp);
//        
//        //DID_UPDATE_VALUE_FOR_KEY(temp, "isisCore::StereoMono::saveResults");
//    }
//
//    if (key == "q" || key == "Q")
//    {
//        writeTextToSceen("You selected LEFT");
//        
//        aq::String temp (getTimeElapsed());
//        temp.prepend("LEFT\t");
//        resultToFile(temp);
//        
//        //DID_UPDATE_VALUE_FOR_KEY(temp, "isisCore::StereoMono::saveResults");
//    }
//    else if (key == "p" || key == "P")
//    {
//        writeTextToSceen("You selected RIGHT");
//        
//        aq::String temp (getTimeElapsed());
//        temp.prepend("RIGHT\t");
//        
//        resultToFile(temp);
//        
//        //DID_UPDATE_VALUE_FOR_KEY(temp, "isisCore::StereoMono::saveResults");
//    }
//
//    else if (key == "skipped" || key == "SKIPPED")
//    {
//        writeTextToSceen("SKIPPED");
//
//        aq::String temp (getTimeElapsed());
//        temp.prepend("SKIPPED\t");
//        
//        resultToFile(temp);
//        
//        //DID_UPDATE_VALUE_FOR_KEY(temp, "isisCore::StereoMono::saveResults");
//    }

    if (key == 13)
    {
        writeTextToSceen("You selected ENTER");
        aq::String temp(getTimeElapsed());
        temp.prepend("\tTime\t");
        
        DID_UPDATE_VALUE_FOR_KEY(NULL, "DoubleSlider::getMaxUserSlider");
        aq::String upperslider(_userSliderMax);
        temp.prepend("\t");
        temp.prepend(upperslider);
        
        DID_UPDATE_VALUE_FOR_KEY(NULL, "DoubleSlider::getMinUserSlider");
        aq::String lowerslider(_userSliderMin);
        temp.prepend(lowerslider);
        
        resultToFile(temp);

    }
    
    else
    {
        writeTextToSceen("You may only select ENTER");
        return;
    }
    
    if (_tasks.empty())
    {
        stop();
        return;
    }
    
    nextDataset();
}

void isisUserStudy::StereoMono::writeTextToSceen(std::string text)
{
    _textActor->SetInput ( text.c_str() );

    vtkRenderer* renderer = boost::any_cast< vtkRenderer* > 
                (GET_VALUE_FOR_KEY("isisCore::MainWindow::getRenderer"));
    
    renderer->RemoveActor2D ( _textActor );
    
    if (text.size() > 0)
    {
        renderer->AddActor2D ( _textActor );    
    }
        
    DID_UPDATE_VALUE_FOR_KEY(NULL,"isisCore::MainWindowController::updateRenderWindow");
}

void isisUserStudy::StereoMono::renderTextInBlack(bool isRenderBlack)
{
    if (isRenderBlack)
        _textActor->GetTextProperty()->SetColor(0.0, 0.0, 0.0);
    else
        _textActor->GetTextProperty()->SetColor ( 1.0,1.0,1.0 );
    
    DID_UPDATE_VALUE_FOR_KEY(NULL,"isisCore::MainWindowController::updateRenderWindow");
}

void isisUserStudy::StereoMono::incrementTimeElapsed(void)
{
    _timeElapsed++;
}

void isisUserStudy::StereoMono::resetTimeElapsed(void)
{
    _timeElapsed = 0;
}


void isisUserStudy::StereoMono::setTasks()
{

    /* This is where the file parser values will be called, then stored in class*/
    
}

void isisUserStudy::StereoMono::setNextTask()
{
    if (_tasks.empty())
    {
        return;
    }
    
    DID_UPDATE_VALUE_FOR_KEY(_tasks.back(), "isisCore::TrocarWidget::setNextTask");
    
    _tasks.pop_back();
}



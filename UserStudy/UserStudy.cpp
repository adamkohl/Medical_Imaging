//
//  UserStudy.cpp
//  Isis
//
//  Created by Eric Foo on 1/23/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#include "UserStudy.h"
#include "DicomController.h"
#include "VolumeController.h"
#include "TrocarStudy.h"
#include "MainWindow.h"
#include <QtCore/QDir>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>

isisUserStudy::UserStudy::UserStudy (void)
{
    _textActor = vtkSmartPointer<vtkTextActor>::New();
    _textActor->GetTextProperty()->SetFontSize ( 24 );
    _textActor->SetPosition2 ( 10, 40 );
    _textActor->GetTextProperty()->SetColor ( 1.0,1.0,1.0 );
    _studyModeEnabled = FALSE;
}


isisUserStudy::UserStudy::~UserStudy (void)
{
    
    
}


void isisUserStudy::UserStudy::didChangeValueForKey(boost::any value, aq::String key)
{
    if (key == "isisUserStudy::StereoMono::recieveMaxUserSlider")
    {
        _userSliderMax = boost::any_cast<int>(value);
    }
    else if (key == "isisUserStudy::StereoMono::recieveMinUserSlider")
    {
        _userSliderMin = boost::any_cast<int>(value);
    }
}


void isisUserStudy::UserStudy::start (void)
{
    _studyModeEnabled = TRUE;
    
    writeTextToSceen("User Study Started");
    
    setTask();

    DID_UPDATE_VALUE_FOR_KEY(NULL,"isisCore::MainWindow::startTimer");
    
    std::ofstream file;
    file.open("/Users/adamkohl/Documents/VRAC/IsisDesktop/studies/Kinect/Results.txt", ios::app);
    if (file.is_open())
    {
        file << "\n\n\n================================== NEW USER STUDY at "
        << QDateTime::currentDateTime().toString().toStdString() << "\n";
        file.close();
    }
}


void isisUserStudy::UserStudy::stop(void)
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


bool isisUserStudy::UserStudy::reset(void)
{
    return TRUE;
}


void isisUserStudy::UserStudy::nextDataset(void)
{
    setTask();
    
    // call to restart the timer once new position is placed
    DID_UPDATE_VALUE_FOR_KEY(NULL, "isisCore::MainWindow::restartTimer");
    
    writeTextToSceen("");
}


void isisUserStudy::UserStudy::prevDataset(void)
{
    writeTextToSceen("");
}


void isisUserStudy::UserStudy::captureSubjectSelection(int key)
{
    if (key == 66 || key == 98)
    {
        time(&timer);
        std::cout<<timer<<std::cout;
        
        writeTextToSceen("You Selected BLUE");
        
        _results.append("BLUE\t");
//        resultToFile(_results);
    }
    
    else if (key == 71 || key == 103)
    {
        time(&timer);
        std::cout<<timer<<std::cout;

        writeTextToSceen("You selected GREEN");
                
        _results.append("GREEN\t");
//        resultToFile(_results);
    }

    else if (key == 80 || key == 112)
    {
        time(&timer);
        std::cout<<timer<<std::cout;

        writeTextToSceen("You selected RIGHT");

        _results.append("RIGHT\t");
//        resultToFile(_results);
    }

    else if (key == 81 || key == 113)
    {
        time(&timer);
        std::cout<<timer<<std::cout;

        writeTextToSceen("You selected LEFT");
        
        _results.append("LEFT\t");
//        resultToFile(_results);
    }

    /* Why are we using this? */
     
//    else if (key == "skipped" || key == "SKIPPED")
//    {
//        writeTextToSceen("SKIPPED");
//
//        aq::String temp (getTimeElapsed());
//        temp.prepend("SKIPPED\t");
//
//        resultToFile(temp);
//    }
    
    else if (key == 13)
    {
        time(&timer);
        std::cout<<timer<<std::cout;

//        writeTextToSceen("You selected ENTER");
//        aq::String temp(getTimeElapsed());
//        temp.prepend("\tTime\t");
//        
//        aq::String upperslider(_userSliderMax);
//        temp.prepend("\t");
//        temp.prepend(upperslider);
//        
//        aq::String lowerslider(_userSliderMin);
//        temp.prepend(lowerslider);
//        
//        resultToFile(temp);
    }
    
    else if (_tasks.empty())
    {
        stop();
        return;
    }
    
    else
    {
        writeTextToSceen("Invalid Response");
        return;
    }
    
    setTask();
}


void isisUserStudy::UserStudy::getStudyParameters(void)
{
    //Read in XML
    
    QDomDocument doc = getDomDocFromFile("/Users/adamkohl/Documents/VRAC/IsisDesktop/UserStudyParameters.xml");
    
    //Study Type | if counter = 1 don't get type
    
    QDomElement root = doc.documentElement();
    
    if (root.tagName() != "userStudyParameters")
    {
        std::cout<<"Cannot read userStudyParameters";
    }
    
    QDomNode node = root.firstChild();
    
    while(!node.isNull())
    {
        QDomElement e = node.toElement();
        if(!e.isNull())
        {
            if (e.tagName() == "studyType")
            {
                QString study = e.attribute("studyType");
            }
        }
    }
    
    //Data File Location | if counter = 1 don't get location
        
    //UI Setup | if counter = 1 don't get data
    
    //Time Value | if counter = 1 don't get value
    
    //Anatomy Orientation | use counter to retrieve data for each orientation

    //Task Line
    
}


void isisUserStudy::UserStudy::setUIParameters(void)
{    
    if (_leftPanelFrame == true)
    {
        _mainWindowController->onUserLeftFrame(true);
    }
    
    else if(_leftPanelFrame == false)
    {
        _mainWindowController->onUserLeftFrame(false);
    }
    
    else if (_rightPanelFrame == true)
    {
        _mainWindowController->onUserRightFrame(true);
    }
    
    else if (_rightPanelFrame == false)
    {
        _mainWindowController->onUserRightFrame(false);
    }
    
    else if (_tissueSliderGridFrame == true)
    {
        _mainWindowController->onUserSliderBar(true);
    }
    
    else if (_tissueSliderGridFrame == false)
    {
        _mainWindowController->onUserSliderBar(false);
    }
}


void isisUserStudy::UserStudy::setTask(void)
{
    getStudyParameters();
    
    _camera->SetPosition(_cameraPosition[0], _cameraPosition[1], _cameraPosition[2]);
    _camera->SetViewUp(_viewPosition[0],_viewPosition[1], _viewPosition[2]);
    
    if (_cylinderStudy == TRUE)
    {
        //call cylinder class
    }
    
    else if (_kinectStudy == TRUE)
    {
        //call kinect class
    }
    
    _camera->OrthogonalizeViewUp();
    _renderer->ResetCamera();
    updateRenderWindow();
}


void isisUserStudy::UserStudy::updateRenderWindow(void)
{
    _renderWindow->Render();
}


void isisUserStudy::UserStudy::resultToFile(std::string value)
{
    std::ofstream file;
    file.open("/Users/adamkohl/Documents/VRAC/IsisDesktop/studies/Kinect/Results.txt", ios::app);
    if (file.is_open())
    {
        file << value << "\n";
        file.close();
    }
}


void isisUserStudy::UserStudy::incrementTimeElapsed(void)
{
    _timeElapsed++;
}


void isisUserStudy::UserStudy::resetTimeElapsed(void)
{
    _timeElapsed = 0;
}


void isisUserStudy::UserStudy::writeTextToSceen(std::string text)
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


void isisUserStudy::UserStudy::renderTextInBlack(bool isRenderBlack)
{
    if (isRenderBlack)
        _textActor->GetTextProperty()->SetColor(0.0, 0.0, 0.0);
    else
        _textActor->GetTextProperty()->SetColor ( 1.0,1.0,1.0 );
    
    DID_UPDATE_VALUE_FOR_KEY(NULL,"isisCore::MainWindowController::updateRenderWindow");
}


QDomDocument getDomDocFromFile(aq::String filepath)
{
	// Create the concept file to read in
	QFile conceptFile(filepath.c_str());
	if (!conceptFile.open(QFile::ReadOnly | QFile::Text))
	{
        std::cout << "Couldn't open file.. returning" << std::endl;
        
        return QDomDocument();
	}
	
	// Set the content of the workspace DOM document
	QDomDocument conceptDoc;
	QString errorStr;
	int errorLine, errorColumn;
	if (!conceptDoc.setContent(&conceptFile, true, &errorStr, &errorLine, &errorColumn))
	{
		conceptFile.close();
        std::cout << "Encountered an error while setting the content of the QDomDoc.. returning" <<
        std::endl;
		return QDomDocument();
	}
	
	// Close the file
	conceptFile.close();
	
	return conceptDoc;
}




//
//  StudyConfirmationWidget.cpp
//  Isis
//
//  Created by Eric Foo on 4/6/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#include "StudyConfirmationWidget.h"

isisUserStudy::StudyConfirmationWidget::StudyConfirmationWidget(QWidget *parent) : QWidget(parent)
{
	scw.setupUi(this);
    
    
    connect (scw.confirmButton, SIGNAL(pressed()), this, SLOT(onConfirmButtonPressed()));
    connect (scw.editButton, SIGNAL(pressed()), this, SLOT(onEditButtonPressed()));
    
    // Register KVO updates
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::StudyConfirmationWidget::setStudyParameters");
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::");
}



isisUserStudy::StudyConfirmationWidget::~StudyConfirmationWidget ()
{
	
}

void isisUserStudy::StudyConfirmationWidget::reset(void)
{
    
}

void isisUserStudy::StudyConfirmationWidget::setStudyParameters (std::vector<QString> val)
{
    // Parse out in this order: date, location, participant ID, study set, study type
    _location = val[0];
    _participantID = val[1];
    _studySet = val[2];
    _studyType = val[3];
 
    _date = QDateTime::currentDateTime().toString();

    scw.dateValue->setText(_date);
    scw.studySetValue->setText(_studySet);
    scw.studyTypeValue->setText(_studyType);
    scw.locationValue->setText(_location);
    scw.participantIDValue->setText(_participantID);
    
    this->show();
}

void isisUserStudy::StudyConfirmationWidget::onConfirmButtonPressed(void)
{
    std::cout << "Confirm Button Pressed" << std::endl;
    
    // call UserStudyController to create study based on these values
    DID_UPDATE_VALUE_FOR_KEY(_studyType, "isisUserStudy::UserStudyController::createStudy");
    
    this->close();
    scw.confirmButton->setDown(FALSE);
}

void isisUserStudy::StudyConfirmationWidget::showStudyConfirmationWidget(void)
{
    this->show();
}

void isisUserStudy::StudyConfirmationWidget::onEditButtonPressed(void)
{
    std::cout << "Edit Button Pressed" << std::endl;
    
    // close this dialog
    this->close();
    scw.editButton->setDown(false);
    
    // open StudySelectionWidget dialog
    DID_UPDATE_VALUE_FOR_KEY(0, "isisUserStudy::StudySelectionWidget::show");
}

void isisUserStudy::StudyConfirmationWidget::didChangeValueForKey(boost::any value, aq::String key)
{
    if (key == "isisUserStudy::StudyConfirmationWidget::setStudyParameters")
    {
        std::vector<QString> val = boost::any_cast< std::vector<QString> >(value);
        setStudyParameters(val);   
    }
    else if (key == "isisUserStudy::")
    {
        
    }
    
}
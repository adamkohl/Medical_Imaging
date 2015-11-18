//
//  StudySelectionWidget.cpp
//  Isis
//
//  Created by Eric Foo on 4/6/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#include "StudySelectionWidget.h"

//isisUserStudy::StudySelectionWidgetController::StudySelectionWidgetController()
//{
//    _studySelectionWidget = new isisUserStudy::StudySelectionWidget();
//    //_studySelectionWidget->connectSignalsWithController(this);
//}
//
//isisUserStudy::StudySelectionWidgetController::~StudySelectionWidgetController()
//{
//    
//}




isisUserStudy::StudySelectionWidget::StudySelectionWidget(QWidget *parent) : QWidget(parent)
{
	ssw.setupUi(this);

    
    // connect (tw.axialSliderRed, SIGNAL(valueChanged(int)), tw.axialSpinBoxRed, SLOT(setValue(int)));
    connect (ssw.pushButton, SIGNAL(pressed()), this, SLOT(onDoneButtonPressed()));


    // Register KVO updates
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::StudySelectionWidget::show");
    ADD_OBSERVER_WITH_KEY(this, "isisUserStudy::");
}



isisUserStudy::StudySelectionWidget::~StudySelectionWidget ()
{
	
}

void isisUserStudy::StudySelectionWidget::reset(void)
{
    
}

void isisUserStudy::StudySelectionWidget::onDoneButtonPressed(void)
{
    _studySet = ssw.studySetComboBox->currentText(); 
    _location = ssw.locationTextBox->displayText();
    _participantID = ssw.participantIDTextBox->displayText();
    _studyType = ssw.studyTypeComboBox->currentText();
    _date = QDateTime::currentDateTime().toString();
    
    // send value to StudyConfirmationWidget
    // in this order: location, participant ID, study set, study type
    std::vector<QString> studyParam;
    studyParam.push_back(_location);
    studyParam.push_back(_participantID);
    studyParam.push_back(_studySet);
    studyParam.push_back(_studyType);
    
    DID_UPDATE_VALUE_FOR_KEY(studyParam, "isisUserStudy::StudyConfirmationWidget::setStudyParameters");
    
    this->close();
    ssw.pushButton->setDown(false);
}

void isisUserStudy::StudySelectionWidget::didChangeValueForKey(boost::any value, aq::String key)
{
    if (key == "isisUserStudy::StudySelectionWidget::show")
    {
        this->show();
    }
    else if (key == "isisUserStudy::")
    {

    }
    
}
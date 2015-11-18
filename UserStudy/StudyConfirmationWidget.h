//
//  StudyConfirmationWidget.h
//  Isis
//
//  Created by Eric Foo on 4/6/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#ifndef _STUDY_CONFIRMATION_WIDGET_H_
#define _STUDY_CONFIRMATION_WIDGET_H_

#include "ui_StudyConfirmationWidget.h"

namespace isisUserStudy
{
    
class StudyConfirmationWidget : public QWidget, public aq::KVObserver
{
    Q_OBJECT
    
public:
    StudyConfirmationWidget(QWidget *parent = 0);
    ~StudyConfirmationWidget();
    
    void reset (void);
    
    // Override KVO methods
    void didChangeValueForKey(boost::any value, aq::String key);
    
    
protected:
    
    
    
private:
    Ui::studyConfirmationWidget scw;
    
    void setStudyParameters (std::vector<QString> val);
    void showStudyConfirmationWidget (void);
    
    QString _date;
    QString _location;
    QString _participantID;
    QString _studySet;
    QString _studyType;
    
public slots:
    void onConfirmButtonPressed(void);
    void onEditButtonPressed(void);


private slots:
    
    
};
    
}

#endif

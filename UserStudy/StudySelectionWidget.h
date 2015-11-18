//
//  StudySelectionWidget.h
//  Isis
//
//  Created by Eric Foo on 1/23/12.
//  Copyright 2012 Iowa State University. All rights reserved.
//

#ifndef _STUDY_SELECTION_WIDGET_H_
#define _STUDY_SELECTION_WIDGET_H_

#include "ui_StudySelectionWidget.h"

namespace isisUserStudy
{
    
//class StudySelectionWidget;
//    
//class StudySelectionWidgetController : public QObject
//{
//    Q_OBJECT  
//    
//public:
//    StudySelectionWidgetController();
//    ~StudySelectionWidgetController();
//    
//    
//    
//public slots:
//    
//    
//private:
//    StudySelectionWidget* _studySelectionWidget;
//    
//
//private slots:
//    
//    
//    
//    
//};
    
class StudySelectionWidget : public QWidget, public aq::KVObserver
{
    Q_OBJECT
	
public:
	StudySelectionWidget(QWidget *parent = 0);
	~StudySelectionWidget();
    
    void reset (void);
    
    // Override KVO methods
	void didChangeValueForKey(boost::any value, aq::String key);        
    
    
    
    
protected:
    
    
    
private:
	Ui::studySelectionWidget ssw;
    
    QString _date;
    QString _location;
    QString _participantID;
    QString _studySet;
    QString _studyType;

    
public slots:
    void onDoneButtonPressed (void);
    
    
private slots:
    
    
};
    
}

#endif

#pragma once

#include <QtWidgets/QMainWindow>
#include <qvboxlayout>
#include<qlistwidget.h>
#include<qcheckbox.h>
#include<qpushbutton.h>
#include<qlineedit.h>
#include "Service.h"
#include<qmessagebox.h>

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    MainWindow(Service& serv, Chef* chef,QWidget *parent = nullptr);
    ~MainWindow();
    void update();
    void populatelist(vector<Receipe*> recs);

private:
    QWidget* mainwidget;
    QVBoxLayout* mainlayout;
    QListWidget* listofrec;
    QCheckBox* checkbox;
    QPushButton* addbutton;
    QLineEdit* recline;
    QLineEdit* prepline;
    QLineEdit* ingredline;
    QLineEdit* searchingredline;
    QPushButton* searchbutton;
    QPushButton* viewbutton;


    Service& serv;
    Chef* chef;

};

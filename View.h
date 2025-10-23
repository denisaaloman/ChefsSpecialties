#pragma once
#include <QWidget>
#include <vector>
#include "Service.h"

class ViewWindow : public QWidget, public Observer {
    Q_OBJECT

private:
    Service& serv;
    Chef* ch;
    vector<Receipe*> receipes;

public:
    ViewWindow(Service& serv,Chef* ch, QWidget* parent=nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void update() override { this->repaint(); }
};

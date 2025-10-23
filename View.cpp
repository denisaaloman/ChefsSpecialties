#include "View.h"
#include <QPainter>

ViewWindow::ViewWindow(Service& serv, Chef* ch,QWidget* parent)
    : serv(serv), ch(ch),receipes(receipes),QWidget(parent)
{
    this->serv.addobserver(this);
    this->setWindowTitle("View Window");
    this->resize(600, 600);
}

void ViewWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    int x = 50;
    int y = 50;

    for (Receipe* r : this->serv.getfilteredrec(this->ch->getcuisine())) {
        int minPrep = 20;
        int maxPrep = 120; 

        int minRadius = 30;
        int maxRadius = 80;

        int prepTime = r->getprep();
        int radius = minRadius + (prepTime - minPrep) * (maxRadius - minRadius) / (maxPrep - minPrep);
        QColor color;
        if (prepTime > 100) {
            color = Qt::red;
        }
        else {
            color = Qt::blue;
        }

        painter.setBrush(Qt::NoBrush);
        painter.setPen(color);
        painter.drawEllipse(QPoint(x + radius, y + radius), radius, radius);
        painter.drawText(x, y + radius * 2 + 20, QString::fromStdString(r->getRecName()));
       
    }
}

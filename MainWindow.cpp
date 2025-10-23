#include "MainWindow.h"
#include "View.h"

MainWindow::MainWindow(Service& serv, Chef* chef,QWidget *parent)
    : serv(serv), chef(chef), QMainWindow(parent)
{
    this->setWindowTitle(QString::fromStdString(this->chef->getname()));
    this->serv.addobserver(this);

    this->mainwidget = new QWidget();
    this->mainlayout = new QVBoxLayout();

    this->listofrec = new QListWidget();
    vector<Receipe*> recs = this->serv.getrecsortedbycuisine();
    this->populatelist(recs);
    this->checkbox = new QCheckBox();
    connect(this->checkbox, &QCheckBox::stateChanged, this, [&]() {
        if (this->checkbox->isChecked() == true) {
            vector<Receipe*> fil = this->serv.getfilteredrec(this->chef->getcuisine());
            this->populatelist(fil);
        }
        else {
            vector<Receipe*> rec = this->serv.getrecsortedbycuisine();
            this->populatelist(rec);
        }
        
    });
   
    this->recline = new QLineEdit();
    this->prepline = new QLineEdit();
    this->ingredline = new QLineEdit();


    this->addbutton = new QPushButton("Add Recipe");

    connect(this->addbutton, &QPushButton::clicked, this, [&]() {
        QString name = this->recline->text();
        int prep = this->prepline->text().toInt();
        QString ingreds = this->ingredline->text();


        if (name.isEmpty()) {
            QMessageBox::critical(this, "Error", "Name cannot be empty");
            return;
        }
        vector<string> ingredients;
        QStringList ingredList = ingreds.split(' ', Qt::SkipEmptyParts);
        for (const QString& ing : ingredList) {
                ingredients.push_back(ing.toStdString());
            }
        try {
            this->serv.addRec(name.toStdString(), this->chef->getcuisine(), prep, ingredients);
        }
        catch (runtime_error& e) {
            QMessageBox::critical(this, "Fail", e.what());
        }
         
    });
   
    
    this->searchingredline = new QLineEdit();
    this->searchbutton = new QPushButton("Search");
    QHBoxLayout* searchLayout = new QHBoxLayout();

    searchLayout->addWidget(this->searchingredline);
    searchLayout->addWidget(this->searchbutton);

    this->mainlayout->addLayout(searchLayout);

    connect(this->searchbutton, &QPushButton::clicked, this, [&]() {
        QString input = this->searchingredline->text();
        QStringList parts = input.split(',');
        vector<string> ingredients;
        for (QString& part : parts) {
            QString trimmed = part.trimmed();
            if (!trimmed.isEmpty()) {
                ingredients.push_back(trimmed.toStdString());
            }
        }

       
        vector<Receipe*> filtered = this->serv.getrecipesbyingredients(ingredients);
        if (this->checkbox->isChecked()) {
            vector<Receipe*> cuisinefiltered;
            for (Receipe* r : filtered) {
                if (r->getRecCuis() == this->chef->getcuisine())
                    cuisinefiltered.push_back(r);
            }
            this->populatelist(cuisinefiltered);
            
        }
        else

        this->populatelist(filtered);
        });

    this->viewbutton = new QPushButton("View");
    this->mainlayout->addWidget(this->viewbutton);

    connect(this->viewbutton, &QPushButton::clicked, this, [&]() {
        vector<Receipe*> chefRecs = this->serv.getfilteredrec(this->chef->getcuisine());
        ViewWindow* view = new ViewWindow(this->serv,this->chef);
        view->show();
        });




    this->mainlayout->addWidget(this->checkbox);
    this->mainlayout->addWidget(this->listofrec); 

    this->mainlayout->addWidget(this->recline);
    this->mainlayout->addWidget(this->prepline);
    this->mainlayout->addWidget(this->ingredline);
    this->mainlayout->addWidget(this->addbutton);

    

    this->mainwidget->setLayout(this->mainlayout);
    this->setCentralWidget(this->mainwidget);


}

MainWindow::~MainWindow()
{}

void MainWindow::update() {
    vector<Receipe*> rec = this->serv.getrecsortedbycuisine();
    this->populatelist(rec);

    
}

void MainWindow::populatelist(vector<Receipe*> recs) {
   
    this->listofrec->clear();
    for (Receipe* r : recs) {
        QString nam = QString::fromStdString(r->getRecName());
        QString cuis = QString::fromStdString(r->getRecCuis());
        QString prep = QString::number(r->getprep());
        QString ingr;
        for (auto ing : r->getingred()) {
            ingr = ingr + QString::fromStdString(ing)+" ";
        }

        this->listofrec->addItem(nam+" " +cuis+" "+prep+" "+ingr);
        
    }

}

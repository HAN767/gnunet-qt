#include "searchwnd.h"
#include "cangote.h"
#include "gnunetmanager.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QTabWidget>

SearchWnd::SearchWnd(QWidget *parent) :
    QWidget(parent)
{



    QVBoxLayout *searchVGlobalLayout = new QVBoxLayout;
    QHBoxLayout *searchBoxLayout = new QHBoxLayout;

    searchTermBox =   new QLineEdit(this);
    searchBtn =     new QPushButton(this);
    //searchResultList = new QTreeView(this);
    searchTab = new QTabWidget(this);


    searchBtn->setText("Search");

    searchBoxLayout->addWidget(searchTermBox);
    searchBoxLayout->addWidget(searchBtn);
    searchVGlobalLayout->addLayout(searchBoxLayout);

    searchVGlobalLayout->addWidget(searchTab);




    setLayout(searchVGlobalLayout);



    Connect();

}

void SearchWnd::CreateNewSearchTab()
{

}

void SearchWnd::Connect()
{
    connect(searchBtn, SIGNAL(clicked()), this,SLOT(OnSearch()));
}


void SearchWnd::OnSearch()
{
    QString keywords = searchTermBox->text();
    theApp->gnunetMgr->Search(keywords);
}



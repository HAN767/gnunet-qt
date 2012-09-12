#include "cangote.h"
#include <gnunetmanager.h>
#include "cangoteDlg.h"
#include <QApplication>

Cangote* theApp;
Cangote::Cangote(QObject *parent) :
    QObject(parent)
{
    theApp =this;




    gnunetMgr = new GNUnetManager();
    gnunetMgr->Init();

    cangoteDlg = new CangoteDlg();

    cangoteDlg->show();
    cangoteDlg->Connect();



}

void Cangote::Connect()
{
     //connect( gnunetMgr, SIGNAL(Event_Peer(QString)), cangoteDlg->networkWnd, SLOT(PeerEvent(QString)) );
}

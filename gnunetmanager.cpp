#include "gnunetmanager.h"
#include "eventloop.h"
#include <QMessageBox>


#include "gnunetnetworkpeersmodel.h"

GNUnetManager::GNUnetManager(QObject *parent) :
    QObject(parent)
{
}


void GNUnetManager::Init()
{
    evt = new Eventloop();
    //New thread where the Gnunet will be run on.
    eventThread = new QThread();

    peers = new GNUnetNetworkPeersModel();

        evt->moveToThread(eventThread);

        // start producing once the producer's thread has started
        evt->connect(eventThread,
                         SIGNAL(started()),
                         SLOT(Start()));


        this->connect(evt,
                         SIGNAL(new_peer(QString)),
                         SLOT(PeerEvent(QString)));

        this->connect(evt,
                         SIGNAL(PeerATSChange(QString , unsigned int, unsigned int, GNUNET_ATS_Information *, int)),
                         SLOT(PeerATSEvent(QString , unsigned int, unsigned int, GNUNET_ATS_Information *, int)));

        this->connect(evt,
                         SIGNAL(PeerHostname(QString ,QString)),
                         SLOT(PeerHostnameEvent(QString ,QString)));




        connect(this,SIGNAL(DoGNUnetSearch(QString, int)),evt, SLOT(DoSearch(QString,int)));

        this->connect(evt,
                         SIGNAL(PeerHostname(QString ,QString)),
                         SLOT(PeerHostnameEvent(QString ,QString)));




        eventThread->start();
}


void GNUnetManager::PeerEvent(QString str)
{

    if(peers->AddNewPeer(str));
        emit PeerAdded(str);

}

void GNUnetManager::PeerATSEvent(QString str, unsigned int b_in, unsigned int b_out, GNUNET_ATS_Information * vec_info, int count)
{


    int type;
    int value;
    for(int i = 0; i < count ; i++)
    {
        type =  ntohl(vec_info->type);
        value =  ntohl(vec_info->value);
    }

     peers->UpdatePeerBandwidth(str,b_in, b_out );
    //emit PeerListChanged();
}


void GNUnetManager::PeerHostnameEvent(QString id, QString hostname)
{
    peers->SetHostname(id,hostname);
}

void GNUnetManager::Search(QString terms)
{
    emit DoGNUnetSearch(terms,0);
}

#include "networkwnd.h"
#include "cangote.h"

#include <QTreeView>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>


#include "gnunetmanager.h"

#include "GNUnetNetworkPeersModel.h"
NetworkWnd::NetworkWnd(QWidget *parent) :
    QWidget(parent)
{

    peerlist = new QTreeView(this);

    peerlist->setAlternatingRowColors(true);
    peerlist->setItemsExpandable(false);
    peerlist->setRootIsDecorated(false);
    //peerlist->verticalHeader()->hide();

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(peerlist);
    setLayout(serverLayout);




    peersModel = theApp->gnunetMgr->peers;

   QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(peersModel);
    proxyModel->setDynamicSortFilter(true);


    peerlist->setModel(proxyModel);
    peerlist->setSortingEnabled(true);
}


void NetworkWnd::PeerEvent(QString id)
{

    //listModel->setStringList(theApp->gnunetMgr->GetPeerStringList());


    //peerlist->setModel(model);

    //peerlist->setModel(NULL);
    //peerlist->setModel(peersModel);

}


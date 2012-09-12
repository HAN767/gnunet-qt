#ifndef NETWORKWND_H
#define NETWORKWND_H

#include <QWidget>


class QTreeView;
class QStandardItemModel;
class GNUnetNetworkPeersModel;
class NetworkWnd : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkWnd(QWidget *parent = 0);
    
signals:
    
public slots:
    void PeerEvent(QString id);

private:
    QTreeView* peerlist;

    QStandardItemModel *model;

    GNUnetNetworkPeersModel *peersModel;
    
};

#endif // NETWORKWND_H

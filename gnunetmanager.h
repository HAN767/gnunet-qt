#ifndef GNUNETMANAGER_H
#define GNUNETMANAGER_H
#include "eventloop.h"

#include <QObject>

class GNUnetNetworkPeersModel;
class GNUnetManager : public QObject
{
    Q_OBJECT
public:
    explicit GNUnetManager(QObject *parent = 0);

    GNUnetNetworkPeersModel* peers;
    void Search(QString terms);

private:
    QThread *eventThread;
    Eventloop* evt;





signals:
    void PeerAdded(QString);
    void DoGNUnetSearch(QString terms, int anonLevel);
    
public slots:
        void Init();
        void PeerEvent(QString str);
        void PeerATSEvent(QString str, unsigned int b_in, unsigned int b_out, GNUNET_ATS_Information * vec_info, int count);
        void PeerHostnameEvent(QString ,QString);
};

#endif // GNUNETMANAGER_H

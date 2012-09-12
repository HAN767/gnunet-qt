#ifndef GNUNETNETWORKPEERSMODEL_H
#define GNUNETNETWORKPEERSMODEL_H

#include <QAbstractTableModel>


typedef struct s_Peer
{
    QString id;
    int ATS_bandwidth_in;
    int ATS_bandwidth_out;
    QString hostname;
}s_Peer;



class GNUnetNetworkPeersModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GNUnetNetworkPeersModel(QObject *parent = 0);
    bool AddNewPeer(QString key);
    void UpdatePeerBandwidth(QString key, unsigned int b_in, unsigned int b_out);
    void SetHostname(QString key, QString address);
signals:
    
public slots:

private:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void onDataChanged();
    QModelIndex idToIndex(QString id);

private:
        QHash<QString, int> m_lookupIndex;
        QList<s_Peer> m_data;
    
};

#endif // GNUNETNETWORKPEERSMODEL_H

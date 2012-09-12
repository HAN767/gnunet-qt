#include "gnunetnetworkpeersmodel.h"
#include <sstream>

GNUnetNetworkPeersModel::GNUnetNetworkPeersModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

void GNUnetNetworkPeersModel::onDataChanged()
{
    beginResetModel();
    endResetModel();
}

int GNUnetNetworkPeersModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int GNUnetNetworkPeersModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant GNUnetNetworkPeersModel::data(const QModelIndex& index, int role) const
{
  if(role == Qt::DisplayRole)
    {


       switch(index.column())
       {
           case 0:
               return m_data[index.row()].id;
               break;
           case 1:
               return m_data[index.row()].ATS_bandwidth_in;
               break;
           case 2:
               return m_data[index.row()].ATS_bandwidth_out;
               break;
           case 3:
               return m_data[index.row()].hostname;
               break;
           default:
                 return QVariant::Invalid;
       }

    }

  return QVariant::Invalid;
}

QVariant GNUnetNetworkPeersModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return tr("ID");
                    break;

                case 1:
                    return tr("Bandwidth In");
                    break;

                case 2:
                    return tr("Bandwidth Out");
                    break;
                case 3:
                    return tr("Address");
                    break;


                default:
                    return QVariant();
            }
        }
        return QVariant();
}

bool GNUnetNetworkPeersModel::AddNewPeer(QString key)
{


    if (m_lookupIndex.contains(key))
    {
      return false;
    }
    else
    {
        int index = m_data.count();
        beginInsertRows(QModelIndex(), index, index);
        s_Peer item;
        item.id = key;
        item.ATS_bandwidth_in = 0;
        item.ATS_bandwidth_out = 0;


        m_data.append(item);

        m_lookupIndex[key] = index;
        endInsertRows();
        return true;
    }


}

void GNUnetNetworkPeersModel::UpdatePeerBandwidth(QString key, unsigned int b_in, unsigned int b_out)
{

    int vindex = m_lookupIndex[key];

    m_data[vindex].ATS_bandwidth_in  = b_in;
    m_data[vindex].ATS_bandwidth_out  = b_out;

    emit dataChanged(index(vindex, 0), index(vindex, 2));


}

void GNUnetNetworkPeersModel::SetHostname(QString key, QString hostname)
{
    int vindex = m_lookupIndex[key];

    m_data[vindex].hostname = hostname;

    emit dataChanged(index(vindex, 0), index(vindex, 2));
}

QModelIndex GNUnetNetworkPeersModel::idToIndex(QString id){
    if(!m_lookupIndex.contains(id))
        return QModelIndex();
    int ind = m_lookupIndex[id];
    // it'd be 2 times faster using iterators, but it's just an example, so...
    return index(ind, 0);
}


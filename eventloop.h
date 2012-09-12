#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <QtCore>
#include <QString>

#include "gnunet_includes.h"



class Eventloop : public QObject
{
    Q_OBJECT
public:
    explicit Eventloop(QObject *parent = 0);
    const struct GNUNET_CONFIGURATION_Handle * getConfiguration();

    void peerinfo_processor(void *cls, const struct GNUNET_PeerIdentity *peer,
                                        const struct GNUNET_HELLO_Message *hello,
                                        const char *err_msg);
    void status_cb (void *cls,
           const struct GNUNET_HELLO_Address *address,
               struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
               struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
               const struct GNUNET_ATS_Information *ats,
           uint32_t ats_count);

    void       peer_address_cb (void *cls, const struct GNUNET_PeerIdentity *peer,
                        const struct GNUNET_HELLO_Address *address);
    void       peer_address_string_cb (void *cls, const char *address);

    void *
    GNUNET_fs_event_handler (void *cls,
                                 const struct GNUNET_FS_ProgressInfo *info);



    void ProcessEvents();

signals:
    void new_peer(QString);
    void PeerATSChange(QString , unsigned int, unsigned int, GNUNET_ATS_Information *, int);
    void PeerHostname(QString, QString);

public slots:
    void Start();
    void DoSearch(QString terms, int anonLevel);


private:

};

#endif // EVENTLOOP_H

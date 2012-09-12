#ifndef GNUNET_DEFINITIONS_H
#define GNUNET_DEFINITIONS_H





namespace GNUnet
{

//////////////FILE SHARING////////////////////////
/**
 * Handle for file-sharing operations.
 */
static struct GNUNET_FS_Handle *fs;











    /**
     * Information we track for each peer outside of the model.
     */
    struct PeerInfo
    {

      /**
       * Handle to an active lookup for addresses of this peer, or NULL.
       */
      struct GNUNET_TRANSPORT_PeerIterateContext *palc;

      /**
       * Handle for address to string conversion.
       */
      struct GNUNET_TRANSPORT_AddressToStringContext *tos;

      /**
       * Did we get any address?
       */
      int got_address;

      struct GNUNET_CRYPTO_HashAsciiEncoded id;
    };

    /**
     * Map of peer identities to the respective PeerInfo for our view.
     */
    static struct GNUNET_CONTAINER_MultiHashMap *peer2info;

    static struct GNUNET_CONFIGURATION_Handle *gcfg;


    /**
     * Handle for our notifications from peerinfo about new peers.
     */
    static struct GNUNET_PEERINFO_NotifyContext *pnc;

    /**
     * Handle to ATS service.
     */
    static struct GNUNET_ATS_PerformanceHandle *ats;


    static void peerinfo_processor (void *cls, const struct GNUNET_PeerIdentity *peer,
                        const struct GNUNET_HELLO_Message *hello,
                        const char *err_msg);


    void main_loop(void *cls, char *const *args, const char *cfgfile,
                   const struct GNUNET_CONFIGURATION_Handle *cfg);

    static void status_cb (void *cls,
           const struct GNUNET_HELLO_Address *address,
               struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
               struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
               const struct GNUNET_ATS_Information *ats,
           uint32_t ats_count);




    ////////////////////FILE SHARING///////////////////
    void *
    GNUNET_fs_event_handler (void *cls,
                                 const struct GNUNET_FS_ProgressInfo *info);
}




#endif // GNUNET_DEFINITIONS_H

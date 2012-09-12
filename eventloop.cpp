#include "eventloop.h"
#include "gnunet_definitions.h"


static Eventloop* eventApp;


namespace GNUnet
{

/**
 * Dummy task to keep our scheduler running.
 */
static void
keepalive_task (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc)
{
    eventApp->ProcessEvents();
    GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_SECONDS, 1), &keepalive_task, NULL);
}



    void main_loop(void *cls, char *const *args, const char *cfgfile,
                       const struct GNUNET_CONFIGURATION_Handle *cfg)
    {


        unsigned int dl_parallel = 128;
        unsigned int req_parallel = 100000;





             gcfg = GNUNET_CONFIGURATION_create ();

             (void) GNUNET_CONFIGURATION_load (gcfg, "cangote.conf");

             peer2info = GNUNET_CONTAINER_multihashmap_create (256);
             pnc =   GNUNET_PEERINFO_notify (gcfg, GNUnet::peerinfo_processor, NULL);
             if (pnc == NULL)
             {
                 //Fail to connect
                 exit(1);

             }
             ats = GNUNET_ATS_performance_init (gcfg, &GNUnet::status_cb, NULL);


             /* initialize file-sharing */

              fs = GNUNET_FS_start (gcfg, "gnunet-qt",
                         &GNUnet::GNUNET_fs_event_handler, NULL,
                         (GNUNET_FS_Flags)(GNUNET_FS_FLAGS_PERSISTENCE | GNUNET_FS_FLAGS_DO_PROBES),
                                     GNUNET_FS_OPTIONS_DOWNLOAD_PARALLELISM,
                                     (unsigned int) dl_parallel,
                                     GNUNET_FS_OPTIONS_REQUEST_PARALLELISM,
                                     (unsigned int) req_parallel,
                                     GNUNET_FS_OPTIONS_END);


              GNUNET_SCHEDULER_add_now ( &keepalive_task, NULL);




     }

    static void peerinfo_processor (void *cls, const struct GNUNET_PeerIdentity *peer,
                        const struct GNUNET_HELLO_Message *hello,
                        const char *err_msg)
    {
        eventApp->peerinfo_processor(cls, peer, hello, err_msg);
    }

    static void status_cb (void *cls,
           const struct GNUNET_HELLO_Address *address,
               struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
               struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
               const struct GNUNET_ATS_Information *ats,
           uint32_t ats_count)
    {

        eventApp->status_cb(cls,address, bandwidth_in, bandwidth_out, ats,ats_count);

    }


    static void
    peer_address_cb (void *cls, const struct GNUNET_PeerIdentity *peer,
                     const struct GNUNET_HELLO_Address *address)
    {
        eventApp->peer_address_cb(cls,peer,address);
     }
    static void
    peer_address_string_cb (void *cls, const char *address)
    {
        eventApp->peer_address_string_cb(cls,address);
    }






    ///////////////////////FILE SHARING/////////////////
    void *
    GNUNET_fs_event_handler (void *cls,
                                 const struct GNUNET_FS_ProgressInfo *info)
    {
       return eventApp->GNUNET_fs_event_handler(cls,info);
    }
}


Eventloop::Eventloop(QObject *parent) :
    QObject(parent)
{
    eventApp = this;
}


const struct GNUNET_CONFIGURATION_Handle * Eventloop::getConfiguration()
{

    return GNUnet::gcfg;
}


void Eventloop::Start()
{

    static struct GNUNET_GETOPT_CommandLineOption options[] = {
      GNUNET_GETOPT_OPTION_END
    };

   char * teste = "cangote";
   int ret =
            GNUNET_PROGRAM_run (1, (char *const *)teste, "cangote", "cangote help", options,
                            &GNUnet::main_loop, NULL);


}

/**
 * Function called for peers that we know about.
 *
 * @param cls closure
 * @param peer id of the peer, NULL for last call
 * @param hello hello message for the peer (can be NULL)
 * @param err_msg NULL if successful, otherwise contains error message
 */
void Eventloop::peerinfo_processor(void *cls, const struct GNUNET_PeerIdentity *peer,
                                    const struct GNUNET_HELLO_Message *hello,
                                    const char *err_msg)
{
      struct GNUNET_CRYPTO_HashAsciiEncoded enc;
      struct GNUnet::PeerInfo *info;


      info = (GNUnet::PeerInfo*)GNUNET_CONTAINER_multihashmap_get (GNUnet::peer2info, &peer->hashPubKey);


      if (NULL == info)
      {


          GNUNET_CRYPTO_hash_to_enc (&peer->hashPubKey, &enc);
          info = (GNUnet::PeerInfo*)GNUNET_malloc (sizeof (struct GNUnet::PeerInfo));
          GNUNET_CONTAINER_multihashmap_put (GNUnet::peer2info, &peer->hashPubKey, info,
                                             GNUNET_CONTAINER_MULTIHASHMAPOPTION_UNIQUE_ONLY);

          QString str((char *)&enc);
          emit new_peer(str);

      }
      if (NULL == info->palc)
      {
          info->palc = GNUNET_TRANSPORT_peer_get_active_addresses (getConfiguration (), peer,
                                                                  GNUNET_NO,
                                                                  GNUNET_TIME_UNIT_FOREVER_REL,
                                                                  &GNUnet::peer_address_cb, info);
      }


}

/**
 * Method called whenever a given peer has a QoS status change.
 *
 * @param cls closure
 * @param address the address
 * @param bandwidth_in available amount of inbound bandwidth
 * @param bandwidth_out available amount of outbound bandwidth
 * @param ats performance data for the address (as far as known)
 * @param ats_count number of performance records in 'ats'
 */
void
Eventloop::status_cb (void *cls,
       const struct GNUNET_HELLO_Address *address,
           struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
           struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
           const struct GNUNET_ATS_Information *ats,
       uint32_t ats_count)
{

    struct PeerInfo *info;
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;



    info = (PeerInfo*)GNUNET_CONTAINER_multihashmap_get (GNUnet::peer2info, &address->peer.hashPubKey);
    if (NULL == info)
      return;                     /* should rarely happen... */


    GNUNET_CRYPTO_hash_to_enc (&address->peer.hashPubKey, &enc);

    QString str((char *)&enc);





    GNUNET_ATS_Information * atsinfo = new GNUNET_ATS_Information[ats_count];
    for(unsigned int i = 0 ; i < ats_count ; i++)
        memcpy(&atsinfo[i], &ats[i], sizeof(GNUNET_ATS_Information));


    emit PeerATSChange(str,(unsigned int)ntohl(bandwidth_in.value__), (unsigned int)ntohl(bandwidth_out.value__),atsinfo, ats_count );
}



/**
 * Function to call with a binary format of an address
 *
 * @param cls the 'struct PeerInfo' for which this is a valid address
 * @param peer peer the update is about
 * @param address NULL on disconnect, otherwise 0-terminated printable UTF-8 string
 */
void
Eventloop::peer_address_cb (void *cls, const struct GNUNET_PeerIdentity *peer,
                 const struct GNUNET_HELLO_Address *address)
{
    struct GNUnet::PeerInfo *info = (GNUnet::PeerInfo *)cls;


    if (NULL == address)
    {
      /* disconnect */
     // gtk_list_store_set (ls, &iter,
     //         PEERINFO_MC_NUMBER_OF_ADDRESSES, (guint) 0,
     //         PEERINFO_MC_CONNECTIVITY_LED, led_red,
     //         PEERINFO_MC_CONNECTED_STATUS, FALSE,
     //                     -1);
      return;
    }
    GNUNET_CRYPTO_hash_to_enc (&address->peer.hashPubKey, &info->id);


   // gtk_list_store_set (ls, &iter,
     //           PEERINFO_MC_NUMBER_OF_ADDRESSES, 1,
     //           PEERINFO_MC_CONNECTIVITY_LED, led_green,
     //           PEERINFO_MC_CONNECTED_STATUS, TRUE,
     //           -1);
    if (NULL != info->tos)
      GNUNET_TRANSPORT_address_to_string_cancel (info->tos);
    info->got_address = GNUNET_NO;



    info->tos =
        GNUNET_TRANSPORT_address_to_string (getConfiguration (), address,
                                            GNUNET_NO,
                                            GNUNET_TIME_UNIT_FOREVER_REL,
                                            &GNUnet::peer_address_string_cb, info);

  }

/**
 * Function to call with the text format of an address
 *
 * @param cls the 'struct PeerInfo' for which this is a valid address
 * @param address address as a string, NULL on error
 */
void
Eventloop::peer_address_string_cb (void *cls, const char *address)
{
  struct GNUnet::PeerInfo *info = (GNUnet::PeerInfo *)cls;

  char *country;
  const char *colon;
  const char *dot;

  if (NULL == address)
  {
    /* error */
   // if (GNUNET_NO == info->got_address)
     // gtk_list_store_set (ls, &iter,
    //		  PEERINFO_MC_NUMBER_OF_ADDRESSES, (guint) 1,
    //		  PEERINFO_MC_COUNTRY_NAME, NULL,
    //		  PEERINFO_MC_COUNTRY_FLAG, NULL,
    //		  PEERINFO_MC_ADDRESS_AS_STRING, "<no address>",
    //		  PEERINFO_MC_CONNECTIVITY_LED, led_green,
    //		  PEERINFO_MC_CONNECTED_STATUS, TRUE,
    //		  -1);
    info->tos = NULL;
    return;
  }

  QString peerid((char *)&info->id);

  /* last address, store information in model */
  country = NULL;
  colon = strstr (address, ":");
  if (NULL != colon)
  {
    for (dot = colon - 1; dot != address; dot--)
      if ('.' == *dot)
    break;
    if ('.' == *dot)
      country = GNUNET_strndup (&dot[1], (colon - dot) - 1);
  }
  //gtk_list_store_set (ls, &iter,
    //	      PEERINFO_MC_NUMBER_OF_ADDRESSES, 1,
    //	      PEERINFO_MC_COUNTRY_NAME, country,
    //	      PEERINFO_MC_COUNTRY_FLAG, GNUNET_PEERINFO_GTK_get_flag (country),
    //	      PEERINFO_MC_ADDRESS_AS_STRING, address,
    //	      PEERINFO_MC_CONNECTIVITY_LED, led_green,
    //	      PEERINFO_MC_CONNECTED_STATUS, TRUE,
    //	      -1);
  GNUNET_free_non_null (country);
  info->got_address = GNUNET_YES;

  QString hostname((char *)address);

  emit PeerHostname(peerid,hostname);
}


void *
Eventloop::GNUNET_fs_event_handler (void *cls,
                             const struct GNUNET_FS_ProgressInfo *info)
{
    void *ret;

     switch (info->status)
     {
        /*
     case GNUNET_FS_STATUS_PUBLISH_START:
       return setup_publish (info->value.publish.pc, info->value.publish.filename,
                             info->value.publish.size, info->value.publish.pctx);
     case GNUNET_FS_STATUS_PUBLISH_RESUME:
       ret =
           setup_publish (info->value.publish.pc, info->value.publish.filename,
                          info->value.publish.size, info->value.publish.pctx);
       if (NULL == ret)
         return ret;
       if (NULL != info->value.publish.specifics.resume.message)
       {
         handle_publish_error (ret,
                   info->value.publish.specifics.resume.message);
       }
       else if (NULL != info->value.publish.specifics.resume.chk_uri)
       {
         handle_publish_completed (ret,
                   info->value.publish.specifics.resume.chk_uri);
       }
       return ret;
     case GNUNET_FS_STATUS_PUBLISH_SUSPEND:
       handle_publish_stop (info->value.publish.cctx);
       return NULL;
     case GNUNET_FS_STATUS_PUBLISH_PROGRESS:
       mark_publish_progress (info->value.publish.cctx,
                  info->value.publish.size,
                  info->value.publish.completed);
       return info->value.publish.cctx;
     case GNUNET_FS_STATUS_PUBLISH_ERROR:
       handle_publish_error (info->value.publish.cctx,
                 info->value.publish.specifics.error.message);
       return info->value.publish.cctx;
     case GNUNET_FS_STATUS_PUBLISH_COMPLETED:
       handle_publish_completed (info->value.publish.cctx,
                     info->value.publish.specifics.completed.chk_uri);
       return info->value.publish.cctx;
     case GNUNET_FS_STATUS_PUBLISH_STOPPED:
       handle_publish_stop (info->value.publish.cctx);
       return NULL;
     case GNUNET_FS_STATUS_DOWNLOAD_START:
       return setup_download (info->value.download.cctx, info->value.download.pctx,
                              info->value.download.sctx, info->value.download.dc,
                              info->value.download.uri,
                              info->value.download.filename,
                              info->value.download.specifics.start.meta,
                              info->value.download.size,
                              info->value.download.completed);
     case GNUNET_FS_STATUS_DOWNLOAD_RESUME:
       ret =
           setup_download (info->value.download.cctx, info->value.download.pctx,
                           info->value.download.sctx, info->value.download.dc,
                           info->value.download.uri, info->value.download.filename,
                           info->value.download.specifics.resume.meta,
                           info->value.download.size,
                           info->value.download.completed);
       if (NULL != info->value.download.specifics.resume.message)
         mark_download_error (ret,
                  info->value.download.specifics.resume.message);
       return ret;
     case GNUNET_FS_STATUS_DOWNLOAD_SUSPEND:
       stop_download (info->value.download.cctx);
       return NULL;
     case GNUNET_FS_STATUS_DOWNLOAD_PROGRESS:
       mark_download_progress (info->value.download.cctx,
                   info->value.download.filename,
                   info->value.download.size,
                   info->value.download.completed,
                   info->value.download.specifics.progress.data,
                   info->value.download.specifics.progress.
                   offset,
                   info->value.download.specifics.progress.
                   data_len,
                   info->value.download.specifics.progress.
                   depth);
       return info->value.download.cctx;
     case GNUNET_FS_STATUS_DOWNLOAD_ERROR:
       mark_download_error (info->value.download.cctx,
                info->value.download.specifics.error.message);
       return info->value.download.cctx;
     case GNUNET_FS_STATUS_DOWNLOAD_COMPLETED:
       mark_download_completed (info->value.download.cctx,
                    info->value.download.size);
       return info->value.download.cctx;
     case GNUNET_FS_STATUS_DOWNLOAD_STOPPED:
       stop_download (info->value.download.cctx);
       return NULL;
     case GNUNET_FS_STATUS_DOWNLOAD_ACTIVE:
       change_download_color (info->value.download.cctx, "yellow");
       change_download_status_icon (info->value.download.cctx,
                    GNUNET_GTK_animation_context_get_pixbuf (animation_downloading));
       return info->value.download.cctx;
     case GNUNET_FS_STATUS_DOWNLOAD_INACTIVE:
       change_download_color (info->value.download.cctx, "blue");
       change_download_status_icon (info->value.download.cctx,
                    GNUNET_GTK_animation_context_get_pixbuf (animation_download_stalled));
       return info->value.download.cctx;
     case GNUNET_FS_STATUS_DOWNLOAD_LOST_PARENT:
       download_lost_parent (info->value.download.cctx);
       return info->value.download.cctx;

     case GNUNET_FS_STATUS_SEARCH_START:
       if (NULL != info->value.search.pctx)
         return setup_inner_search (info->value.search.sc,
                                    info->value.search.pctx);
       return setup_search_tab (info->value.search.sc, info->value.search.query);
     case GNUNET_FS_STATUS_SEARCH_RESUME:
       ret = setup_search_tab (info->value.search.sc, info->value.search.query);
       if (info->value.search.specifics.resume.message)
         handle_search_error (ret,
                  info->value.search.specifics.resume.message);
       return ret;
     case GNUNET_FS_STATUS_SEARCH_RESUME_RESULT:
       ret =
           process_search_result (info->value.search.cctx, info->value.search.pctx,
                                  info->value.search.specifics.resume_result.uri,
                                  info->value.search.specifics.resume_result.meta,
                                  info->value.search.specifics.resume_result.
                                  result,
                                  info->value.search.specifics.resume_result.
                                  applicability_rank);
       update_search_result (ret,
                 info->value.search.specifics.resume_result.
                 meta,
                 info->value.search.specifics.resume_result.
                 applicability_rank,
                 info->value.search.specifics.resume_result.
                 availability_certainty,
                 info->value.search.specifics.resume_result.
                 availability_rank);
       return ret;
     case GNUNET_FS_STATUS_SEARCH_SUSPEND:
       close_search_tab (info->value.search.cctx);
       return NULL;
     case GNUNET_FS_STATUS_SEARCH_RESULT:
       return process_search_result (info->value.search.cctx,
                                     info->value.search.pctx,
                                     info->value.search.specifics.result.uri,
                                     info->value.search.specifics.result.meta,
                                     info->value.search.specifics.result.result,
                                     info->value.search.specifics.result.
                                     applicability_rank);
     case GNUNET_FS_STATUS_SEARCH_RESULT_NAMESPACE:
       GNUNET_break (0);
       break;
     case GNUNET_FS_STATUS_SEARCH_UPDATE:
       update_search_result (info->value.search.specifics.update.cctx,
                 info->value.search.specifics.update.meta,
                 info->value.search.specifics.update.
                 applicability_rank,
                 info->value.search.specifics.update.
                 availability_certainty,
                 info->value.search.specifics.update.
                 availability_rank);
       return info->value.search.specifics.update.cctx;
     case GNUNET_FS_STATUS_SEARCH_ERROR:
       handle_search_error (info->value.search.cctx,
                info->value.search.specifics.error.message);
       return info->value.search.cctx;
     case GNUNET_FS_STATUS_SEARCH_PAUSED:
       return info->value.search.cctx;
     case GNUNET_FS_STATUS_SEARCH_CONTINUED:
       return info->value.search.cctx;
     case GNUNET_FS_STATUS_SEARCH_RESULT_STOPPED:
       free_search_result (info->value.search.specifics.result_stopped.cctx);
       return NULL;
     case GNUNET_FS_STATUS_SEARCH_RESULT_SUSPEND:
       free_search_result (info->value.search.specifics.result_suspend.cctx);
       return NULL;
     case GNUNET_FS_STATUS_SEARCH_STOPPED:
       close_search_tab (info->value.search.cctx);
       return NULL;
       /*
     case GNUNET_FS_STATUS_UNINDEX_START:
       return info->value.unindex.cctx;
     case GNUNET_FS_STATUS_UNINDEX_RESUME:
       return GNUNET_FS_GTK_unindex_handle_resume_ (info->value.unindex.uc,
                            info->value.unindex.filename,
                            info->value.unindex.size,
                            info->value.unindex.completed,
                            info->value.unindex.specifics.resume.message);
     case GNUNET_FS_STATUS_UNINDEX_SUSPEND:
       GNUNET_FS_GTK_unindex_handle_stop_ (info->value.unindex.cctx);
       return NULL;
     case GNUNET_FS_STATUS_UNINDEX_PROGRESS:
       GNUNET_FS_GTK_unindex_handle_progress_ (info->value.unindex.cctx,
                           info->value.unindex.completed);
       return info->value.unindex.cctx;
     case GNUNET_FS_STATUS_UNINDEX_ERROR:
       GNUNET_FS_GTK_unindex_handle_error_ (info->value.unindex.cctx,
                        info->value.unindex.specifics.error.message);
       return info->value.unindex.cctx;
     case GNUNET_FS_STATUS_UNINDEX_COMPLETED:
       GNUNET_FS_GTK_unindex_handle_completed_ (info->value.unindex.cctx);
       return info->value.unindex.cctx;
     case GNUNET_FS_STATUS_UNINDEX_STOPPED:
       GNUNET_FS_GTK_unindex_handle_stop_ (info->value.unindex.cctx);
       return NULL;
     default:
       GNUNET_break (0);
       break;

     */
     }
     return NULL;

}


































void
Eventloop::DoSearch(QString terms, int anonLevel)
{
    char *emsg = NULL;
    struct GNUNET_FS_Uri *uri;

    QByteArray byteArray = terms.toUtf8();
    const char* cString = byteArray.constData();



        uri = GNUNET_FS_uri_ksk_create (cString, &emsg);
        if (NULL == uri)
        {
          //GNUNET_log (GNUNET_ERROR_TYPE_ERROR, _("Invalid keyword string `%s': %s"),
           //           cString, emsg);
          GNUNET_free_non_null (emsg);
          return;
        }

        /* start search */
        GNUNET_FS_search_start (GNUnet::fs,
                    uri, anonLevel,
                                GNUNET_FS_SEARCH_OPTION_NONE, NULL);
        GNUNET_FS_uri_destroy (uri);
}

void
Eventloop::ProcessEvents()
{
    QCoreApplication::processEvents();
}

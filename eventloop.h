#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <QtCore>
#include <QString>

#include "gnunet_includes.h"

/**
 * Information we keep for each search result entry in any search tab.
 * An entry like this is also generated for downloads by-URI.  Used to
 * quickly identify the tab and row of the result; stored in the
 * user-context of the FS library for the search result.
 */
struct SearchResult
{
  /**
   * Where in the tab is this result?
   */
  //GtkTreeRowReference *rr;

  /**
   * Tab storing this result.
   */
  struct SearchTab *tab;

  /**
   * Search result for top-level results and
   * namespace-update results.
   */
  struct GNUNET_FS_SearchResult *result;

  /**
   * Associated download, or NULL for none.
   */
  struct DownloadEntry *download;
};


/**
 * Context we keep for a search tab.
 */
struct SearchTab
{
  /**
   * This is a doubly-linked list.
   */
  struct SearchTab *next;

  /**
   * This is a doubly-linked list.
   */
  struct SearchTab *prev;

  /**
   * Set in case this is an inner search, otherwise NULL.
   */
  struct SearchResult *parent;

  /**
   * Handle for this search with FS library.
   */
  struct GNUNET_FS_SearchContext *sc;

  /**
   * Text of the search query.
   */
  char *query_txt;


  /**
   * Number of results we got for this search.
   */
  unsigned int num_results;

};


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

        void ProcessEvents();

    ////////////FILESHARING/////////////////////////
    void *
    GNUNET_fs_event_handler (void *cls,
                                 const struct GNUNET_FS_ProgressInfo *info);

        ////////SEARCH//////////
    struct SearchTab *
    setup_inner_search (struct GNUNET_FS_SearchContext *sc,
                        struct SearchResult *parent);
    struct SearchTab *
    setup_search_tab (struct GNUNET_FS_SearchContext *sc,
              const struct GNUNET_FS_Uri *query);
    struct SearchResult *
    process_search_result (struct SearchTab *tab,
                   struct SearchResult *parent,
                           const struct GNUNET_FS_Uri *uri,
                           const struct GNUNET_CONTAINER_MetaData *meta,
                           struct GNUNET_FS_SearchResult *result,
                           uint32_t applicability_rank);
    void
    update_search_result (struct SearchResult *sr,
                          const struct GNUNET_CONTAINER_MetaData *meta,
                          uint32_t applicability_rank,
                  int32_t availability_rank,
                          uint32_t availability_certainty);
    void
    close_search_tab (struct SearchTab *tab);
    void
    free_search_result (struct SearchResult *sr);

    void
    handle_search_error (struct SearchTab *tab,
                 const char *emsg);


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

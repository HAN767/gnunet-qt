/*
     This file is part of GNUnet.
     (C) 2011 Christian Grothoff (and other contributing authors)

     GNUnet is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 2, or (at your
     option) any later version.

     GNUnet is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with GNUnet; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
*/

/**
 * @file src/include/gnunet_gtk.h
 * @brief Helper library for Gtk user interfaces to GNUnet
 * @author Christian Grothoff
 */
#ifndef GNUNET_GTK_H
#define GNUNET_GTK_H

#ifndef HAVE_USED_CONFIG_H
#define HAVE_USED_CONFIG_H
#if HAVE_CONFIG_H
#include "gnunet_gtk_config.h"
#endif
#endif

#include <gnunet/platform.h>
#include <gnunet/gnunet_util_lib.h>
#include <gnunet/gnunet_fs_service.h>
#include <extractor.h>
#include <gtk/gtk.h>
#include <gladeui/glade.h>
#include <gdk/gdkkeysyms.h>
#ifndef GDK_KEY_Return
#define GDK_KEY_Return GDK_Return
#endif
#ifndef GDK_KEY_Delete
#define GDK_KEY_Delete GDK_Delete
#endif

/* ****************** Initialization *************** */

/**
 * Initialize natural language support.
 */
void
GNUNET_GTK_setup_nls (void);


/**
 * Initialize GTK search path for icons.
 */
void
GNUNET_GTK_set_icon_search_path (void);


/**
 * Get the name of the directory where all of our package
 * data is stored ($PREFIX/share/)
 *
 * @return name of the data directory
 */
const char *
GNUNET_GTK_get_data_dir (void);


/**
 * @brief get the path to a specific GNUnet installation directory or,
 * with GNUNET_IPK_SELF_PREFIX, the current running apps installation directory
 * @author Milan
 * @return a pointer to the dir path (to be freed by the caller)
 */
char *
GNUNET_GTK_installation_get_path (enum GNUNET_OS_InstallationPathKind dirkind);


/* **************** Glade/Gtk helpers *************** */

/**
 * Create an initialize a new builder based on the GNUnet-GTK glade
 * file.
 *
 * @param filename name of the resource file to load
 * @param user_data user_data to pass to signal handlers,
 *        use "NULL" to pass the GtkBuilder itself.
 * @return NULL on error
 */
GtkBuilder *
GNUNET_GTK_get_new_builder (const char *filename,
			    void *user_data);


/**
 * This displays an about dialog.
 *
 * @param dialogfile name of the glade file containing the dialog
 */
void
GNUNET_GTK_display_about (const char *dialogfile);


/**
 * Obtain a string from a GtkTreeView's model.
 *
 * @param treeview treeview to inspect
 * @param treepath path that identifies the item
 * @param column number of the column with the string
 * @param value where to store the string
 * @return TRUE on success, FALSE on errors
 */
gboolean
GNUNET_GTK_get_tree_string (GtkTreeView *treeview, 
			    GtkTreePath *treepath,
                            guint column, gchar ** value);

/**
 * Create our tray icon.
 *
 * @param main handle to the main window (show or hide)
 * @param icon_name name of the tray icon file
 * @param tooltip tooltip for the tray icon
 */
void
GNUNET_GTK_tray_icon_create (GtkWindow * main, const char *icon_name,
                             const char *tooltip);


/**
 * Destroy the tray icon.
 */
void
GNUNET_GTK_tray_icon_destroy (void);


/**
 * Convert a string from the current locale to UTF-8.
 *
 * @param str_loc string in current locale
 * @return string in UTF-8, NULL if str_loc was NULL
 */
char *
GNUNET_GTK_from_loc_to_utf8 (const char * str_loc);


/**
 * Returns filename form filechooser, encoded in UTF-8.
 *
 * @param fc file chooser to inspect
 * @return selected filename as UTF-8, NULL on errors
 */
char *
GNUNET_GTK_filechooser_get_filename_utf8 (GtkFileChooser * fc);


/**
 * Remove the given entry and all of its children from the tree store.
 *
 * @param ts tree store to change
 * @param root root of the subtree to remove
 */
void
GNUNET_FS_GTK_remove_treestore_subtree (GtkTreeStore * ts,
					GtkTreeIter * root);


/* ******************* main loop ***************** */

/**
 * Handle for our main loop.
 */
struct GNUNET_GTK_MainLoop;


/**
 * Initialize the main loop.
 *
 * @param binary_name binary name
 * @param binary_help help text for the binary
 * @param argc number of command line options
 * @param argv command line options
 * @param options allowed command line options
 * @param main_window_file glade file for the main window
 * @param main_task first task to run, closure will be set to the 'struct GNUNET_GTK_MainLoop'
 * @return GNUNET_OK on success, GNUNET_SYSERR on error (i.e. bad command-line options, etc)
 */
int
GNUNET_GTK_main_loop_start (const char *binary_name, const char *binary_help,
                            int argc, char *const *argv,
                            struct GNUNET_GETOPT_CommandLineOption *options,
                            const char *main_window_file,
                            GNUNET_SCHEDULER_Task main_task);


/**
 * Get an object from the main window.
 *
 * @param ml handle to the main loop
 * @param name name of the object
 * @return NULL on error, otherwise the object
 */
GObject *
GNUNET_GTK_main_loop_get_object (struct GNUNET_GTK_MainLoop *ml,
                                 const char *name);

/**
 * Get the builder from the main window.
 *
 * @param ml handle to the main loop
 * @return NULL on error, otherwise the builder
 */
GtkBuilder *
GNUNET_GTK_main_loop_get_builder (struct GNUNET_GTK_MainLoop *ml);

int
GNUNET_GTK_main_loop_build_window (struct GNUNET_GTK_MainLoop *ml,
                                   gpointer data);


/**
 * Obtain the name of the configuration file that is being used.
 *
 * @param ml handle to the main loop
 * @return name of configuration file
 */
const char *
GNUNET_GTK_main_loop_get_configuration_file (struct GNUNET_GTK_MainLoop *ml);


/**
 * Get the configuration.
 *
 * @param ml handle to the main loop
 * @return handle to the configuration, never NULL
 */
const struct GNUNET_CONFIGURATION_Handle *
GNUNET_GTK_main_loop_get_configuration (struct GNUNET_GTK_MainLoop *ml);


/**
 * Trigger shutdown of the GUI and exit the main loop.
 *
 * @param ml handle to the main loop
 */
void
GNUNET_GTK_main_loop_quit (struct GNUNET_GTK_MainLoop *ml);


/* ******************** animations ******************* */


/**
 * Handle for an animation.  Each animation file should only
 * be loaded once and can then be used in multiple tree views.
 */
struct GNUNET_FS_AnimationContext;


/**
 * Handle to a tree view (and column) that contains animations.
 * Whenever an animation is added to a tree view, this module
 * must be told about the tree view and column for the animations
 * to work.
 */
struct GNUNET_FS_AnimationTreeViewHandle;


/**
 * Create an animation context.  Usually animation contexts are
 * created during the startup of the application and kept around
 * until shutdown.
 *
 * @param filename name of the file with the animation to show
 * @return context to use to get the animated pixbuf, NULL on error
 */
struct GNUNET_FS_AnimationContext *
GNUNET_GTK_animation_context_create (const char *filename);


/**
 * Destroy an animation context.  Should only be called after the
 * respective pixbufs are no longer needed.
 *
 * @param ac animation context to destroy.
 */
void
GNUNET_GTK_animation_context_destroy (struct GNUNET_FS_AnimationContext *ac);


/**
 * Obtain the animated pixbuf from an animation context.  Note
 * that the pixbuf will only properly work within GtkTreeViews
 * where the column with the image has been registered using
 * GNUNET_GTK_animation_tree_view_register.
 *
 * @param ac animation context to query
 * @return pixbuf of the AC, NULL on error loading the pixbuf
 */
GdkPixbuf *
GNUNET_GTK_animation_context_get_pixbuf (struct GNUNET_FS_AnimationContext *ac);


/**
 * Register a tree view column with the animation subsystem.  This
 * column may contain animated pixbufs and thus needs to be periodically
 * redrawn.
 *
 * @param tv tree view to register
 * @param image_col column in the tree view with the animated pixbufs
 * @return handle to unregister the tree view later
 */
struct GNUNET_FS_AnimationTreeViewHandle *
GNUNET_GTK_animation_tree_view_register (GtkTreeView *tv,
					 GtkTreeViewColumn *image_col);


/**
 * Unregister a tree view, it no longer needs to be updated.
 *
 * @param atv tree view to unregister
 */
void
GNUNET_GTK_animation_tree_view_unregister (struct GNUNET_FS_AnimationTreeViewHandle *atv);


#endif
/* end of gnunet_gtk.h */

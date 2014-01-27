/**
* +----------------------------------------------------------------------+
* | This file is part of Samplecat. http://ayyi.github.io/samplecat/     |
* | copyright (C) 2007-2014 Tim Orford <tim@orford.org>                  |
* +----------------------------------------------------------------------+
* | This program is free software; you can redistribute it and/or modify |
* | it under the terms of the GNU General Public License version 3       |
* | as published by the Free Software Foundation.                        |
* +----------------------------------------------------------------------+
*
*/
#ifndef __application_h__
#define __application_h__

#include "config.h"
#include <glib.h>
#include <glib-object.h>
#include "types.h"
#include "dir_tree/view_dir_tree.h"

G_BEGIN_DECLS


#define TYPE_APPLICATION            (application_get_type ())
#define APPLICATION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APPLICATION, Application))
#define APPLICATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APPLICATION, ApplicationClass))
#define IS_APPLICATION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APPLICATION))
#define IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APPLICATION))
#define APPLICATION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APPLICATION, ApplicationClass))

typedef struct _Application Application;
typedef struct _ApplicationClass ApplicationClass;
typedef struct _ApplicationPrivate ApplicationPrivate;

enum {
	SHOW_PLAYER = 0,
	SHOW_FILEMANAGER,
	SHOW_WAVEFORM,
#ifdef HAVE_FFTW3
	SHOW_SPECTROGRAM,
#endif
	MAX_VIEW_OPTIONS
};

struct _Application
{
   GObject              parent_instance;
   ApplicationPrivate*  priv;
   gint                 state;
   gboolean             loaded;

   const char*          cache_dir;
   const char*          config_dir;
   char*                config_filename;
   Config               config;
   SamplecatModel*      model;

   pthread_t            gui_thread;
   gboolean             add_recursive;
   gboolean             loop_playback;
   Auditioner const*    auditioner;
#if (defined HAVE_JACK)
   gboolean             enable_effect;
   gboolean             effect_enabled;         // read-only set by jack_player.c
   float                effect_param[3];
   float                playback_speed;
   gboolean             link_speed_pitch;
#endif
   gboolean             no_gui;
   struct _args {
      char*             search;
      char*             add;
   }                    args;

   struct _view_option {
      char*             name;
      void              (*on_toggle)(gboolean);
      gboolean          value;
      GtkWidget*        menu_item;
   }                    view_options[MAX_VIEW_OPTIONS];

   GKeyFile*            key_file;               // config file data.

   GList*               backends;
   GList*               players;

   int                  playing_id;             ///< database index of the file that is currently playing, or zero if none playing, -1 if playing an external file.

   GtkListStore*        store;
   LibraryView*         libraryview;
   Inspector*           inspector;
   PlayCtrl*            playercontrol;

   GtkWidget*           window;
   GtkWidget*           msg_panel;
   GtkWidget*           statusbar;
   GtkWidget*           statusbar2;
   GtkWidget*           search;
   GtkWidget*           context_menu;
   GtkWidget*           spectrogram;

   gboolean             colourbox_dirty;

   GNode*               dir_tree;
   GtkWidget*           dir_treeview;
   ViewDirTree*         dir_treeview2;
   GtkWidget*           fm_view;

   GdkColor             fg_colour;
   GdkColor             bg_colour;
   GdkColor             bg_colour_mod1;
   GdkColor             base_colour;
   GdkColor             text_colour;

   GAsyncQueue*         msg_queue;

   //nasty!
   gint                 mouse_x;
   gint                 mouse_y;
};

struct _ApplicationClass
{
   GObjectClass         parent_class;
};

#ifndef __main_c__
extern Application*     app;
#endif

GType        application_get_type                () G_GNUC_CONST;
Application* application_new                     ();
Application* application_construct               (GType);
void         application_emit_icon_theme_changed (Application*, const gchar*);
void         application_quit                    (Application*);


G_END_DECLS

#endif
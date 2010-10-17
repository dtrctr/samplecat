char err [32];
char warn[32];

#define EXPAND_TRUE 1
#define EXPAND_FALSE 0
#define FILL_TRUE 1
#define FILL_FALSE 0
#define NON_HOMOGENOUS 0
#define START_EDITING 1
#define TIMER_STOP FALSE

#define PALETTE_SIZE 17

#define MAX_DISPLAY_ROWS 1000

#define POINTER_OK_NULL(A, B, C) if((unsigned)A < 1024){ errprintf("%s(): bad %s pointer (%p).\n", B, C, A); return NULL; }
#ifndef USE_AYYI
#endif


typedef struct _inspector
{
	unsigned       row_id;
	GtkTreeRowReference* row_ref;
	GtkWidget*     widget;
	GtkWidget*     name;
	GtkWidget*     filename;
	GtkWidget*     tags;
	GtkWidget*     tags_ev;    //event box for mouse clicks
	GtkWidget*     length;
	GtkWidget*     samplerate;
	GtkWidget*     channels;
	GtkWidget*     mimetype;
	GtkWidget*     level;
	GtkWidget*     image;
	GtkWidget*     text;
	GtkTextBuffer* notes;
	GtkWidget*     edit;
	int            min_height;
} Inspector;


struct _config
{
	char      database_host[64];
	char      database_user[64];
	char      database_pass[64];
	char      database_name[64];
	char      show_dir[256];
	char      window_width[64];
	char      window_height[64];
	char      colour[PALETTE_SIZE][8];
	gboolean  add_recursive;
	char      column_widths[4][64];
	char      browse_dir[64];
};


struct _backend
{
	gboolean         pending;

	gboolean         (*search_iter_new)  (char* search, char* dir, const char* category, int* n_results);
	SamplecatResult* (*search_iter_next) (unsigned long**);
	void             (*search_iter_free) ();

	void             (*dir_iter_new)     ();
	char*            (*dir_iter_next)    ();
	void             (*dir_iter_free)    ();

	int              (*insert)           (Sample*, MIME_type*);
	gboolean         (*delete)           (int);
	gboolean         (*update_colour)    (int, int);
	gboolean         (*update_keywords)  (int, const char*);
	gboolean         (*update_notes)     (int, const char*);
	gboolean         (*update_pixbuf)    (Sample*);
	gboolean         (*update_online)    (int, gboolean);
	gboolean         (*update_peaklevel) (int, float);

	void             (*disconnect)       ();
};
#ifdef __main_c__
struct _backend backend = {false, NULL, NULL, NULL, NULL, NULL, NULL};
#else
extern struct _backend backend;
#endif

#define BACKEND_IS_NULL (backend.search_iter_new == NULL)

enum {
	SHOW_FILEMANAGER = 0,
	SHOW_SPECTROGRAM,
	MAX_VIEW_OPTIONS
};

struct _app
{
	gboolean       loaded;

	char*          config_filename;
	const char*    cache_dir;
	struct _config config;
	char           search_phrase[256];
	char*          search_dir;
	gchar*         search_category;
	gboolean       add_recursive;
	gboolean       no_gui;
	struct _args {
		char*      search;
		char*      add;
	}              args;

	struct _view_option {
		char*            name;
		gboolean         value;
		GtkWidget*       menu_item;
		void             (*on_toggle)(GtkMenuItem*, gpointer);
	} view_options[MAX_VIEW_OPTIONS];

	GKeyFile*      key_file;   //config file data.

	GList*         backends;

	int            playing_id; //database index of the file that is currently playing, or zero if none playing.

	GtkListStore*  store;
	Inspector*     inspector;
	
	GtkWidget*     window;
	GtkWidget*     vbox;
	GtkWidget*     toolbar;
	GtkWidget*     toolbar2;
	GtkWidget*     scroll;
	GtkWidget*     hpaned;
	GtkWidget*     view;
	GtkWidget*     msg_panel;
	GtkWidget*     statusbar;
	GtkWidget*     statusbar2;
	GtkWidget*     search;
	GtkWidget*     category;
	GtkWidget*     view_category;
	GtkWidget*     context_menu;
	GtkWidget*     spectrogram;

	GtkWidget*     colour_button[PALETTE_SIZE];
	gboolean       colourbox_dirty;

	GtkCellRenderer*     cell1;          //sample name.
	GtkCellRenderer*     cell_tags;
	GtkTreeViewColumn*   col_name;
	GtkTreeViewColumn*   col_path;
	GtkTreeViewColumn*   col_pixbuf;
	GtkTreeViewColumn*   col_tags;

	GtkTreeRowReference* mouseover_row_ref;

	GNode*               dir_tree;
	GtkWidget*           dir_treeview;
	ViewDirTree*         dir_treeview2;
	GtkWidget*           vpaned;        //vertical divider on lhs between the dir_tree and inspector

	GtkWidget*           fm_view;

	GdkColor             fg_colour;
	GdkColor             bg_colour;
	GdkColor             bg_colour_mod1;
	GdkColor             base_colour;
	GdkColor             text_colour;

	GAsyncQueue*         msg_queue;

	//nasty!
	gint       mouse_x;
	gint       mouse_y;

	GMutex*    mutex;
};
#ifndef __main_c__
extern struct _app app;
#endif

struct _palette {
	guint red[8];
	guint grn[8];
	guint blu[8];
};

enum {
	TYPE_SNDFILE = 1,
	TYPE_FLAC,
};

gboolean    row_set_tags_from_id(int id, GtkTreeRowReference*, const char* tags_new);

void        do_search(char* search, char* dir);

gboolean    new_search(GtkWidget*, gpointer userdata);

void        scan_dir(const char* path, int* added_count);

gboolean    mimestring_is_unsupported(char*);
gboolean    mimetype_is_unsupported(MIME_type*, char* mime_string);

gboolean    add_file(char* path);
gboolean    add_dir(char* uri);
gboolean    on_overview_done(gpointer sample);
gboolean    on_peaklevel_done(gpointer sample);
void        delete_row(GtkMenuItem*, gpointer);

void        update_dir_node_list();

gint        get_mouseover_row();

void        update_search_dir(gchar* uri);

gboolean    keyword_is_dupe(char* new, char* existing);

gboolean    config_load();
void        config_new();
gboolean    config_save();
void        on_quit(GtkMenuItem*, gpointer user_data);

void        set_backend(BackendType);

void        observer__item_selected(Result*);


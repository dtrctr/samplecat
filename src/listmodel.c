
#include "config.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <gtk/gtk.h>
#ifdef USE_AYYI
#include <ayyi/ayyi.h>
#endif
#include "dh-link.h"
#include "file_manager/support.h"

#include "typedefs.h"
#include "src/types.h"
#include "mimetype.h"
#include "support.h"
#include "main.h"
#include "sample.h"
#include "dnd.h"
#include "pixmaps.h"
#include "listmodel.h"

extern struct _app app;


void
listmodel__update()
{
	do_search(NULL, NULL);
}


void
listmodel__add_result(SamplecatResult* result)
{
	g_return_if_fail(result);

	char samplerate_s[32]; float samplerate = result->sample_rate; samplerate_format(samplerate_s, samplerate);
	char* keywords = result->keywords ? result->keywords : "";
	char length[64]; format_time_int(length, result->length);

#if 0
//#ifdef USE_AYYI
	//is the file loaded in the current Ayyi song?
	if(ayyi.got_song){
		gchar* fullpath = g_build_filename(row[MYSQL_DIR], sample_name, NULL);
		if(pool__file_exists(fullpath)) dbg(0, "exists"); else dbg(0, "doesnt exist");
		g_free(fullpath);
	}
//#endif
#endif

	GdkPixbuf* get_iconbuf_from_mimetype(char* mimetype)
	{
		GdkPixbuf* iconbuf = NULL;
		MIME_type* mime_type = mime_type_lookup(mimetype);
		if(mime_type){
			type_to_icon(mime_type);
			if (!mime_type->image) dbg(0, "no icon.");
			iconbuf = mime_type->image->sm_pixbuf;
		}
		return iconbuf;
	}

	//icon (only shown if the sound file is currently available):
	GdkPixbuf* iconbuf = result->online ? get_iconbuf_from_mimetype(result->mimetype) : NULL;

	GtkTreeIter iter;
	gtk_list_store_append(app.store, &iter);
	gtk_list_store_set(app.store, &iter, COL_ICON, iconbuf,
	                   COL_NAME, result->sample_name,
	                   COL_FNAME, result->dir,
	                   COL_IDX, result->idx,
	                   COL_MIMETYPE, result->mimetype,
	                   COL_KEYWORDS, keywords, 
	                   COL_OVERVIEW, result->overview, COL_LENGTH, length, COL_SAMPLERATE, samplerate_s, COL_CHANNELS, result->channels, 
	                   COL_NOTES, result->notes, COL_COLOUR, result->colour,
#ifdef USE_AYYI
	                   COL_AYYI_ICON, ayyi_icon,
#endif
	                   -1);

	GtkTreePath* treepath;
	if((treepath = gtk_tree_model_get_path(GTK_TREE_MODEL(app.store), &iter))){
		GtkTreeRowReference* row_ref = gtk_tree_row_reference_new(GTK_TREE_MODEL(app.store), treepath);
		gtk_tree_path_free(treepath);
		result->row_ref = row_ref;
	}

	if(!result->overview){
		if(result->row_ref){
			if(!mimestring_is_unsupported(result->mimetype)){
				sample* sample = sample_new_from_result(result);
				dbg(2, "no overview: sending request: filename=%s", result->sample_name);

				g_async_queue_push(app.msg_queue, sample);
			}
		}
		else pwarn("cannot request overview without row_ref.");
	}
}


char*
listmodel__get_filename_from_id(int id)
{
	//result must be free'd.

	GtkTreeIter iter;
	gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app.store), &iter);
	int i;
	char* fname;
	char* path;
	int row = 0;
	do {
		gtk_tree_model_get(GTK_TREE_MODEL(app.store), &iter, COL_IDX, &i, COL_NAME, &fname, COL_FNAME, &path, -1);
		if(i == id){
			dbg(0, "found %s/%s", path, fname);
			return g_strdup_printf("%s/%s", path, fname);
		}
		row++;
	} while (gtk_tree_model_iter_next(GTK_TREE_MODEL(app.store), &iter));

	gwarn("not found. %i", id);
	return NULL;
}

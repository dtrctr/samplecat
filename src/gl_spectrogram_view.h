/* gl_spectrogram_view.h generated by valac, the Vala compiler, do not modify */


#ifndef __GL_SPECTROGRAM_VIEW_H__
#define __GL_SPECTROGRAM_VIEW_H__

#include <glib.h>
#include <gdk-pixbuf/gdk-pixdata.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS


#define TYPE_GL_SPECTROGRAM (gl_spectrogram_get_type ())
#define GL_SPECTROGRAM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GL_SPECTROGRAM, GlSpectrogram))
#define GL_SPECTROGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GL_SPECTROGRAM, GlSpectrogramClass))
#define IS_GL_SPECTROGRAM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GL_SPECTROGRAM))
#define IS_GL_SPECTROGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GL_SPECTROGRAM))
#define GL_SPECTROGRAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GL_SPECTROGRAM, GlSpectrogramClass))

typedef struct _GlSpectrogram GlSpectrogram;
typedef struct _GlSpectrogramClass GlSpectrogramClass;
typedef struct _GlSpectrogramPrivate GlSpectrogramPrivate;

typedef void (*SpectrogramReady) (gchar* filename, GdkPixbuf* a, void* user_data_, void* user_data);
struct _GlSpectrogram {
	GtkDrawingArea parent_instance;
	GlSpectrogramPrivate * priv;
};

struct _GlSpectrogramClass {
	GtkDrawingAreaClass parent_class;
};


void get_spectrogram_with_target (gchar* path, SpectrogramReady on_ready, void* on_ready_target, void* user_data);
GType gl_spectrogram_get_type (void);
extern GlSpectrogram* gl_spectrogram_instance;
GlSpectrogram* gl_spectrogram_new (void);
GlSpectrogram* gl_spectrogram_construct (GType object_type);
void gl_spectrogram_set_file (GlSpectrogram* self, gchar* filename);


G_END_DECLS

#endif

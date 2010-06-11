/* gl_spectrogram_view.c generated by valac, the Vala compiler
 * generated from gl_spectrogram_view.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gdk-pixbuf/gdk-pixdata.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <gdk/gdk.h>
#include <gtkglext-1.0/gdk/gdkgl.h>
#include <gtkglext-1.0/gtk/gtkgl.h>
#include <GL/glu.h>
#include <stdio.h>


#define TYPE_GL_SPECTROGRAM (gl_spectrogram_get_type ())
#define GL_SPECTROGRAM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GL_SPECTROGRAM, GlSpectrogram))
#define GL_SPECTROGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GL_SPECTROGRAM, GlSpectrogramClass))
#define IS_GL_SPECTROGRAM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GL_SPECTROGRAM))
#define IS_GL_SPECTROGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GL_SPECTROGRAM))
#define GL_SPECTROGRAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GL_SPECTROGRAM, GlSpectrogramClass))

typedef struct _GlSpectrogram GlSpectrogram;
typedef struct _GlSpectrogramClass GlSpectrogramClass;
typedef struct _GlSpectrogramPrivate GlSpectrogramPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

typedef void (*PrintIntFunc) (GdkPixbuf* a, void* user_data_, void* user_data);
struct _GlSpectrogram {
	GtkDrawingArea parent_instance;
	GlSpectrogramPrivate * priv;
};

struct _GlSpectrogramClass {
	GtkDrawingAreaClass parent_class;
};

struct _GlSpectrogramPrivate {
	char* _filename;
	GdkPixbuf* pixbuf;
	gboolean gl_init_done;
	GLuint Textures[2];
};


static gpointer gl_spectrogram_parent_class = NULL;

GType gl_spectrogram_get_type (void);
void render_spectrogram (gchar* path, GlSpectrogram* w, PrintIntFunc callback, void* callback_target, void* user_data);
void get_spectrogram (gchar* path, GlSpectrogram* w, PrintIntFunc callback, void* callback_target);
#define GL_SPECTROGRAM_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_GL_SPECTROGRAM, GlSpectrogramPrivate))
enum  {
	GL_SPECTROGRAM_DUMMY_PROPERTY
};
GlSpectrogram* gl_spectrogram_new (void);
GlSpectrogram* gl_spectrogram_construct (GType object_type);
static void gl_spectrogram_load_texture (GlSpectrogram* self);
static gboolean gl_spectrogram_real_configure_event (GtkWidget* base, GdkEventConfigure* event);
static gboolean gl_spectrogram_real_expose_event (GtkWidget* base, GdkEventExpose* event);
static gboolean gl_spectrogram_real_button_press_event (GtkWidget* base, GdkEventButton* event);
static gboolean gl_spectrogram_real_button_release_event (GtkWidget* base, GdkEventButton* event);
static gboolean gl_spectrogram_real_motion_notify_event (GtkWidget* base, GdkEventMotion* event);
void gl_spectrogram_image_ready (GlSpectrogram* self, GdkPixbuf* _pixbuf);
static void _gl_spectrogram_image_ready_print_int_func (GdkPixbuf* a, void* user_data_, gpointer self);
void gl_spectrogram_set_file (GlSpectrogram* self, gchar* filename);
static void gl_spectrogram_finalize (GObject* obj);



GlSpectrogram* gl_spectrogram_construct (GType object_type) {
	GlSpectrogram * self;
	GdkGLConfig* glconfig;
	self = g_object_newv (object_type, 0, NULL);
	gtk_widget_add_events ((GtkWidget*) self, (gint) ((GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK) | GDK_POINTER_MOTION_MASK));
	gtk_widget_set_size_request ((GtkWidget*) self, 200, 100);
	glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB | GDK_GL_MODE_DOUBLE);
	gtk_widget_set_gl_capability ((GtkWidget*) self, glconfig, NULL, TRUE, (gint) GDK_GL_RGBA_TYPE);
	_g_object_unref0 (glconfig);
	return self;
}


GlSpectrogram* gl_spectrogram_new (void) {
	return gl_spectrogram_construct (TYPE_GL_SPECTROGRAM);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void gl_spectrogram_load_texture (GlSpectrogram* self) {
	GdkGLContext* glcontext;
	GdkGLDrawable* gldrawable;
	GdkPixbuf* scaled;
	GLint n_colour_components;
	GLenum _tmp0_ = 0U;
	GLenum format;
	g_return_if_fail (self != NULL);
	glcontext = _g_object_ref0 (gtk_widget_get_gl_context ((GtkWidget*) self));
	gldrawable = _g_object_ref0 (gtk_widget_get_gl_drawable ((GtkWidget*) self));
	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext)) {
		_g_object_unref0 (glcontext);
		_g_object_unref0 (gldrawable);
		return;
	}
	glBindTexture (GL_TEXTURE_2D, self->priv->Textures[0]);
	scaled = gdk_pixbuf_scale_simple (self->priv->pixbuf, 256, 256, GDK_INTERP_BILINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat) GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) GL_LINEAR);
	n_colour_components = (GLint) gdk_pixbuf_get_n_channels (scaled);
	if (gdk_pixbuf_get_n_channels (scaled) == 4) {
		_tmp0_ = GL_RGBA;
	} else {
		_tmp0_ = GL_RGB;
	}
	format = _tmp0_;
	if (((gboolean) gluBuild2DMipmaps (GL_TEXTURE_2D, n_colour_components, (GLsizei) gdk_pixbuf_get_width (scaled), (GLsizei) gdk_pixbuf_get_height (scaled), format, GL_UNSIGNED_BYTE, gdk_pixbuf_get_pixels (scaled)))) {
		fprintf (stdout, "mipmap generation failed!\n");
	}
	g_object_unref ((GObject*) scaled);
	gdk_gl_drawable_gl_end (gldrawable);
	_g_object_unref0 (glcontext);
	_g_object_unref0 (gldrawable);
}


static gboolean gl_spectrogram_real_configure_event (GtkWidget* base, GdkEventConfigure* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	GdkGLContext* glcontext;
	GdkGLDrawable* gldrawable;
	self = (GlSpectrogram*) base;
	glcontext = _g_object_ref0 (gtk_widget_get_gl_context ((GtkWidget*) self));
	gldrawable = _g_object_ref0 (gtk_widget_get_gl_drawable ((GtkWidget*) self));
	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext)) {
		result = FALSE;
		_g_object_unref0 (glcontext);
		_g_object_unref0 (gldrawable);
		return result;
	}
	glViewport ((GLint) 0, (GLint) 0, (GLsizei) ((GtkWidget*) self)->allocation.width, (GLsizei) ((GtkWidget*) self)->allocation.height);
	if (!self->priv->gl_init_done) {
		//fprintf (stdout, "GlSpectrogram: texture init...\n");
		glGenTextures ((GLsizei) 1, self->priv->Textures);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, self->priv->Textures[0]);
		self->priv->gl_init_done = TRUE;
	}
	gdk_gl_drawable_gl_end (gldrawable);
	result = TRUE;
	_g_object_unref0 (glcontext);
	_g_object_unref0 (gldrawable);
	return result;
}


static gboolean gl_spectrogram_real_expose_event (GtkWidget* base, GdkEventExpose* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	GdkGLContext* glcontext;
	GdkGLDrawable* gldrawable;
	gint x;
	gint top;
	gint botm;
	self = (GlSpectrogram*) base;
	glcontext = _g_object_ref0 (gtk_widget_get_gl_context ((GtkWidget*) self));
	gldrawable = _g_object_ref0 (gtk_widget_get_gl_drawable ((GtkWidget*) self));
	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext)) {
		result = FALSE;
		_g_object_unref0 (glcontext);
		_g_object_unref0 (gldrawable);
		return result;
	}
	glClearColor ((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 1.0f);
	glClear ((GLbitfield) GL_COLOR_BUFFER_BIT);
	x = -1;
	top = 1;
	botm = -1;
	glBegin (GL_QUADS);
	glTexCoord2d ((GLdouble) 0.0, (GLdouble) 0.0);
	glVertex2d ((GLdouble) (x + 0.0), (GLdouble) top);
	glTexCoord2d ((GLdouble) 1.0, (GLdouble) 0.0);
	glVertex2d ((GLdouble) (x + 2.0), (GLdouble) top);
	glTexCoord2d ((GLdouble) 1.0, (GLdouble) 1.0);
	glVertex2d ((GLdouble) (x + 2.0), (GLdouble) botm);
	glTexCoord2d ((GLdouble) 0.0, (GLdouble) 1.0);
	glVertex2d ((GLdouble) (x + 0.0), (GLdouble) botm);
	glEnd ();
	if (gdk_gl_drawable_is_double_buffered (gldrawable)) {
		gdk_gl_drawable_swap_buffers (gldrawable);
	} else {
		glFlush ();
	}
	gdk_gl_drawable_gl_end (gldrawable);
	result = TRUE;
	_g_object_unref0 (glcontext);
	_g_object_unref0 (gldrawable);
	return result;
}


static gboolean gl_spectrogram_real_button_press_event (GtkWidget* base, GdkEventButton* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	self = (GlSpectrogram*) base;
	result = FALSE;
	return result;
}


static gboolean gl_spectrogram_real_button_release_event (GtkWidget* base, GdkEventButton* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	self = (GlSpectrogram*) base;
	result = FALSE;
	return result;
}


static gboolean gl_spectrogram_real_motion_notify_event (GtkWidget* base, GdkEventMotion* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	self = (GlSpectrogram*) base;
	result = FALSE;
	return result;
}


void gl_spectrogram_image_ready (GlSpectrogram* self, GdkPixbuf* _pixbuf) {
	g_return_if_fail (self != NULL);
	if (_pixbuf != NULL) {
		//fprintf (stdout, "image_ready\n");
		if (self->priv->pixbuf != NULL) {
			g_object_unref ((GObject*) self->priv->pixbuf);
		}
		self->priv->pixbuf = _pixbuf;
		gl_spectrogram_load_texture (self);
		gtk_widget_queue_draw ((GtkWidget*) self);
	}
}


static void _gl_spectrogram_image_ready_print_int_func (GdkPixbuf* a, void* user_data_, gpointer self) {
	gl_spectrogram_image_ready (self, a);
}


void gl_spectrogram_set_file (GlSpectrogram* self, gchar* filename) {
	//printf("gl_spectrogram_set_file...\n");
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	self->priv->_filename = (_tmp0_ = g_strdup ((const char*) filename), _g_free0 (self->priv->_filename), _tmp0_);
	get_spectrogram (filename, self, _gl_spectrogram_image_ready_print_int_func, self);
}


static void gl_spectrogram_class_init (GlSpectrogramClass * klass) {
	gl_spectrogram_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GlSpectrogramPrivate));
	GTK_WIDGET_CLASS (klass)->configure_event = gl_spectrogram_real_configure_event;
	GTK_WIDGET_CLASS (klass)->expose_event = gl_spectrogram_real_expose_event;
	GTK_WIDGET_CLASS (klass)->button_press_event = gl_spectrogram_real_button_press_event;
	GTK_WIDGET_CLASS (klass)->button_release_event = gl_spectrogram_real_button_release_event;
	GTK_WIDGET_CLASS (klass)->motion_notify_event = gl_spectrogram_real_motion_notify_event;
	G_OBJECT_CLASS (klass)->finalize = gl_spectrogram_finalize;
}


static void gl_spectrogram_instance_init (GlSpectrogram * self) {
	self->priv = GL_SPECTROGRAM_GET_PRIVATE (self);
	self->priv->pixbuf = NULL;
	self->priv->gl_init_done = FALSE;
}


static void gl_spectrogram_finalize (GObject* obj) {
	GlSpectrogram * self;
	self = GL_SPECTROGRAM (obj);
	_g_free0 (self->priv->_filename);
	G_OBJECT_CLASS (gl_spectrogram_parent_class)->finalize (obj);
}


GType gl_spectrogram_get_type (void) {
	static volatile gsize gl_spectrogram_type_id__volatile = 0;
	if (g_once_init_enter (&gl_spectrogram_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GlSpectrogramClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gl_spectrogram_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GlSpectrogram), 0, (GInstanceInitFunc) gl_spectrogram_instance_init, NULL };
		GType gl_spectrogram_type_id;
		gl_spectrogram_type_id = g_type_register_static (GTK_TYPE_DRAWING_AREA, "GlSpectrogram", &g_define_type_info, 0);
		g_once_init_leave (&gl_spectrogram_type_id__volatile, gl_spectrogram_type_id);
	}
	return gl_spectrogram_type_id__volatile;
}





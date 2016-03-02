/* model.h generated by valac 0.20.1, the Vala compiler, do not modify */


#ifndef __MODEL_H__
#define __MODEL_H__

#include <glib.h>
#include <glib-object.h>
#include <samplecat/sample.h>
#include <samplecat/db/db.h>

G_BEGIN_DECLS


#define SAMPLECAT_TYPE_FILTER (samplecat_filter_get_type ())
#define SAMPLECAT_FILTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SAMPLECAT_TYPE_FILTER, SamplecatFilter))
#define SAMPLECAT_FILTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SAMPLECAT_TYPE_FILTER, SamplecatFilterClass))
#define SAMPLECAT_IS_FILTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SAMPLECAT_TYPE_FILTER))
#define SAMPLECAT_IS_FILTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SAMPLECAT_TYPE_FILTER))
#define SAMPLECAT_FILTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SAMPLECAT_TYPE_FILTER, SamplecatFilterClass))

typedef struct _SamplecatFilter SamplecatFilter;
typedef struct _SamplecatFilterClass SamplecatFilterClass;
typedef struct _SamplecatFilterPrivate SamplecatFilterPrivate;

#define SAMPLECAT_TYPE_FILTERS (samplecat_filters_get_type ())
typedef struct _SamplecatFilters SamplecatFilters;

#define SAMPLECAT_TYPE_IDLE (samplecat_idle_get_type ())
#define SAMPLECAT_IDLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SAMPLECAT_TYPE_IDLE, SamplecatIdle))
#define SAMPLECAT_IDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SAMPLECAT_TYPE_IDLE, SamplecatIdleClass))
#define SAMPLECAT_IS_IDLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SAMPLECAT_TYPE_IDLE))
#define SAMPLECAT_IS_IDLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SAMPLECAT_TYPE_IDLE))
#define SAMPLECAT_IDLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SAMPLECAT_TYPE_IDLE, SamplecatIdleClass))

typedef struct _SamplecatIdle SamplecatIdle;
typedef struct _SamplecatIdleClass SamplecatIdleClass;
typedef struct _SamplecatIdlePrivate SamplecatIdlePrivate;

#define SAMPLECAT_TYPE_MODEL (samplecat_model_get_type ())
#define SAMPLECAT_MODEL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SAMPLECAT_TYPE_MODEL, SamplecatModel))
#define SAMPLECAT_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SAMPLECAT_TYPE_MODEL, SamplecatModelClass))
#define SAMPLECAT_IS_MODEL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SAMPLECAT_TYPE_MODEL))
#define SAMPLECAT_IS_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SAMPLECAT_TYPE_MODEL))
#define SAMPLECAT_MODEL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SAMPLECAT_TYPE_MODEL, SamplecatModelClass))

typedef struct _SamplecatModel SamplecatModel;
typedef struct _SamplecatModelClass SamplecatModelClass;
typedef struct _SamplecatModelPrivate SamplecatModelPrivate;

struct _SamplecatFilter {
	GTypeInstance parent_instance;
	volatile int ref_count;
	SamplecatFilterPrivate * priv;
	gchar* name;
	gchar* value;
};

struct _SamplecatFilterClass {
	GTypeClass parent_class;
	void (*finalize) (SamplecatFilter *self);
};

struct _SamplecatFilters {
	SamplecatFilter* search;
	SamplecatFilter* dir;
	SamplecatFilter* category;
};

struct _SamplecatIdle {
	GTypeInstance parent_instance;
	volatile int ref_count;
	SamplecatIdlePrivate * priv;
};

struct _SamplecatIdleClass {
	GTypeClass parent_class;
	void (*finalize) (SamplecatIdle *self);
};

struct _SamplecatModel {
	GObject parent_instance;
	SamplecatModelPrivate * priv;
	gint state;
	gchar* cache_dir;
	GList* backends;
	SamplecatBackend backend;
	SamplecatFilters filters;
	GList* filters_;
	Sample* selection;
	GList* modified;
};

struct _SamplecatModelClass {
	GObjectClass parent_class;
};


gpointer samplecat_filter_ref (gpointer instance);
void samplecat_filter_unref (gpointer instance);
GParamSpec* samplecat_param_spec_filter (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void samplecat_value_set_filter (GValue* value, gpointer v_object);
void samplecat_value_take_filter (GValue* value, gpointer v_object);
gpointer samplecat_value_get_filter (const GValue* value);
GType samplecat_filter_get_type (void) G_GNUC_CONST;
SamplecatFilter* samplecat_filter_new (gchar* _name);
SamplecatFilter* samplecat_filter_construct (GType object_type, gchar* _name);
void samplecat_filter_set_value (SamplecatFilter* self, gchar* val);
GType samplecat_filters_get_type (void) G_GNUC_CONST;
SamplecatFilters* samplecat_filters_dup (const SamplecatFilters* self);
void samplecat_filters_free (SamplecatFilters* self);
gpointer samplecat_idle_ref (gpointer instance);
void samplecat_idle_unref (gpointer instance);
GParamSpec* samplecat_param_spec_idle (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void samplecat_value_set_idle (GValue* value, gpointer v_object);
void samplecat_value_take_idle (GValue* value, gpointer v_object);
gpointer samplecat_value_get_idle (const GValue* value);
GType samplecat_idle_get_type (void) G_GNUC_CONST;
SamplecatIdle* samplecat_idle_new (GSourceFunc _fn, void* _fn_target);
SamplecatIdle* samplecat_idle_construct (GType object_type, GSourceFunc _fn, void* _fn_target);
void samplecat_idle_queue (SamplecatIdle* self);
GType samplecat_model_get_type (void) G_GNUC_CONST;
SamplecatModel* samplecat_model_new (void);
SamplecatModel* samplecat_model_construct (GType object_type);
gboolean samplecat_model_add (SamplecatModel* self);
gboolean samplecat_model_remove (SamplecatModel* self, gint id);
void samplecat_model_set_search_dir (SamplecatModel* self, gchar* dir);
void samplecat_model_set_selection (SamplecatModel* self, Sample* sample);
void samplecat_model_add_filter (SamplecatModel* self, SamplecatFilter* filter);
void samplecat_model_refresh_sample (SamplecatModel* self, Sample* sample, gboolean force_update);
gboolean samplecat_model_update_sample (SamplecatModel* self, Sample* sample, gint prop, void* val);
gchar* samplecat_model_print_col_name (guint prop_type);
void samplecat_model_move_files (GList*, const gchar* dest_path);


G_END_DECLS

#endif
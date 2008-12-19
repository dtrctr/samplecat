#ifndef __AYYI_TYPES_H__
#define __AYYI_TYPES_H__
typedef struct _container          AyyiContainer;
typedef struct _ayyi_list          AyyiList;
typedef struct _midi_region_shared midi_region_shared;

typedef enum {
	AYYI_AUDIO = 1,
	AYYI_MIDI
} MediaType;

//op types
typedef enum {
	AYYI_NEW = 1,
	AYYI_DEL,
	AYYI_GET,
	AYYI_SET,
	AYYI_UNDO
} AyyiOp;

enum {
    AYYI_OBJECT_EMPTY = 0,
    AYYI_OBJECT_TRACK,
    AYYI_OBJECT_AUDIO_TRACK,
    AYYI_OBJECT_MIDI_TRACK,
    AYYI_OBJECT_CHAN,
    AYYI_OBJECT_AUX,
    AYYI_OBJECT_PART,
    AYYI_OBJECT_AUDIO_PART,
    AYYI_OBJECT_MIDI_PART,
    AYYI_OBJECT_EVENT,
    AYYI_OBJECT_RAW,
    AYYI_OBJECT_STRING,
    AYYI_OBJECT_ROUTE,
    AYYI_OBJECT_FILE,
    AYYI_OBJECT_LIST,
    AYYI_OBJECT_MIDI_NOTE,
    AYYI_OBJECT_SONG,
    AYYI_OBJECT_TRANSPORT,
    AYYI_OBJECT_AUTO,
    AYYI_OBJECT_UNSUPPORTED,
    AYYI_OBJECT_ALL
};

//properties
enum {
	AYYI_NO_PROP,
	AYYI_NAME,
	AYYI_STIME,
	AYYI_LENGTH,
	AYYI_HEIGHT,
	AYYI_END,
	AYYI_TRACK,
	AYYI_MUTE,
	AYYI_ARM,
	AYYI_SOLO,
	AYYI_SDEF,
	AYYI_INSET,
	AYYI_FADEIN,
	AYYI_FADEOUT,
	AYYI_OUTPUT,
	AYYI_AUX1_OUTPUT,
	AYYI_AUX2_OUTPUT,
	AYYI_AUX3_OUTPUT,
	AYYI_AUX4_OUTPUT,
	AYYI_PREPOST,
	AYYI_SPLIT,

	AYYI_PB_LEVEL,
	AYYI_PB_PAN,
	AYYI_PB_DELAY_MU,
	AYYI_PLUGIN_SEL,
	AYYI_PLUGIN_BYPASS,

	AYYI_CHAN_LEVEL,
	AYYI_CHAN_PAN,

	AYYI_TRANSPORT_PLAY,
	AYYI_TRANSPORT_STOP,
	AYYI_TRANSPORT_REW,
	AYYI_TRANSPORT_FF,
	AYYI_TRANSPORT_REC,
	AYYI_TRANSPORT_LOCATE,
	AYYI_TRANSPORT_CYCLE,
	AYYI_TRANSPORT_LOCATOR,

	AYYI_AUTO_PT, // not really a property. We specify the complete point. Perhaps remove?

	AYYI_ADD_POINT,
	AYYI_DEL_POINT,

	AYYI_TEMPO,
	AYYI_HISTORY,

	AYYI_LOAD_SONG,
	AYYI_SAVE,
	AYYI_NEW_SONG
};


struct _song_pos
{
	int beat;
	unsigned short sub;
	unsigned short mu;
};


enum {
    VOL = 0,
    PAN,
	AUTO_MAX
};

enum // channel/track/aux flags
{
    muted  = 1 << 0,
    solod  = 1 << 1,
    armed  = 1 << 2,
    master = 1 << 3,
} ChanFlags;

#endif
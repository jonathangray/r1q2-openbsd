#include "../qcommon/qcommon.h"

#ifdef USE_OPENAL
#include <AL/al.h>
#include <AL/alc.h>

#ifndef _WIN32
#include <AL/alext.h>
#endif

#include "client.h"

#include "eax.h"

#include "qal.h"

#ifdef _WIN32
#include "../win32/alw_win.h"
#else
#include "../linux/al_linux.h"
#endif

typedef struct
{
	int 		length;
	int 		loopstart;
	int 		speed;			// not needed, because converted on load?
	int 		width;
	int 		stereo;
	byte		data[1];		// variable sized
} sfxcache_t;

typedef struct sfx_s
{
	char 		name[MAX_QPATH];
	int			registration_sequence;
	sfxcache_t	*cache;
	char 		*truename;

#ifdef USE_OPENAL
	qboolean			loaded;
	int					samples;
	int					rate;
	unsigned			format;
	unsigned			bufferNum;
#endif
} sfx_t;

#ifdef USE_OPENAL

typedef struct
{
	int					rate;
	int					width;
	int					channels;
	int					samples;
} wavInfo_t;

typedef struct openal_sfx_s
{
	char				name[MAX_QPATH];
	qboolean			defaulted;
	qboolean			loaded;

	int					samples;
	int					rate;
	unsigned			format;
	unsigned			bufferNum;

	struct openal_sfx_s		*nextHash;
} openal_sfx_t;

/*typedef struct {
	char				introName[MAX_QPATH];
	char				loopName[MAX_QPATH];
	qboolean			looping;
	fileHandle_t		file;
	int					start;
	int					rate;
	unsigned			format;
	void				*vorbisFile;
} bgTrack_t;*/

// A playSound will be generated by each call to S_StartSound.
// When the mixer reaches playSound->beginTime, the playSound will be
// assigned to a channel.
/*typedef struct openal_playSound_s
{
	struct openal_playSound_s	*prev, *next;
	openal_sfx_t		*asfx;
	int					entNum;
	int					entChannel;
	qboolean			fixedPosition;	// Use position instead of fetching entity's origin
	vec3_t				position;		// Only use if fixedPosition is set
	float				volume;
	float				attenuation;
	int					beginTime;		// Begin at this time
} openal_playSound_t;*/

typedef struct
{
	qboolean			streaming;
	sfx_t				*sfx;			// NULL if unused
	//openal_sfx_t		*asfx;			// NULL if unused
	int					entNum;			// To allow overriding a specific sound
	int					entChannel;
	int					startTime;		// For overriding oldest sounds
	qboolean			loopSound;		// Looping sound
	int					loopNum;		// Looping entity number
	int					loopFrame;		// For stopping looping sounds
	qboolean			fixedPosition;	// Use position instead of fetching entity's origin
	vec3_t				position;		// Only use if fixedPosition is set
	float				volume;
	float				distanceMult;
	unsigned			sourceNum;		// OpenAL source
} openal_channel_t;

typedef struct
{
	vec3_t				position;
	vec3_t				velocity;
	float				orientation[6];
} openal_listener_t;

extern qboolean			openal_active;

extern cvar_t	*snd_openal_extensions;
extern cvar_t	*snd_openal_eax;

/*
 =======================================================================

 IMPLEMENTATION SPECIFIC FUNCTIONS

 =======================================================================
*/

typedef struct
{
	const char			*vendorString;
	const char			*rendererString;
	const char			*versionString;
	const char			*extensionsString;

	const char			*deviceList;
	const char			*deviceName;

	qboolean			eax;
	unsigned			eaxState;
} alConfig_t;

extern alConfig_t		alConfig;

#ifdef _WIN32

#define AL_DRIVER_OPENAL	"OpenAL32"

#define ALimp_Init						ALW_Init
#define ALimp_Shutdown					ALW_Shutdown

#else

#define AL_DRIVER_OPENAL	"libopenal.so"

#define ALimp_Init						AL_Init
#define ALimp_Shutdown					AL_Shutdown

#endif
#endif
#endif

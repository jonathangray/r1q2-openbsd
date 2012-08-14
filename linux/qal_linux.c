/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/


// qal_win.c -- binding of AL to QAL function pointers

#ifdef USE_OPENAL

#include <dlfcn.h> // ELF dl loader
#include "../client/snd_loc.h"

qboolean	openal_active;

LPALCOPENDEVICE				qalcOpenDevice;
LPALCCLOSEDEVICE				qalcCloseDevice;
LPALCCREATECONTEXT			qalcCreateContext;
LPALCDESTROYCONTEXT			qalcDestroyContext;
LPALCMAKECONTEXTCURRENT		qalcMakeContextCurrent;
LPALCPROCESSCONTEXT			qalcProcessContext;
LPALCSUSPENDCONTEXT			qalcSuspendContext;
LPALCGETCURRENTCONTEXT		qalcGetCurrentContext;
LPALCGETCONTEXTSDEVICE		qalcGetContextsDevice;
LPALCGETSTRING				qalcGetString;
LPALCGETINTEGERV				qalcGetIntegerv;
LPALCGETERROR					qalcGetError;
LPALCISEXTENSIONPRESENT		qalcIsExtensionPresent;
LPALCGETPROCADDRESS			qalcGetProcAddress;
LPALCGETENUMVALUE				qalcGetEnumValue;

LPALBUFFERDATA				qalBufferData;
LPALDELETEBUFFERS				qalDeleteBuffers;
LPALDELETESOURCES				qalDeleteSources;
LPALDISABLE					qalDisable;
LPALDISTANCEMODEL				qalDistanceModel;
LPALDOPPLERFACTOR				qalDopplerFactor;
LPALDOPPLERVELOCITY			qalDopplerVelocity;
LPALENABLE					qalEnable;
LPALGENBUFFERS				qalGenBuffers;
LPALGENSOURCES				qalGenSources;
LPALGETBOOLEAN				qalGetBoolean;
LPALGETBOOLEANV				qalGetBooleanv;
LPALGETBUFFERF				qalGetBufferf;
LPALGETBUFFERI				qalGetBufferi;
LPALGETDOUBLE					qalGetDouble;
LPALGETDOUBLEV				qalGetDoublev;
LPALGETENUMVALUE				qalGetEnumValue;
LPALGETERROR					qalGetError;
LPALGETFLOAT					qalGetFloat;
LPALGETFLOATV					qalGetFloatv;
LPALGETINTEGER				qalGetInteger;
LPALGETINTEGERV				qalGetIntegerv;
LPALGETLISTENER3F				qalGetListener3f;
LPALGETLISTENERF				qalGetListenerf;
LPALGETLISTENERFV				qalGetListenerfv;
LPALGETLISTENERI				qalGetListeneri;
LPALGETPROCADDRESS			qalGetProcAddress;
LPALGETSOURCE3F				qalGetSource3f;
LPALGETSOURCEF				qalGetSourcef;
LPALGETSOURCEFV				qalGetSourcefv;
LPALGETSOURCEI				qalGetSourcei;
LPALGETSTRING					qalGetString;
LPALISBUFFER					qalIsBuffer;
LPALISENABLED					qalIsEnabled;
LPALISEXTENSIONPRESENT		qalIsExtensionPresent;
LPALISSOURCE					qalIsSource;
LPALLISTENER3F				qalListener3f;
LPALLISTENERF					qalListenerf;
LPALLISTENERFV				qalListenerfv;
LPALLISTENERI					qalListeneri;
LPALSOURCE3F					qalSource3f;
LPALSOURCEF					qalSourcef;
LPALSOURCEFV					qalSourcefv;
LPALSOURCEI					qalSourcei;
LPALSOURCEPAUSE				qalSourcePause;
LPALSOURCEPAUSEV				qalSourcePausev;
LPALSOURCEPLAY				qalSourcePlay;
LPALSOURCEPLAYV				qalSourcePlayv;
LPALSOURCEQUEUEBUFFERS		qalSourceQueueBuffers;
LPALSOURCEREWIND				qalSourceRewind;
LPALSOURCEREWINDV				qalSourceRewindv;
LPALSOURCESTOP				qalSourceStop;
LPALSOURCESTOPV				qalSourceStopv;
LPALSOURCEUNQUEUEBUFFERS		qalSourceUnqueueBuffers;

// =====================================================================

#define GPA(a)			dlsym(alState.ALlib, a);


/*
 =================
 QAL_Shutdown

 Unloads the specified DLL then nulls out all the proc pointers
 =================
*/
void QAL_Shutdown (void){

	Com_Printf("...shutting down QAL\n", LOG_CLIENT);

	if (alState.ALlib)
	{
		Com_Printf("...unloading OpenAL DLL\n", LOG_CLIENT);

		dlclose(alState.ALlib);
		alState.ALlib = NULL;
	}

	openal_active = false;

	qalcOpenDevice				= NULL;
	qalcCloseDevice				= NULL;
	qalcCreateContext			= NULL;
	qalcDestroyContext			= NULL;
	qalcMakeContextCurrent		= NULL;
	qalcProcessContext			= NULL;
	qalcSuspendContext			= NULL;
	qalcGetCurrentContext		= NULL;
	qalcGetContextsDevice		= NULL;
	qalcGetString				= NULL;
	qalcGetIntegerv				= NULL;
	qalcGetError				= NULL;
	qalcIsExtensionPresent		= NULL;
	qalcGetProcAddress			= NULL;
	qalcGetEnumValue			= NULL;

	qalBufferData				= NULL;
	qalDeleteBuffers			= NULL;
	qalDeleteSources			= NULL;
	qalDisable					= NULL;
	qalDistanceModel			= NULL;
	qalDopplerFactor			= NULL;
	qalDopplerVelocity			= NULL;
	qalEnable					= NULL;
	qalGenBuffers				= NULL;
	qalGenSources				= NULL;
	qalGetBoolean				= NULL;
	qalGetBooleanv				= NULL;
	qalGetBufferf				= NULL;
	qalGetBufferi				= NULL;
	qalGetDouble				= NULL;
	qalGetDoublev				= NULL;
	qalGetEnumValue				= NULL;
	qalGetError					= NULL;
	qalGetFloat					= NULL;
	qalGetFloatv				= NULL;
	qalGetInteger				= NULL;
	qalGetIntegerv				= NULL;
	qalGetListener3f			= NULL;
	qalGetListenerf				= NULL;
	qalGetListenerfv			= NULL;
	qalGetListeneri				= NULL;
	qalGetProcAddress			= NULL;
	qalGetSource3f				= NULL;
	qalGetSourcef				= NULL;
	qalGetSourcefv				= NULL;
	qalGetSourcei				= NULL;
	qalGetString				= NULL;
	qalIsBuffer					= NULL;
	qalIsEnabled				= NULL;
	qalIsExtensionPresent		= NULL;
	qalIsSource					= NULL;
	qalListener3f				= NULL;
	qalListenerf				= NULL;
	qalListenerfv				= NULL;
	qalListeneri				= NULL;
	qalSource3f					= NULL;
	qalSourcef					= NULL;
	qalSourcefv					= NULL;
	qalSourcei					= NULL;
	qalSourcePause				= NULL;
	qalSourcePausev				= NULL;
	qalSourcePlay				= NULL;
	qalSourcePlayv				= NULL;
	qalSourceQueueBuffers		= NULL;
	qalSourceRewind				= NULL;
	qalSourceRewindv			= NULL;
	qalSourceStop				= NULL;
	qalSourceStopv				= NULL;
	qalSourceUnqueueBuffers		= NULL;
}

/*
 =================
 QAL_Init

 Binds our QAL function pointers to the appropriate AL stuff
 =================
*/
qboolean QAL_Init (const char *driver){

	Com_Printf("...initializing QAL\n", LOG_CLIENT);

	Com_Printf("...calling dlopen( '%s' ): ", LOG_CLIENT, driver);

	if ((alState.ALlib = dlopen(driver, RTLD_NOW)) == NULL)
	{
		Com_Printf("failed\n", LOG_CLIENT);
		return false;
	}
	Com_Printf("succeeded\n", LOG_CLIENT);

	qalcOpenDevice				= (LPALCOPENDEVICE)GPA("alcOpenDevice");
	qalcCloseDevice				= (LPALCCLOSEDEVICE)GPA("alcCloseDevice");
	qalcCreateContext			= (LPALCCREATECONTEXT)GPA("alcCreateContext");
	qalcDestroyContext			= (LPALCDESTROYCONTEXT)GPA("alcDestroyContext");
	qalcMakeContextCurrent		= (LPALCMAKECONTEXTCURRENT)GPA("alcMakeContextCurrent");
	qalcProcessContext			= (LPALCPROCESSCONTEXT)GPA("alcProcessContext");
	qalcSuspendContext			= (LPALCSUSPENDCONTEXT)GPA("alcSuspendContext");
	qalcGetCurrentContext		= (LPALCGETCURRENTCONTEXT)GPA("alcGetCurrentContext");
	qalcGetContextsDevice		= (LPALCGETCONTEXTSDEVICE)GPA("alcGetContextsDevice");
	qalcGetString				= (LPALCGETSTRING)GPA("alcGetString");
	qalcGetIntegerv				= (LPALCGETINTEGERV)GPA("alcGetIntegerv");
	qalcGetError				= (LPALCGETERROR)GPA("alcGetError");
	qalcIsExtensionPresent		= (LPALCISEXTENSIONPRESENT)GPA("alcIsExtensionPresent");
	qalcGetProcAddress			= (LPALCGETPROCADDRESS)GPA("alcGetProcAddress");
	qalcGetEnumValue			= (LPALCGETENUMVALUE)GPA("alcGetEnumValue");

	qalBufferData				= (LPALBUFFERDATA)GPA("alBufferData");
	qalDeleteBuffers			= (LPALDELETEBUFFERS)GPA("alDeleteBuffers");
	qalDeleteSources			= (LPALDELETESOURCES)GPA("alDeleteSources");
	qalDisable					= (LPALDISABLE)GPA("alDisable");
	qalDistanceModel			= (LPALDISTANCEMODEL)GPA("alDistanceModel");
	qalDopplerFactor			= (LPALDOPPLERFACTOR)GPA("alDopplerFactor");
	qalDopplerVelocity			= (LPALDOPPLERVELOCITY)GPA("alDopplerVelocity");
	qalEnable					= (LPALENABLE)GPA("alEnable");
	qalGenBuffers				= (LPALGENBUFFERS)GPA("alGenBuffers");
	qalGenSources				= (LPALGENSOURCES)GPA("alGenSources");
	qalGetBoolean				= (LPALGETBOOLEAN)GPA("alGetBoolean");
	qalGetBooleanv				= (LPALGETBOOLEANV)GPA("alGetBooleanv");
	qalGetBufferf				= (LPALGETBUFFERF)GPA("alGetBufferf");
	qalGetBufferi				= (LPALGETBUFFERI)GPA("alGetBufferi");
	qalGetDouble				= (LPALGETDOUBLE)GPA("alGetDouble");
	qalGetDoublev				= (LPALGETDOUBLEV)GPA("alGetDoublev");
	qalGetEnumValue				= (LPALGETENUMVALUE)GPA("alGetEnumValue");
	qalGetError					= (LPALGETERROR)GPA("alGetError");
	qalGetFloat					= (LPALGETFLOAT)GPA("alGetFloat");
	qalGetFloatv				= (LPALGETFLOATV)GPA("alGetFloatv");
	qalGetInteger				= (LPALGETINTEGER)GPA("alGetInteger");
	qalGetIntegerv				= (LPALGETINTEGERV)GPA("alGetIntegerv");
	qalGetListener3f			= (LPALGETLISTENER3F)GPA("alGetListener3f");
	qalGetListenerf				= (LPALGETLISTENERF)GPA("alGetListenerf");
	qalGetListenerfv			= (LPALGETLISTENERFV)GPA("alGetListenerfv");
	qalGetListeneri				= (LPALGETLISTENERI)GPA("alGetListeneri");
	qalGetProcAddress			= (LPALGETPROCADDRESS)GPA("alGetProcAddress");
	qalGetSource3f				= (LPALGETSOURCE3F)GPA("alGetSource3f");
	qalGetSourcef				= (LPALGETSOURCEF)GPA("alGetSourcef");
	qalGetSourcefv				= (LPALGETSOURCEFV)GPA("alGetSourcefv");
	qalGetSourcei				= (LPALGETSOURCEI)GPA("alGetSourcei");
	qalGetString				= (LPALGETSTRING)GPA("alGetString");
	qalIsBuffer					= (LPALISBUFFER)GPA("alIsBuffer");
	qalIsEnabled				= (LPALISENABLED)GPA("alIsEnabled");
	qalIsExtensionPresent		= (LPALISEXTENSIONPRESENT)GPA("alIsExtensionPresent");
	qalIsSource					= (LPALISSOURCE)GPA("alIsSource");
	qalListener3f				= (LPALLISTENER3F)GPA("alListener3f");
	qalListenerf				= (LPALLISTENERF)GPA("alListenerf");
	qalListenerfv				= (LPALLISTENERFV)GPA("alListenerfv");
	qalListeneri				= (LPALLISTENERI)GPA("alListeneri");
	qalSource3f					= (LPALSOURCE3F)GPA("alSource3f");
	qalSourcef					= (LPALSOURCEF)GPA("alSourcef");
	qalSourcefv					= (LPALSOURCEFV)GPA("alSourcefv");
	qalSourcei					= (LPALSOURCEI)GPA("alSourcei");
	qalSourcePause				= (LPALSOURCEPAUSE)GPA("alSourcePause");
	qalSourcePausev				= (LPALSOURCEPAUSEV)GPA("alSourcePausev");
	qalSourcePlay				= (LPALSOURCEPLAY)GPA("alSourcePlay");
	qalSourcePlayv				= (LPALSOURCEPLAYV)GPA("alSourcePlayv");
	qalSourceQueueBuffers		= (LPALSOURCEQUEUEBUFFERS)GPA("alSourceQueueBuffers");
	qalSourceRewind				= (LPALSOURCEREWIND)GPA("alSourceRewind");
	qalSourceRewindv			= (LPALSOURCEREWINDV)GPA("alSourceRewindv");
	qalSourceStop				= (LPALSOURCESTOP)GPA("alSourceStop");
	qalSourceStopv				= (LPALSOURCESTOPV)GPA("alSourceStopv");
	qalSourceUnqueueBuffers		= (LPALSOURCEUNQUEUEBUFFERS)GPA("alSourceUnqueueBuffers");

	openal_active = true;

	return true;
}
#endif

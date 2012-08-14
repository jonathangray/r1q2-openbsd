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


#ifndef __QAL_H__
#define __QAL_H__

#include <AL/al.h>

qboolean	QAL_Init (const char *driver);
void		QAL_Shutdown (void);

// =====================================================================

extern LPALCOPENDEVICE			qalcOpenDevice;
extern LPALCCLOSEDEVICE			qalcCloseDevice;
extern LPALCCREATECONTEXT			qalcCreateContext;
extern LPALCDESTROYCONTEXT		qalcDestroyContext;
extern LPALCMAKECONTEXTCURRENT	qalcMakeContextCurrent;
extern LPALCPROCESSCONTEXT		qalcProcessContext;
extern LPALCSUSPENDCONTEXT		qalcSuspendContext;
extern LPALCGETCURRENTCONTEXT		qalcGetCurrentContext;
extern LPALCGETCONTEXTSDEVICE		qalcGetContextsDevice;
extern LPALCGETSTRING				qalcGetString;
extern LPALCGETINTEGERV			qalcGetIntegerv;
extern LPALCGETERROR				qalcGetError;
extern LPALCISEXTENSIONPRESENT	qalcIsExtensionPresent;
extern LPALCGETPROCADDRESS		qalcGetProcAddress;
extern LPALCGETENUMVALUE			qalcGetEnumValue;

extern LPALBUFFERDATA				qalBufferData;
extern LPALDELETEBUFFERS			qalDeleteBuffers;
extern LPALDELETESOURCES			qalDeleteSources;
extern LPALDISABLE				qalDisable;
extern LPALDISTANCEMODEL			qalDistanceModel;
extern LPALDOPPLERFACTOR			qalDopplerFactor;
extern LPALDOPPLERVELOCITY		qalDopplerVelocity;
extern LPALENABLE					qalEnable;
extern LPALGENBUFFERS				qalGenBuffers;
extern LPALGENSOURCES				qalGenSources;
extern LPALGETBOOLEAN				qalGetBoolean;
extern LPALGETBOOLEANV			qalGetBooleanv;
extern LPALGETBUFFERF				qalGetBufferf;
extern LPALGETBUFFERI				qalGetBufferi;
extern LPALGETDOUBLE				qalGetDouble;
extern LPALGETDOUBLEV				qalGetDoublev;
extern LPALGETENUMVALUE			qalGetEnumValue;
extern LPALGETERROR				qalGetError;
extern LPALGETFLOAT				qalGetFloat;
extern LPALGETFLOATV				qalGetFloatv;
extern LPALGETINTEGER				qalGetInteger;
extern LPALGETINTEGERV			qalGetIntegerv;
extern LPALGETLISTENER3F			qalGetListener3f;
extern LPALGETLISTENERF			qalGetListenerf;
extern LPALGETLISTENERFV			qalGetListenerfv;
extern LPALGETLISTENERI			qalGetListeneri;
extern LPALGETPROCADDRESS			qalGetProcAddress;
extern LPALGETSOURCE3F			qalGetSource3f;
extern LPALGETSOURCEF				qalGetSourcef;
extern LPALGETSOURCEFV			qalGetSourcefv;
extern LPALGETSOURCEI				qalGetSourcei;
extern LPALGETSTRING				qalGetString;
extern LPALISBUFFER				qalIsBuffer;
extern LPALISENABLED				qalIsEnabled;
extern LPALISEXTENSIONPRESENT		qalIsExtensionPresent;
extern LPALISSOURCE				qalIsSource;
extern LPALLISTENER3F				qalListener3f;
extern LPALLISTENERF				qalListenerf;
extern LPALLISTENERFV				qalListenerfv;
extern LPALLISTENERI				qalListeneri;
extern LPALSOURCE3F				qalSource3f;
extern LPALSOURCEF				qalSourcef;
extern LPALSOURCEFV				qalSourcefv;
extern LPALSOURCEI				qalSourcei;
extern LPALSOURCEPAUSE			qalSourcePause;
extern LPALSOURCEPAUSEV			qalSourcePausev;
extern LPALSOURCEPLAY				qalSourcePlay;
extern LPALSOURCEPLAYV			qalSourcePlayv;
extern LPALSOURCEQUEUEBUFFERS		qalSourceQueueBuffers;
extern LPALSOURCEREWIND			qalSourceRewind;
extern LPALSOURCEREWINDV			qalSourceRewindv;
extern LPALSOURCESTOP				qalSourceStop;
extern LPALSOURCESTOPV			qalSourceStopv;
extern LPALSOURCEUNQUEUEBUFFERS	qalSourceUnqueueBuffers;


#endif	// __QAL_H__

/*
 * RealRTCW XR: MSVC has no pthreads. Upstream RealRTCW (built with MinGW)
 * starts a detached thread that sleeps and then clears FL_NOTARGET; this
 * maps the two calls it uses onto the MSVC CRT so the behaviour is unchanged.
 */
#ifndef G_THREAD_COMPAT_H
#define G_THREAD_COMPAT_H

#ifdef _MSC_VER
#include <process.h>
#include <stdlib.h>

__declspec(dllimport) void __stdcall Sleep( unsigned long dwMilliseconds );
__declspec(dllimport) int __stdcall CloseHandle( void *hObject );

typedef uintptr_t pthread_t;

typedef struct {
	void *( *func )( void * );
	void *arg;
} xrThreadStart_t;

static unsigned __stdcall XR_ThreadTrampoline( void *p ) {
	xrThreadStart_t start = *(xrThreadStart_t *)p;
	free( p );
	start.func( start.arg );
	return 0;
}

static int pthread_create( pthread_t *thread, const void *attr, void *( *func )( void * ), void *arg ) {
	xrThreadStart_t *start = malloc( sizeof( *start ) );

	(void)attr;
	if ( !start ) {
		return -1;
	}
	start->func = func;
	start->arg = arg;

	*thread = _beginthreadex( NULL, 0, XR_ThreadTrampoline, start, 0, NULL );
	if ( !*thread ) {
		free( start );
		return -1;
	}
	CloseHandle( (void *)*thread ); // detached, like upstream
	return 0;
}

static unsigned int sleep( unsigned int seconds ) {
	Sleep( seconds * 1000 );
	return 0;
}
#else
#include <pthread.h>
#include <unistd.h>
#endif

#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <signal.h>
//#include "popen_pid.h"
#include "game.h"
#include "portable.h"

#include "sounds.h"

void soundInit(void) { }
void soundEnableMusic(bool enable) { }
void soundPlay(sound_t sound) { }
void soundStopAll(void) { }


// typedef struct {
//     int pid;
//     FILE* stream;
//     pthread_t* thread; 
//     const char* file;
//     bool loop;
// } qe_t;
// 
// static qe_t queue[ 6 ] = {0, };
// static bool music_enabled = true;
// 
// static void deQueue( int pid );
// static void enQueue( const char* file, bool loop );
// static bool fullQueue( void );
// 
// static void* startPlayback( void *arg ) {
//    qe_t* e = arg;
//    char *cmd = "aplay";
//    char file[256] = {0,};
//    char *path = getenv( "STEWIE_PATH" );
//    if ( !path ) {
//       path = ".";
//    }
//    snprintf( file, sizeof(file)-1, "%s/sounds/%s.wav", path, e->file );
//    char *args[] = {cmd, "-q", file, NULL};
//    do {
//        printf( "play:%s\n", e->file );
//        e->stream = popen_pid( args, 'w', &(e->pid) );
//        assert( e->stream );
//        assert( e->pid );
//        printf( "waiting:%d\n", e->pid );
//        pclose_pid( e->stream, e->pid ); // waits
//    } while ( e->loop );
//    printf( "done:%d\n", e->pid );
//    memset( e, 0x00, sizeof(qe_t) );
//    return NULL;
// }
// 
// static void deQueue( int pid ) {
//     for (int i=0; i<sizeof(queue)/sizeof(queue[0]); i++) {
//         qe_t* e = &queue[ i ];
//         if ( e->pid == pid ) {
//             memset( e, 0x00, sizeof(qe_t) );
//             return;
//         }
//     }
//     printf("dequeue failed %d\n", pid);
// }
// 
// static void enQueue( const char* file, bool loop ) {
//     for (int i=0; i<sizeof(queue)/sizeof(queue[0]); i++) {
//         qe_t* e = &queue[ i ];
//         if ( e->pid == 0 ) {
//             static int pid = 1;
//             e->pid = pid++;
//             e->file = file;
//             e->loop = loop;
//             e->thread = gpioStartThread( startPlayback, e );
//             return;
//         }
//     }
//     printf("enqueue failed %s\n", file);
// }
// 
// static bool fullQueue( void ) {
//     for (int i=0; i<sizeof(queue)/sizeof(queue[0]); i++) {
//         qe_t* e = &queue[ i ];
//         if ( e->pid == 0 ) {
//             return false;   
//         }
//     }
//     return true;
// }
// 
// void soundInit(void) {
//     printf("soundInit\n");
//     soundStopAll();
// }
// 
// void soundEnableMusic(bool enable) {
//     music_enabled = enable;
// }  
// 
// void soundStopAll(void) {
//     printf("soundStopAll\n");
//     for (int i=0; i<sizeof(queue)/sizeof(queue[0]); i++) {
//         qe_t* e = &queue[ i ];
//         if ( e->pid ) {
//             printf( "killing:%d\n", e->pid );
//             kill( e->pid, SIGINT );
//  //           pclose_pid( e->stream, e->pid );
//  //           gpioStopThread( e->thread );
//         }
//     }
//     memset( queue, 0x00, sizeof(queue) );
// }
// 
// static void soundPlayFile(const char *file, bool loop) {
//     if ( !fullQueue() ) {
//         enQueue( file, loop );
//     }
// }
// 
// void soundPlay(sound_t sound) {
//     switch( sound ) {
//         case sound_boot: {
//             static const char* s = "Small playfield intro";
//             soundPlayFile( s, false );
//             break; }
// 
//         case sound_start: {
//             static const char* s[]= {
//                 "Main theme music",
//                 "Timed event music",
//                 "Chris theme music",
//             };
//             if ( music_enabled ) {
//                 soundPlayFile( s[rand()/(RAND_MAX / 3 + 1)], true );
//             }
//             break; }
// 
//         case sound_launch: {
//             static const char* s[] = {
//                 "Launch 1",
//                 "Launch 2",
//                 "Launch 3",
//                 "Launch 4",
//                 "Launch 5"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 5 + 1)], false );
//             break; }
// 
//         case sound_hit: {
//             static const char* s[] = {
//                 "Hit 1",
//                 "Hit 2 (fart)",
//                 "Hit 3",
//                 "Hit 4",
//                 "Hit 5",
//                 "Hit 6",
//                 "Hit 7",
//                 "Hit 8",
//                 "Hit 9",
//                 "Hit 10",
//                 "Hit 11"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 10 + 1)], false );
//             break; }
// 
//         case sound_game_over: {
//             static const char* s[]= {
//                 "Stewie says game over man",
//                 "Stewie will not tolerate failure"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 2 + 1)], false );
//             break; }
// 
//         case sound_drain: {
//             static const char* s[] = {
//                 "Drain music 1",
//                 "Drain music 2",
//                 "Drain music 3",
//                 "Drain music 4",
//                 "Drain music 5",
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 5 + 1)], false );
//             break; }
// 
//         case sound_brian: {
//             static const char* s[]= {
//                 "Brian asks if anyone wants a mojito",
//                 "Brian says good good so far",
//                 "Brian says wow",
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 3 + 1)], false );
//             break; }
// 
//         case sound_meg: {
//             static const char* s[]= {
//                 "Meg cries",
//                 "Meg hates everyone",
//                 "Meg wants Lois to do something"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 3 + 1)], false );
//             break; }
// 
//         case sound_peter: {
//             static const char* s[]= {
//                 "Peter giggles",
//                 "Peter has an idea",
//                 "Peter says that was awesome",
//                 "Peter says you bastard"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 4 + 1)], false );
//             break; }
// 
//         case sound_lois: {
//             static const char* s[]= {
//                 "Lois advises Meg",
//                 "Lois isn't wearing any panties",
//                 "Lois says what on earth was that"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 3 + 1)], false );
//             break; }
// 
//         case sound_chris: {
//             static const char* s[]= {
//                 "Chris isn't supposed to mention poo",
//                 "Someone peed in Chris' pants"
//             };
//             soundPlayFile( s[rand()/(RAND_MAX / 2 + 1)], false );
//             break; }
//     }
// }
// 

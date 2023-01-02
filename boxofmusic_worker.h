#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef void (*boxofMusicWorkerCallback)(
    uint8_t semitone,
    uint8_t dots,
    uint8_t duration,
    float position,
    void* context);

typedef struct boxofMusicWorker boxofMusicWorker;

boxofMusicWorker* boxofmusic_worker_alloc();

void boxofmusic_worker_clear(boxofMusicWorker* instance);

void boxofmusic_worker_free(boxofMusicWorker* instance);

bool boxofmusic_worker_load(boxofMusicWorker* instance, const char* file_path);

bool boxofmusic_worker_load_fmf_from_file(boxofMusicWorker* instance, const char* file_path);

bool boxofmusic_worker_load_rtttl_from_file(boxofMusicWorker* instance, const char* file_path);

bool boxofmusic_worker_load_rtttl_from_string(boxofMusicWorker* instance, const char* string);

void boxofmusic_worker_set_callback(
    boxofMusicWorker* instance,
    boxofMusicWorkerCallback callback,
    void* context);

void boxofmusic_worker_set_volume(boxofMusicWorker* instance, float volume);

void boxofmusic_worker_start(boxofMusicWorker* instance);

void boxofmusic_worker_stop(boxofMusicWorker* instance);

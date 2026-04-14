/*
 * dusty_log.h — C-side logging bridge for Dusty Bytes platform
 *
 * Include in Emscripten game engine forks. Routes log calls through EM_ASM
 * to the JS logging framework (dusty.log) in the Web Worker.
 *
 * Build with -DDUSTY_LOG_ENABLED to include logging.
 * Without the flag, all calls compile to nothing.
 *
 * Usage:
 *   DUSTY_LOG("combat", "info", "hit %s for %d damage", target, dmg);
 *   DUSTY_LOG("vfs", "warn", "file not found: %s", path);
 */

#ifndef DUSTY_LOG_H
#define DUSTY_LOG_H

#ifdef DUSTY_LOG_ENABLED

#include <emscripten.h>
#include <stdio.h>

#define DUSTY_LOG(channel, level, fmt, ...) \
    do { \
        char _dusty_buf[512]; \
        snprintf(_dusty_buf, sizeof(_dusty_buf), fmt, ##__VA_ARGS__); \
        EM_ASM({ \
            if (typeof dusty !== 'undefined' && dusty.log) { \
                dusty.log(UTF8ToString($0), UTF8ToString($1), UTF8ToString($2)); \
            } \
        }, channel, level, _dusty_buf); \
    } while (0)

#else

#define DUSTY_LOG(channel, level, fmt, ...) ((void)0)

#endif /* DUSTY_LOG_ENABLED */

#endif /* DUSTY_LOG_H */

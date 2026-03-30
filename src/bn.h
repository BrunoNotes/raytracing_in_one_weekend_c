#pragma once

/*
BrunoNotes C helper lib
#define BN_IMPLEMENTATION
#include "bn.h"
*/

#define BN_ASSERT_ENABLED // comment to disable asserts

// clang-format off
#if defined(__cplusplus)
    extern "C" {
#endif

#include <stdbool.h>

#ifndef thread_local
    #define thread_local _Thread_local
#endif

#ifdef __GNUC__
    #ifndef _VA_LIST_DEFINED
        #include <stdio.h>
        typedef __gnuc_va_list va_list;
        #define _VA_LIST_DEFINED
    #endif
#else
    #include <stdarg.h>
#endif

#ifndef va_arg
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
        /* C23 uses a special builtin. */
        #define va_start(...) __builtin_c23_va_start(__VA_ARGS__)
    #else
        /* Versions before C23 do require the second parameter. */
        #define va_start(ap, param) __builtin_va_start(ap, param)
    #endif
    #define va_end(ap) __builtin_va_end(ap)
    #define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif

#if _MSC_VER
    #include <intrin.h>
    #define debugBreak() __debugbreak()
#else
    #define debugBreak() __builtin_trap()
#endif
// clang-format on

#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef i8 b8;
typedef i32 b32;
typedef i64 b64;
typedef float f32;
typedef double f64;

#define vec2Prototype(type)                                                    \
    typedef union U_Vec2##type {                                               \
        type elements[2];                                                      \
        struct {                                                               \
            union {                                                            \
                type x, r, s, u;                                               \
            };                                                                 \
            union {                                                            \
                type y, g, t, v;                                               \
            };                                                                 \
        };                                                                     \
    } Vec2##type;

vec2Prototype(f32);
vec2Prototype(f64);

#define vec3Prototype(type)                                                    \
    typedef union U_Vec3##type {                                               \
        type elements[3];                                                      \
        struct {                                                               \
            union {                                                            \
                type x, r, s, u;                                               \
            };                                                                 \
            union {                                                            \
                type y, g, t, v;                                               \
            };                                                                 \
            union {                                                            \
                type z, b, p, w;                                               \
            };                                                                 \
        };                                                                     \
    } Vec3##type;

vec3Prototype(f32);
vec3Prototype(f64);

Vec3f32 vec3f32Add(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32AddScalar(Vec3f32 u, f32 s);
Vec3f32 vec3f32Sub(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32Mult(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32MultScalar(Vec3f32 u, f32 s);
Vec3f32 vec3f32DivScalar(Vec3f32 u, f32 s);
f32 vec3f32LengthSquared(Vec3f32 v);
f32 vec3f32Length(Vec3f32 v);
Vec3f32 vec3f32UnitVector(Vec3f32 v);
f32 vec3f32Dot(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32Cross(Vec3f32 u, Vec3f32 v);

#define vec4Prototype(type)                                                    \
    typedef union U_Vec4##type {                                               \
        type elements[4];                                                      \
        struct {                                                               \
            union {                                                            \
                type x, r, s;                                                  \
            };                                                                 \
            union {                                                            \
                type y, g, t;                                                  \
            };                                                                 \
            union {                                                            \
                type z, b, p;                                                  \
            };                                                                 \
            union {                                                            \
                type w, a, q;                                                  \
            };                                                                 \
        };                                                                     \
    } Vec4##type;

vec4Prototype(f32);
vec4Prototype(f64);

#define arrayLength(a) (sizeof(a) / sizeof(a[0]))

#define slicePrototype(type)                                                   \
    typedef struct {                                                           \
        type* ptr;                                                             \
        u32 length;                                                            \
    } type##Slice

#define sliceInit(type, p, len) ((type##Slice){.ptr = (p), .length = (len)})

slicePrototype(i8);
slicePrototype(i16);
slicePrototype(i32);
slicePrototype(i64);
slicePrototype(u8);
slicePrototype(u16);
slicePrototype(u32);
slicePrototype(u64);
slicePrototype(b8);
slicePrototype(b32);
slicePrototype(b64);
slicePrototype(f32);
slicePrototype(f64);

typedef struct {
    char* str;
    u32 len;
} String32;

String32 string32Substring(String32 str, u32 start, u32 end);

#define stringLit(s)                                                           \
    (String32){(char*)(s), sizeof((s)) - 1} // makes a string from char*
#define stringFmt(s)                                                           \
    (int)(s).len, (s).str // to be used with "%.*s" in printf for example

#define Byte 1
#define KiloByte (u32)(1024 * Byte)
#define MegaByte (u32)(1024 * KiloByte)
#define GigaByte (u32)(1024 * MegaByte)
#define TeraByte (u32)(1024 * GigaByte)
#define PetaByte (u32)(1024 * TeraByte)
#define ExaByte (u32)(1024 * PetaByte)

#define Kib(n) ((u32)(n) * KiloByte)
#define Mib(n) ((u32)(n) * MegaByte)
#define Gib(n) ((u32)(n) * GigaByte)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define alignPow2(x, b) (((x) + (b) - 1) & (~((b) - 1)))

typedef enum {
    LogLevel_Debug = 0,
    LogLevel_Info = 1,
    LogLevel_Warning = 2,
    LogLevel_Error = 3,
    LogLevel_Panic = 4,
} LogLevel;

void defaultLogHandler(LogLevel level, const char* fmt, va_list args);

typedef void(LogHandler)(LogLevel level, const char* fmt, va_list args);

void bnLog(LogLevel level, const char* fmt, ...);
LogLevel getMinLogLevel();
void setMinLogLevel(LogLevel level);
void setLogHandler(LogHandler* handler);

#define logInfo(message) bnLog(LogLevel_Info, message)
#define logInfof(...) bnLog(LogLevel_Info, __VA_ARGS__)
#define logWarn(message) bnLog(LogLevel_Warning, message)
#define logWarnf(...) bnLog(LogLevel_Warning, __VA_ARGS__)
#define logError(message) bnLog(LogLevel_Error, message)
#define logErrorf(...) bnLog(LogLevel_Error, __VA_ARGS__)
#define logPanic(message) bnLog(LogLevel_Panic, message)
#define logPanicf(...) bnLog(LogLevel_Panic, __VA_ARGS__)
#define logDebug(message) bnLog(LogLevel_Debug, message)
#define logDebugf(...) bnLog(LogLevel_Debug, __VA_ARGS__)
#define logFatal(message) bnLog(LogLevel_Fatal, message)
#define logFatalf(...) bnLog(LogLevel_Fatal, __VA_ARGS__)

// clang-format off
#ifdef BN_ASSERT_ENABLED
    #define bnAssert(expr)                                                         \
        do {                                                                       \
            if (expr) {                                                            \
            } else {                                                               \
                logErrorf(                                                         \
                    "Assertion Failure: %s, in file: %s, line: %d", #expr,         \
                    __FILE__, __LINE__                                             \
                );                                                                 \
                debugBreak();                                                      \
            }                                                                      \
        } while (0)

    #define bnAssertMsg(expr, msg)                                                 \
        do {                                                                       \
            if (expr) {                                                            \
            } else {                                                               \
                logErrorf(                                                         \
                    "Assertion Failure: %s, in file: %s, line: %d, msg: %s",       \
                    #expr, __FILE__, __LINE__, msg                                 \
                );                                                                 \
                debugBreak();                                                      \
            }                                                                      \
        } while (0)
#else
    #define bnAssert(expr)
    #define bnAssertMsg(expr, msg)
#endif
// clang-format on

u32 platformGetPageSize(void);
void* platformMemReserve(u64 size);
b32 platformMemCommit(void* ptr, u64 size);
b32 platformMemDecommit(void* ptr, u64 size);
b32 platformMemRelease(void* ptr, u64 size);

#define ARENA_BASE_POS (sizeof(Arena))
#define ARENA_ALIGN (sizeof(void*))

typedef enum {
    ArenaType_Static,
    ArenaType_Growing,
} ArenaType;

typedef struct {
    u64 reserve_size;
    u64 commit_size;
    u64 pos;
    u64 commit_pos;
    ArenaType type;
} Arena;

Arena* initArena(u64 reserve_size, u64 commit_size, ArenaType type);
void destroyArena(Arena* arena);

void* arenaPush(Arena* arena, u64 size, b32 non_zero);
void arenaRealloc(Arena* arena, u64 new_pos);
void arenaPop(Arena* arena, u64 size);
void arenaPopTo(Arena* arena, u64 pos);

typedef struct {
    Arena* arena;
    u64 start_pos;
} TempArena;

TempArena beginTempArena(Arena* arena);
void endTempArena(TempArena temp);

void* heapAllocatorPush(u64 size, b32 non_zero);
void heapAllocatorFree(void* data, u64 size);

typedef enum {
    AllocatorType_ArenaStatic,
    AllocatorType_ArenaGrowing,
    AllocatorType_HeapAllocator,
    AllocatorType_TempAllocator,
} AllocatorType;

typedef struct {
    u64 reserve_size;
    u64 commit_size;
    AllocatorType type;
} AllocatorInitParams;

typedef struct {
    u64 size;
    b32 non_zero;
} AllocatorParams;

typedef struct {
    AllocatorType type;
    void* data;
    u64 size;
    TempArena _temp;
} Allocator;

Allocator initAllocator(AllocatorInitParams params);
void destroyAllocator(Allocator* alloc);

void* allocatorPush(AllocatorParams params, Allocator* alloc);
void allocatorFree(Allocator* alloc, void* data);
void allocatorFreeAll(Allocator* alloc);

#define allocPushStruct(alloc, T)                                              \
    (T*)allocatorPush((AllocatorParams){sizeof(T), false}, (alloc))
#define allocPushStructNZ(alloc, T)                                            \
    (T*)allocatorPush((AllocatorParams){sizeof(T), true}, (alloc))
#define allocPushArray(alloc, T, len)                                          \
    (T*)allocatorPush((AllocatorParams){sizeof(T) * (len), false}, (alloc))
#define allocPushArrayNZ(alloc, T, len)                                        \
    (T*)allocatorPush((AllocatorParams){sizeof(T) * (len), true}, (alloc))
#define allocFree(alloc, data) allocatorFree((alloc), (data))
#define allocFreeAll(alloc) allocatorFreeAll((alloc))

#define arrayPrototype(type)                                                   \
    typedef struct {                                                           \
        type* items;                                                           \
        u32 count;                                                             \
        u32 capacity;                                                          \
        Allocator* alloc;                                                      \
    } type##Array

arrayPrototype(i8);
arrayPrototype(i16);
arrayPrototype(i32);
arrayPrototype(i64);
arrayPrototype(u8);
arrayPrototype(u16);
arrayPrototype(u32);
arrayPrototype(u64);
arrayPrototype(b8);
arrayPrototype(b32);
arrayPrototype(b64);
arrayPrototype(f32);
arrayPrototype(f64);
arrayPrototype(String32);

// based on https://github.com/tsoding/nob.h
#ifndef DYNAMIC_ARRAY_INITIAL_CAPACITY
#define DYNAMIC_ARRAY_INITIAL_CAPACITY 256
#endif

#define daInit(allocator)                                                      \
    {.items = NULL, .count = 0, .capacity = 0, .alloc = allocator}

#define daReserve(da, expected_capacity)                                       \
    do {                                                                       \
        if ((expected_capacity) > (da)->capacity) {                            \
            if ((da)->capacity == 0) {                                         \
                (da)->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;               \
                (da)->items = allocatorPush(                                   \
                    (AllocatorParams){                                         \
                        (da)->capacity * sizeof(*(da)->items), false           \
                    },                                                         \
                    (da)->alloc                                                \
                );                                                             \
            } else {                                                           \
                u32 old_capacity = (da)->capacity;                             \
                while ((expected_capacity) > (da)->capacity) {                 \
                    (da)->capacity *= 2;                                       \
                }                                                              \
                void* new_entries = allocatorPush(                             \
                    (AllocatorParams){                                         \
                        (da)->capacity * sizeof(*(da)->items), false           \
                    },                                                         \
                    (da)->alloc                                                \
                );                                                             \
                memcpy(                                                        \
                    new_entries, (da)->items,                                  \
                    old_capacity * sizeof(*(da)->items)                        \
                );                                                             \
                allocatorFree((da)->alloc, (da)->items);                       \
                (da)->items = new_entries;                                     \
            }                                                                  \
            bnAssert((da)->items != NULL);                                     \
        }                                                                      \
    } while (0)

#define daAppend(da, item)                                                     \
    do {                                                                       \
        daReserve((da), (da)->count + 1);                                      \
        (da)->items[(da)->count++] = (item);                                   \
    } while (0)

#define daFree(da)                                                             \
    do {                                                                       \
        allocatorFree((da)->alloc, (da)->items);                               \
        (da)->count = 0;                                                       \
        (da)->capacity = 0;                                                    \
    } while (0)

#define daAppendMany(da, new_items, new_items_count)                           \
    do {                                                                       \
        daReserve((da), (da)->count + (new_items_count));                      \
        memcpy(                                                                \
            (da)->items + (da)->count, (new_items),                            \
            (new_items_count) * sizeof(*(da)->items)                           \
        );                                                                     \
        (da)->count += (new_items_count);                                      \
    } while (0)

#define daResize(da, new_size)                                                 \
    do {                                                                       \
        daReserve((da), new_size);                                             \
        (da)->count = (new_size);                                              \
    } while (0)

#define daLast(da) (da)->items[(bnAssert((da)->count > 0), (da)->count - 1)]

#define daRemoveUnordered(da, i)                                               \
    do {                                                                       \
        size_t j = (i);                                                        \
        bnAssert(j < (da)->count);                                             \
        (da)->items[j] = (da)->items[--(da)->count];                           \
    } while (0)

#define daForEach(Type, it, da)                                                \
    for (Type* it = (da)->items; it < (da)->items + (da)->count; ++it)

// fixed array
#define faInit(item)                                                           \
    {.items = (item),                                                          \
     .count = arrayLength((item)),                                             \
     .capacity = arrayLength((item)),                                          \
     .alloc = NULL}

#ifndef HASH_TABLE_INITIAL_CAPACITY
#define HASH_TABLE_INITIAL_CAPACITY 256
#endif

typedef struct {
    String32 key;
    void* value;
} HashTableEntry;

typedef struct {
    HashTableEntry* items;
    u32 count;
    u32 capacity;
    Allocator* alloc;
} HashTable;

#define htInit(allocator)                                                      \
    {.items = NULL, .count = 0, .capacity = 0, .alloc = allocator}

void htReserve(HashTable* table, u32 expected_capacity);
void htFree(HashTable* table);
u32 htLinearProbe(HashTable* table, String32 key);
void* htGet(HashTable* table, String32 key);
void htAppend(HashTable* table, String32 key, void* value);

#ifdef BN_IMPLEMENTATION

#if defined(_WIN32)

#include <windows.h>

u32 platformGetPageSize(void) {
    SYSTEM_INFO sysinfo = {0};
    GetSystemInfo(&sysinfo);

    return sysinfo.dwPageSize;
}

void* platformMemReserve(u64 size) {
    return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
}

b32 platformMemCommit(void* ptr, u64 size) {
    void* ret = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
    return ret != NULL;
}

b32 platformMemDecommit(void* ptr, u64 size) {
    return VirtualFree(ptr, size, MEM_DECOMMIT);
}

b32 platformMemRelease(void* ptr, u64 size) {
    return VirtualFree(ptr, size, MEM_RELEASE);
}

#elif defined(__linux__)

#include <sys/mman.h>
#include <unistd.h>

u32 platformGetPageSize(void) {
    return (u32)sysconf(_SC_PAGESIZE);
}

void* platformMemReserve(u64 size) {
    void* out = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (out == MAP_FAILED) {
        return NULL;
    }
    return out;
}

b32 platformMemCommit(void* ptr, u64 size) {
    i32 ret = mprotect(ptr, size, PROT_READ | PROT_WRITE);
    return ret == 0;
}

b32 platformMemDecommit(void* ptr, u64 size) {
    i32 ret = mprotect(ptr, size, PROT_NONE);
    if (ret != 0)
        return false;
    ret = madvise(ptr, size, MADV_DONTNEED);
    return ret == 0;
}

b32 platformMemRelease(void* ptr, u64 size) {
    i32 ret = munmap(ptr, size);
    return ret == 0;
}

#endif

String32 string32Substring(String32 str, u32 start, u32 end) {
    end = min(end, str.len);
    start = min(start, end);
    return (String32){str.str + start, end - start};
}

#include <string.h>

Arena* initArena(u64 reserve_size, u64 commit_size, ArenaType type) {
    u32 page_size = platformGetPageSize();

    reserve_size = alignPow2(reserve_size, page_size);
    commit_size = alignPow2(commit_size, page_size);

    Arena* arena = (Arena*)platformMemReserve(reserve_size);

    if (!platformMemCommit(arena, commit_size)) {
        return NULL;
    }

    arena->reserve_size = reserve_size;
    arena->commit_size = commit_size;
    arena->pos = ARENA_BASE_POS;
    arena->commit_pos = commit_size;
    arena->type = type;

    return arena;
}

void destroyArena(Arena* arena) {
    bool ok = platformMemRelease(arena, arena->reserve_size);
    bnAssert(ok == true);
}

void* arenaPush(Arena* arena, u64 size, b32 non_zero) {
    u64 pos_aligned = alignPow2(arena->pos, ARENA_ALIGN);
    u64 new_pos = pos_aligned + size;

    // Grow arena if needed
    if (new_pos > arena->reserve_size && arena->type == ArenaType_Growing) {
        arenaRealloc(arena, new_pos);
    }

    if (new_pos > arena->commit_pos) {
        u64 new_commit_pos = new_pos;
        new_commit_pos += arena->commit_size - 1;
        new_commit_pos -= new_commit_pos % arena->commit_size;
        new_commit_pos = min(new_commit_pos, arena->reserve_size);

        u8* mem = (u8*)arena + arena->commit_pos;
        u64 commit_size = new_commit_pos - arena->commit_pos;

        if (!platformMemCommit(mem, commit_size)) {
            return NULL;
        }

        arena->commit_pos = new_commit_pos;
    }

    arena->pos = new_pos;

    u8* out = (u8*)arena + pos_aligned;

    if (!non_zero) {
        memset(out, 0, size);
    }

    return out;
}

void arenaRealloc(Arena* arena, u64 new_pos) {
    u64 new_reserve_size = arena->reserve_size * 2;
    while (new_reserve_size < new_pos) {
        new_reserve_size *= 2;
    }

    u32 page_size = platformGetPageSize();
    new_reserve_size = alignPow2(new_reserve_size, page_size);

    Arena* new_arena = (Arena*)platformMemReserve(new_reserve_size);
    bnAssert(new_arena != NULL);

    // Copy existing data and commit the current committed size
    memcpy(new_arena, arena, arena->commit_pos);
    if (!platformMemCommit(new_arena, arena->commit_pos)) {
        platformMemRelease(new_arena, new_reserve_size);
        return;
    }

    new_arena->reserve_size = new_reserve_size;
    new_arena->commit_size = arena->commit_size;
    new_arena->pos = arena->pos;
    new_arena->commit_pos = arena->commit_pos;

    // Release old arena and update pointer
    platformMemRelease(arena, arena->reserve_size);

    arena = new_arena;
}

void arenaPop(Arena* arena, u64 size) {
    size = min(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}

void arenaPopTo(Arena* arena, u64 pos) {
    u64 size = pos < arena->pos ? arena->pos - pos : 0;
    arenaPop(arena, size);
}

TempArena beginTempArena(Arena* arena) {
    return (TempArena){
        .arena = arena,
        .start_pos = arena->pos,
    };
}

void endTempArena(TempArena temp) {
    arenaPopTo(temp.arena, temp.start_pos);
}

#include <stdlib.h>

Allocator initAllocator(AllocatorInitParams params) {
    Allocator alloc = {0};

    switch (params.type) {
    case AllocatorType_ArenaStatic:
        alloc.data = initArena(
            params.reserve_size, params.commit_size, ArenaType_Static
        );
        alloc.type = params.type;
        break;
    case AllocatorType_ArenaGrowing:
        alloc.data = initArena(
            params.reserve_size, params.commit_size, ArenaType_Growing
        );
        alloc.type = params.type;
        break;
    case AllocatorType_HeapAllocator:
        alloc.data = NULL;
        alloc.size = 0;
        alloc.type = params.type;
        break;
    case AllocatorType_TempAllocator:
        alloc.data = initArena(
            params.reserve_size, params.commit_size, ArenaType_Growing
        );
        alloc.type = params.type;
        alloc._temp = beginTempArena((Arena*)alloc.data);
        break;
    default:
        logPanic("Allocator not implemented");
        break;
    }

    return alloc;
}

void destroyAllocator(Allocator* alloc) {
    switch (alloc->type) {
    case AllocatorType_ArenaStatic:
    case AllocatorType_ArenaGrowing:
        destroyArena((Arena*)alloc->data);
        break;
    case AllocatorType_HeapAllocator:
        break;
    case AllocatorType_TempAllocator:
        endTempArena(alloc->_temp);
        destroyArena((Arena*)alloc->data);
        break;
    default:
        logPanic("Allocator not implemented");
        break;
    }
}

void* heapAllocatorPush(u64 size, b32 non_zero) {
    // void* data = malloc(size);
    u32 page_size = platformGetPageSize();
    size = alignPow2(size, page_size);
    void* data = platformMemReserve(size);

    if (!platformMemCommit(data, size)) {
        return NULL;
    }

    if (!non_zero) {
        memset(data, 0, size);
    }

    return data;
}

void heapAllocatorFree(void* data, u64 size) {
    // free(data);
    // data = NULL;
    platformMemRelease(data, size);
}

void* allocatorPush(AllocatorParams params, Allocator* alloc) {
    switch (alloc->type) {
    case AllocatorType_ArenaStatic:
    case AllocatorType_ArenaGrowing:
        return arenaPush((Arena*)alloc->data, params.size, params.non_zero);
    case AllocatorType_HeapAllocator:
        alloc -> size = params.size;
        return heapAllocatorPush(params.size, params.non_zero);
    case AllocatorType_TempAllocator:
        return arenaPush(
            (Arena*)alloc->_temp.arena, params.size, params.non_zero
        );
    default:
        logPanic("Allocator not initialized");
        return NULL;
    }
}

void allocatorFree(Allocator* alloc, void* data) {
    switch (alloc->type) {
    case AllocatorType_ArenaStatic:
    case AllocatorType_ArenaGrowing:
    case AllocatorType_TempAllocator:
        break;
    case AllocatorType_HeapAllocator:
        heapAllocatorFree(data, alloc->size);
        break;
    default:
        logPanic("Allocator not initialized");
        break;
    }
}

void allocatorFreeAll(Allocator* alloc) {
    switch (alloc->type) {
    case AllocatorType_ArenaStatic:
    case AllocatorType_ArenaGrowing:
        arenaPopTo((Arena*)alloc->data, ARENA_BASE_POS);
        break;
    case AllocatorType_HeapAllocator:
        break;
    case AllocatorType_TempAllocator:
        endTempArena(alloc->_temp);
        alloc->_temp = beginTempArena((Arena*)alloc->data);
        break;
    default:
        logPanic("Allocator not initialized");
        break;
    }
}

#ifdef DEBUG
static LogLevel bn_g_min_log_level = LogLevel_Debug;
#else
static LogLevel bn_g_min_log_level = LogLevel_Info;
#endif

static LogHandler* bn_g_log_handler = NULL;

void defaultLogHandler(LogLevel level, const char* fmt, va_list args) {
    if (level < bn_g_min_log_level) {
        return;
    }

    switch (level) {
    case LogLevel_Debug:
        fprintf(stderr, "\x1b[90m[Debug]\x1b[0m ");
        break;
    case LogLevel_Info:
        fprintf(stderr, "\x1b[0m[Info]\x1b[0m ");
        break;
    case LogLevel_Warning:
        fprintf(stderr, "\x1b[33m[Warn]\x1b[0m ");
        break;
    case LogLevel_Error:
        fprintf(stderr, "\x1b[31m[Error]\x1b[0m ");
        break;
    case LogLevel_Panic:
        fprintf(stderr, "\x1b[35m[Panic]\x1b[0m ");
        break;
    default:
        return;
    }

    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    if (level == LogLevel_Panic) {
        exit(1);
    }
}

void bnLog(LogLevel level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    if (bn_g_log_handler == NULL) {
        bn_g_log_handler = &defaultLogHandler;
    }

    bn_g_log_handler(level, fmt, args);
    va_end(args);
}

LogLevel getMinLogLevel() {
    return bn_g_min_log_level;
}

void setMinLogLevel(LogLevel level) {
    bn_g_min_log_level = level;
}

void setLogHandler(LogHandler* handler) {
    bn_g_log_handler = handler;
}

static inline u32 fvn32aHash(u8* data, u32 length) {
    u32 h = 0x811c9dc5;

    for (u32 i = 0; i < length; i++) {
        h = (h ^ (u32)data[i]) * 0x01000193;
    }

    return h;
}

void htReserve(HashTable* table, u32 expected_capacity) {
    if (expected_capacity > table->capacity) {
        if (table->capacity == 0) {
            table->capacity = HASH_TABLE_INITIAL_CAPACITY;
            table->items = (HashTableEntry*)allocatorPush(
                (AllocatorParams){
                    table->capacity * sizeof(*table->items), false
                },
                table->alloc
            );
        } else {
            while (expected_capacity > table->capacity) {
                table->capacity *= 2;
            }
            HashTableEntry* new_entries = (HashTableEntry*)allocatorPush(
                (AllocatorParams){
                    table->capacity * sizeof(*table->items), false
                },
                table->alloc
            );

            for (u32 i = 0; i < table->capacity; i++) {
                if (table->items[i].key.str != NULL) {
                    new_entries[i] = table->items[i];
                }
            }

            allocatorFree(table->alloc, table->items);
            table->items = new_entries;
        }
        bnAssert(table->items != NULL);
    }
}

void htFree(HashTable* table) {
    allocatorFree(table->alloc, table->items);
    table->count = 0;
    table->capacity = 0;
}

u32 htLinearProbe(HashTable* table, String32 key) {
    u32 hash = fvn32aHash((u8*)key.str, key.len);
    u32 idx = (u32)(hash & (u32)(table->capacity - 1));

    while (table->items[idx].key.str != NULL) {
        if (strcmp(key.str, table->items[idx].key.str) == 0) {
            // Found key
            return idx;
        }
        // Key wasn't in this slot, move to next (linear probing).
        idx++;
        if (idx >= table->capacity) {
            // At end of entries array, wrap around.
            idx = 0;
        }
    }
    return idx;
}

void* htGet(HashTable* table, String32 key) {
    u32 idx = htLinearProbe(table, key);

    return table->items[idx].value;
}

void htAppend(HashTable* table, String32 key, void* value) {
    bnAssert(value != NULL);

    htReserve(table, table->count + 1);

    u32 idx = htLinearProbe(table, key);

    if (table->items[idx].key.str == NULL) {
        table->items[idx].key = key;
    }
    table->items[idx].value = value;
    table->count++;
}

#include <math.h>

Vec3f32 vec3f32Add(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x + v.x, u.y + v.y, u.z + v.z}};
}

Vec3f32 vec3f32AddScalar(Vec3f32 u, f32 s) {
    return (Vec3f32){{u.x + s, u.y + s, u.z + s}};
}

Vec3f32 vec3f32Sub(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x - v.x, u.y - v.y, u.z - v.z}};
}

Vec3f32 vec3f32Mult(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x * v.x, u.y * v.y, u.z * v.z}};
}

Vec3f32 vec3f32MultScalar(Vec3f32 u, f32 s) {
    return (Vec3f32){{u.x * s, u.y * s, u.z * s}};
}

Vec3f32 vec3f32DivScalar(Vec3f32 u, f32 s) {
    return (Vec3f32)vec3f32MultScalar(u, (1 / s));
}

f32 vec3f32LengthSquared(Vec3f32 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

f32 vec3f32Length(Vec3f32 v) {
    return sqrt(vec3f32LengthSquared(v));
}

Vec3f32 vec3f32UnitVector(Vec3f32 v) {
    return vec3f32DivScalar(v, vec3f32Length(v));
}

f32 vec3f32Dot(Vec3f32 u, Vec3f32 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vec3f32 vec3f32Cross(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){
        {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x}
    };
}

#endif

#if defined(__cplusplus)
}
#endif

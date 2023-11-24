#pragma once

// ZPL impl does not play well with raylib because windows.h
#include <zpl/zpl.h>

#define FLECS_SYSTEM
#include <flecs/flecs.h>

#include "Base.h"
#include "Vector2i.h"
#include "Utils.h"
#include "Memory.h"
#include "Lib/Random.h"

/*
*
* -TODO
* -NOTE
* -COMMENT_THIS
* -FIXME
*
*/

typedef Vector2i Vec2i;

#if 1
	#define SPrintPrefix(level) zpl_printf("%s ", level)
#else
	#define SPrintPrefix(level)
#endif

#if 1
	#define SPrintLine() zpl_printf("\n")
#else
	#define SPrintPrefix(level)
#endif

#define SPrint(fmt, ...) SPrintPrefix("[Info]"), zpl_printf(fmt, __VA_ARGS__), SPrintLine()
#define SPrintDebug(fmt, ...) SPrintPrefix("[Debug]"), zpl_printf(fmt, __VA_ARGS__), SPrintLine()

#define SPrintErr(fmt, ...) SPrintPrefix("[Error]"), zpl_printf_err(fmt, __VA_ARGS__), SPrintLine()
#define SPrintWarn(fmt, ...) SPrintPrefix("[Warning]"), zpl_printf_err(fmt, __VA_ARGS__), SPrintLine()
#define SPrintTrace(fmt, ...) SPrintPrefix("[Trace]"), zpl_printf_err(fmt, __VA_ARGS__), SPrintLine()
#define SPrintFatal(fmt, ...) SPrintPrefix("[Fatal]"), zpl_printf_err(fmt, __VA_ARGS__), SPrintLine()

#if SCAL_DEBUG
	#define SAssert(expr) if (!(expr)) { SPrintErr("Assertion Failure: %s\nMessage: % s\n  File : % s, Line : % d\n", #expr, "", __FILE__, __LINE__); DebugBreak(void); } 
	#define SAssertMsg(expr, msg) if (!(expr)) { SPrintErr("Assertion Failure: %s\nMessage: % s\n  File : % s, Line : % d\n", #expr, msg, __FILE__, __LINE__); DebugBreak(void); }
	#define STraceLog(msg, ...) SPrintTrace(msg, __VA_ARGS__)
	#define SDebugLog(msg, ...) SPrintDebug(msg, __VA_ARGS__)
#else
	#define SAssert(expr)
	#define SAssertMsg(expr, msg)
	#define STraceLog(msg, ...)
	#define SDebugLog(msg, ...)
#endif

#if 1
#define SInfoLog(msg, ... ) SPrint(msg, __VA_ARGS__)
#define SWarn(msg, ... ) SPrintWarn(msg, __VA_ARGS__)

#define SError(msg, ...) \
	SPrintErr(msg, __VA_ARGS__); \
	DebugBreak(void) \

#define SFatal(msg, ...) \
	SPrintFatal(msg, __VA_ARGS__); \
	SPrintFatal("Fatal error detected, program crashed! File: %s, Line: %s", __FILE__, __LINE__); \
	DebugBreak(void) \

#else
#define SInfoLog(msg, ... )
#define SWarn(msg, ... )
#define SError(msg, ...) DebugBreak(void)
#define SFatal(msg, ...) DebugBreak(void) 
#endif
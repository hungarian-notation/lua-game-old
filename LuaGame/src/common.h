#pragma once

#include "conf.h"
#include "gl_headers.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include <lua53\lua.hpp>

#ifdef _DEBUG
#include <intrin.h>
#define _HANDLE_ERROR_TRACE(errtype, what_cstr) __debugbreak()
#else
#define _HANDLE_ERROR_TRACE(errtype, what_cstr)  throw new errtype (what_cstr)
#endif

#define _err(what_cstr)	_HANDLE_ERROR_TRACE(std::runtime_error, what_cstr)
#define _bug(what_cstr)	_HANDLE_ERROR_TRACE(std::logic_error, what_cstr)
#define _notnull(var) if (!var) _HANDLE_ERROR_TRACE(std::invalid_argument, #var " is null")

#ifdef _DEBUG
bool _trace(char *format, ...);
#define _log _trace
#else
#define _log __noop
#endif

#include "reference_counted.h"
#include "graphics\vertex.h"

#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(XBOFSWIN_LIB)
#  define XBOFSWIN_EXPORT Q_DECL_EXPORT
# else
#  define XBOFSWIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define XBOFSWIN_EXPORT
#endif

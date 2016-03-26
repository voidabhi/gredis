

# - Try to find HIREDIS
# Once done this will define
#  HIREDIS_FOUND - System has HIREDIS
#  HIREDIS_INCLUDE_DIRS - The HIREDIS include directories
#  HIREDIS_LIBRARIES - The libraries needed to use HIREDIS
#  HIREDIS_DEFINITIONS - Compiler switches required for using HIREDIS

find_package(PkgConfig)
pkg_check_modules(PC_LIBHIREDIS hiredis)
set(HIREDIS_DEFINITIONS ${PC_HIREDIS_CFLAGS_OTHER})

find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h
       HINTS ${PC_HIREDIS_INCLUDEDIR} ${PC_HIREDIS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/thirdparty/include
		/usr/include /usr/local/include /opt/local/include)

find_library(HIREDIS_LIBRARY NAMES libhiredis.a hiredis libhiredis
       HINTS ${PC_HIREDIS_LIBDIR} ${PC_HIREDIS_LIBRARY_DIRS} ${PROJECT_SOURCE_DIR}/thirdparty/lib 
		/usr/lib /usr/lib64 /usr/local/lib /opt/local/lib)

set(HIREDIS_LIBRARIES ${HIREDIS_LIBRARY} )
set(HIREDIS_INCLUDE_DIRS ${HIREDIS_INCLUDE_DIR} )

#include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set HIREDIS_FOUND to TRUE
# if all listed variables are TRUE

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
if (CMAKE_VERSION LESS 2.8.3)
	find_package_handle_standard_args(HIREDIS DEFAULT_MSG HIREDIS_INCLUDE_DIR HIREDIS_LIBRARY)
else ()
	find_package_handle_standard_args(HIREDIS REQUIRED_VARS HIREDIS_INCLUDE_DIR HIREDIS_LIBRARY)
endif ()
#mark_as_advanced(HIREDIS_INCLUDE_DIR HIREDIS_LIBRARY )

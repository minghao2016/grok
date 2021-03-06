#    Copyright (C) 2016-2017 Grok Image Compression Inc.
#
#    This source code is free software: you can redistribute it and/or  modify
#    it under the terms of the GNU Affero General Public License, version 3,
#    as published by the Free Software Foundation.
#
#    This source code is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.
#
#    You should have received a copy of the GNU Affero General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
#    This source code incorporates work covered by the following copyright and
#    permission notice:
#
# Copyright � 2015 Open Microscopy Environment / University of Dundee
# Written by Roger Leigh <rleigh@codelibre.net>
#
# Permission to use, copy, modify, distribute, and sell this software and
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Sam Leffler and Silicon Graphics.
#
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.

cmake_minimum_required(VERSION 2.8.9)

# Default policy is from 2.8.9
cmake_policy(VERSION 2.8.9)
# Set MacOSX @rpath usage globally.
if (POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif(POLICY CMP0020)
if (POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif(POLICY CMP0042)
# Use new variable expansion policy.
if (POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif(POLICY CMP0053)
if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif(POLICY CMP0054)


project(libtiff)

set(VERSION "\"4.0.8\"")
set(PACKAGE_VERSION ${VERSION})
set(PACKAGE "\"tiff\"")

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/EHsc")
ENDIF(MSVC)


include(GNUInstallDirs)
include(CheckCCompilerFlag)
include(CheckCSourceCompiles)
include(CheckIncludeFile)
include(CheckTypeSize)
include(CheckFunctionExists)
enable_testing()

macro(current_date var)
  if(UNIX)
    execute_process(COMMAND "date" +"%Y%m%d" OUTPUT_VARIABLE ${var})
  endif()
endmacro()

current_date(RELEASE_DATE)

macro(extra_dist)
  foreach(file ${ARGV})
    file(RELATIVE_PATH relfile "${PROJECT_SOURCE_DIR}"
         "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    list(APPEND EXTRA_DIST "${relfile}")
  endforeach()
  set(EXTRA_DIST "${EXTRA_DIST}" PARENT_SCOPE)
endmacro()


include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(BEFORE "${CMAKE_CURRENT_BINARY_DIR}")

set(TARGET_FILES
  t4.h
  tiffiop.h
  tif_aux.c
  tif_close.c
  tif_codec.c
  tif_color.c
  tif_compress.c
  tif_dir.c
  tif_dir.h
  tif_dirinfo.c
  tif_dirread.c
  tif_dirwrite.c
  tif_dumpmode.c
  tif_error.c
  tif_extension.c
  tif_fax3.c
  tif_fax3.h
  tif_fax3sm.c
  tif_flush.c
  tif_getimage.c
  tif_jbig.c
  tif_jpeg.c
  tif_luv.c
  tif_lzw.c
  tif_next.c
  tif_ojpeg.c
  tif_open.c
  tif_packbits.c
  tif_pixarlog.c
  tif_predict.c
  tif_predict.h
  tif_print.c
  tif_read.c
  tif_stream.cxx
  tiffio.hxx
  tif_strip.c
  tif_swab.c
  tif_thunder.c
  tif_tile.c
  tif_version.c
  tif_warning.c
  tif_write.c
  tif_zip.c
  tif_jpeg_12.c
  tif_lzma.c
  uvcode.h
  )

if(UNIX)
  set(TARGET_FILES ${TARGET_FILES} tif_unix.c)
  # Large file support
  # This might not catch every possibility catered for by
  # AC_SYS_LARGEFILE.
  add_definitions(-D_FILE_OFFSET_BITS=64)
  set(_FILE_OFFSET_BITS 64)
else()
  set(TARGET_FILES ${TARGET_FILES} tif_win32.c)
endif()

include(${CMAKE_ROOT}/Modules/TestBigEndian.cmake)
TEST_BIG_ENDIAN(WORDS_BIGENDIAN)
set(HOST_BIGENDIAN ${WORDS_BIGENDIAN})
if(HOST_BIGENDIAN)
set(HOST_FILLORDER "FILLORDER_MSB2LSB")
else()
set(HOST_FILLORDER "FILLORDER_LSB2MSB")
endif()
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

CHECK_INCLUDE_FILES("zlib.h" HAVE_ZLIB_H)
CHECK_INCLUDE_FILES("jpeglib.h" HAVE_JPEGLIB_H)
if(HAVE_JPEGLIB_H)
  set(JPEG_SUPPORT 1)
endif()

if (BUILD_THIRDPARTY OR HAVE_ZLIB_H)
  if (BUILD_THIRDPARTY)
	include_directories( ${GROK_SOURCE_DIR}/thirdparty/include )
  elseif (HAVE_ZLIB_H)
	include_directories( ${ZLIB_INCLUDE_DIR} )
  endif()
  set(ZIP_SUPPORT 1)
  set(PIXARLOG_SUPPORT 1) # require zlib
endif()
CHECK_INCLUDE_FILES("assert.h" HAVE_ASSERT_H)
CHECK_INCLUDE_FILES("dlfcn.h" HAVE_DLFCN_H)
CHECK_INCLUDE_FILES("fcntl.h" HAVE_FCNTL_H)
CHECK_INCLUDE_FILES("inttypes.h" HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES("io.h" HAVE_IO_H)
CHECK_INCLUDE_FILES("limits.h" HAVE_LIMITS_H)
CHECK_INCLUDE_FILES("malloc.h" HAVE_MALLOC_H)
CHECK_INCLUDE_FILES("memory.h" HAVE_MEMORY_H)
CHECK_INCLUDE_FILES("search.h" HAVE_SEARCH_H)
CHECK_INCLUDE_FILES("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILES("stdlib.h" HAVE_STDLIB_H)
CHECK_INCLUDE_FILES("string.h" HAVE_STRING_H)
CHECK_INCLUDE_FILES("strings.h" HAVE_STRINGS_H)
CHECK_INCLUDE_FILES("sys/stat.h" HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES("sys/time.h" HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILES("time.h" HAVE_TIME_H)
CHECK_INCLUDE_FILES("sys/types.h" HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES("unistd.h" HAVE_UNISTD_H)
CHECK_INCLUDE_FILES("windows.h" HAVE_WINDOWS_H)
CHECK_INCLUDE_FILES("strings.h" HAVE_STRINGS_H)
CHECK_INCLUDE_FILES("ieeefp.h" HAVE_IEEEFP_H)

# wotsit ?
if( HAVE_TIME_H AND HAVE_SYS_TIME_H )
 set(TIME_WITH_SYS_TIME 1)
endif()
set(LZMA_SUPPORT 0) # ?
set(MDI_SUPPORT 1) # ?
set(STDC_HEADERS 1) # why not ?
set(DEFAULT_EXTRASAMPLE_AS_ALPHA 1)
set(CHECK_JPEG_YCBCR_SUBSAMPLING 1)
set(CCITT_SUPPORT 1)
set(DEFER_STRILE_LOAD 0)
set(HAVE_JBG_NEWLEN 0) # FIXME: jbigkit stuff
set(STRIPCHOP_DEFAULT "TIFF_STRIPCHOP")
set(STRIP_SIZE_DEFAULT 8192)
set(SUBIFD_SUPPORT 1)
set(THUNDER_SUPPORT 1)

CHECK_FUNCTION_EXISTS(getopt HAVE_GETOPT)
CHECK_FUNCTION_EXISTS(isascii HAVE_ISASCII)
CHECK_FUNCTION_EXISTS(memmove HAVE_MEMMOVE)
CHECK_FUNCTION_EXISTS(memset HAVE_MEMSET)
CHECK_FUNCTION_EXISTS(mmap HAVE_MMAP)
CHECK_FUNCTION_EXISTS(strcasecmp HAVE_STRCASECMP)
CHECK_FUNCTION_EXISTS(strchr HAVE_STRCHR)
CHECK_FUNCTION_EXISTS(strrchr HAVE_STRRCHR)
CHECK_FUNCTION_EXISTS(strstr HAVE_STRSTR)
CHECK_FUNCTION_EXISTS(strtol HAVE_STRTOL)
CHECK_FUNCTION_EXISTS(strtoul HAVE_STRTOUL)
CHECK_FUNCTION_EXISTS(strtoull HAVE_STRTOULL)

# May be inlined, so check it compiles:
check_c_source_compiles("
#include <stdio.h>
int main(void) {
  char buf[10];
  snprintf(buf, 10, \"Test %d\", 1);
  return 0;
}"
  HAVE_SNPRINTF)

if(NOT HAVE_SNPRINTF)
  add_definitions(-DNEED_LIBPORT)
endif()

# CPU bit order
set(fillorder FILLORDER_MSB2LSB)
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i.*86.*" OR
   CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "amd64.*" OR
   CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64.*")
  set(fillorder FILLORDER_LSB2MSB)
endif()
set(HOST_FILLORDER ${fillorder} CACHE STRING "Native CPU bit order")
mark_as_advanced(HOST_FILLORDER)

# CPU endianness
include(TestBigEndian)
test_big_endian(bigendian)
if (bigendian)
  set(bigendian ON)
else()
  set(bigendian OFF)
endif()
set(HOST_BIG_ENDIAN ${bigendian} CACHE STRING "Native CPU bit order")
mark_as_advanced(HOST_BIG_ENDIAN)
if (HOST_BIG_ENDIAN)
  set(HOST_BIG_ENDIAN 1)
else()
  set(HOST_BIG_ENDIAN 0)
endif()

# IEEE floating point
set(HAVE_IEEEFP 1 CACHE STRING "IEEE floating point is available")
mark_as_advanced(HAVE_IEEEFP)


# Large file support
if (UNIX)
  # This might not catch every possibility catered for by
  # AC_SYS_LARGEFILE.
  add_definitions(-D_FILE_OFFSET_BITS=64)
  set(FILE_OFFSET_BITS 64)
endif()


include(CheckTypeSize)

# Check type sizes
# NOTE: Could be replaced with C99 <stdint.h>
check_type_size("signed short" SIZEOF_SIGNED_SHORT)
check_type_size("unsigned short" SIZEOF_UNSIGNED_SHORT)
check_type_size("signed int" SIZEOF_SIGNED_INT)
check_type_size("unsigned int" SIZEOF_UNSIGNED_INT)
check_type_size("signed long" SIZEOF_SIGNED_LONG)
check_type_size("unsigned long" SIZEOF_UNSIGNED_LONG)
check_type_size("signed long long" SIZEOF_SIGNED_LONG_LONG)
check_type_size("unsigned long long" SIZEOF_UNSIGNED_LONG_LONG)
check_type_size("unsigned char *" SIZEOF_UNSIGNED_CHAR_P)

set(CMAKE_EXTRA_INCLUDE_FILES_SAVE ${CMAKE_EXTRA_INCLUDE_FILES})
set(CMAKE_EXTRA_INCLUDE_FILES ${CMAKE_EXTRA_INCLUDE_FILES} "stddef.h")
check_type_size("size_t" SIZEOF_SIZE_T)
check_type_size("ptrdiff_t" SIZEOF_PTRDIFF_T)
set(CMAKE_EXTRA_INCLUDE_FILES ${CMAKE_EXTRA_INCLUDE_FILES_SAVE})

set(TIFF_INT8_T "signed char")
set(TIFF_UINT8_T "unsigned char")

set(TIFF_INT16_T "signed short")
set(TIFF_UINT16_T "unsigned short")

if(SIZEOF_SIGNED_INT EQUAL 4)
  set(TIFF_INT32_T "signed int")
  set(TIFF_INT32_FORMAT "%d")
elseif(SIZEOF_SIGNED_LONG EQUAL 4)
  set(TIFF_INT32_T "signed long")
  set(TIFF_INT32_FORMAT "%ld")
endif()

if(SIZEOF_UNSIGNED_INT EQUAL 4)
  set(TIFF_UINT32_T "unsigned int")
  set(TIFF_UINT32_FORMAT "%u")
elseif(SIZEOF_UNSIGNED_LONG EQUAL 4)
  set(TIFF_UINT32_T "unsigned long")
  set(TIFF_UINT32_FORMAT "%lu")
endif()

if(SIZEOF_SIGNED_LONG EQUAL 8)
  set(TIFF_INT64_T "signed long")
  set(TIFF_INT64_FORMAT "%ld")
elseif(SIZEOF_SIGNED_LONG_LONG EQUAL 8)
  set(TIFF_INT64_T "signed long long")
  if (MINGW)
    set(TIFF_INT64_FORMAT "%I64d")
  else()
    set(TIFF_INT64_FORMAT "%lld")
  endif()
endif()

if(SIZEOF_UNSIGNED_LONG EQUAL 8)
  set(TIFF_UINT64_T "unsigned long")
  set(TIFF_UINT64_FORMAT "%lu")
elseif(SIZEOF_UNSIGNED_LONG_LONG EQUAL 8)
  set(TIFF_UINT64_T "unsigned long long")
  if (MINGW)
    set(TIFF_UINT64_FORMAT "%I64u")
  else()
    set(TIFF_UINT64_FORMAT "%llu")
  endif()
endif()

if(SIZEOF_UNSIGNED_INT EQUAL SIZEOF_SIZE_T)
  set(TIFF_SIZE_T "unsigned int")
  set(TIFF_SIZE_FORMAT "%u")
elseif(SIZEOF_UNSIGNED_LONG EQUAL SIZEOF_SIZE_T)
  set(TIFF_SIZE_T "unsigned long")
  set(TIFF_SIZE_FORMAT "%lu")
elseif(SIZEOF_UNSIGNED_LONG_LONG EQUAL SIZEOF_SIZE_T)
  set(TIFF_SIZE_T "unsigned long")
  if (MINGW)
    set(TIFF_SIZE_FORMAT "%I64u")
  else()
    set(TIFF_SIZE_FORMAT "%llu")
  endif()
endif()

if(SIZEOF_SIGNED_INT EQUAL SIZEOF_UNSIGNED_CHAR_P)
  set(TIFF_SSIZE_T "signed int")
  set(TIFF_SSIZE_FORMAT "%d")
elseif(SIZEOF_SIGNED_LONG EQUAL SIZEOF_UNSIGNED_CHAR_P)
  set(TIFF_SSIZE_T "signed long")
  set(TIFF_SSIZE_FORMAT "%ld")
elseif(SIZEOF_SIGNED_LONG_LONG EQUAL SIZEOF_UNSIGNED_CHAR_P)
  set(TIFF_SSIZE_T "signed long long")
  if (MINGW)
    set(TIFF_SSIZE_FORMAT "%I64d")
  else()
    set(TIFF_SSIZE_FORMAT "%lld")
  endif()
endif()

if(NOT SIZEOF_PTRDIFF_T)
  set(TIFF_PTRDIFF_T "${TIFF_SSIZE_T}")
  set(TIFF_PTRDIFF_FORMAT "${SSIZE_FORMAT}")
else()
  set(TIFF_PTRDIFF_T "ptrdiff_t")
  set(TIFF_PTRDIFF_FORMAT "%ld")
endif()

#report_values(TIFF_INT8_T TIFF_INT8_FORMAT
#              TIFF_UINT8_T TIFF_UINT8_FORMAT
#              TIFF_INT16_T TIFF_INT16_FORMAT
#              TIFF_UINT16_T TIFF_UINT16_FORMAT
#              TIFF_INT32_T TIFF_INT32_FORMAT
#              TIFF_UINT32_T TIFF_UINT32_FORMAT
#              TIFF_INT64_T TIFF_INT64_FORMAT
#              TIFF_UINT64_T TIFF_UINT64_FORMAT
#              TIFF_SSIZE_T TIFF_SSIZE_FORMAT
#              TIFF_PTRDIFF_T TIFF_PTRDIFF_FORMAT)

# Nonstandard int types
check_type_size(INT8 int8)
set(HAVE_INT8 ${INT8})
check_type_size(INT16 int16)
set(HAVE_INT16 ${INT16})
check_type_size(INT32 int32)
set(HAVE_INT32 ${INT32})

#


# universal build ?
if(APPLE)
  set(AC_APPLE_UNIVERSAL_BUILD 1)
endif()
if(UNIX)
  set(CMAKE_REQUIRED_LIBRARIES m)
  set(HAVE_LIBM 1)
endif()
CHECK_SYMBOL_EXISTS(floor "math.h" HAVE_FLOOR)
CHECK_SYMBOL_EXISTS(sqrt "math.h" HAVE_SQRT)
CHECK_SYMBOL_EXISTS(pow "math.h" HAVE_POW)
CHECK_SYMBOL_EXISTS(lfind "search.h" HAVE_LFIND)
CHECK_SYMBOL_EXISTS(setmod "io.h" HAVE_SETMODE)

# http://www.cmake.org/pipermail/cmake/2007-September/016285.html
foreach(KEYWORD "inline" "__inline__" "__inline")
  if(NOT DEFINED C_INLINE)
    try_compile(C_HAS_${KEYWORD} "${CMAKE_CURRENT_BINARY_DIR}"
       "${CMAKE_CURRENT_SOURCE_DIR}/test_inline.c"
       COMPILE_DEFINITIONS "-Dinline=${KEYWORD}")
    if(C_HAS_${KEYWORD})
      set(C_INLINE TRUE)
      set(INLINE_KEYWORD "${KEYWORD}")
    endif(C_HAS_${KEYWORD})
  endif(NOT DEFINED C_INLINE)
endforeach(KEYWORD)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tiffconf.h.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/tiffconf.h @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tif_config.h.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/tif_config.h @ONLY)

set(LIBTARGET "tiff")
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 
#
add_library(${LIBTARGET} STATIC ${TARGET_FILES})
#
set_target_properties(${LIBTARGET}
  PROPERTIES
  OUTPUT_NAME "${LIBTARGET}"
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/lib
)

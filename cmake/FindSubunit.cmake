# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindSubunit
-----------

Find the Subunit library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``Subunit::subunit``
  The Subunit library
``Subunit::cppunit_subunit``
  The Cppunit_Subunit library

Result Variables
^^^^^^^^^^^^^^^^

This module will define the following variables:

``Subunit_FOUND``
  True if the system has the Subunit library.
``Subunit_VERSION``
  The version of the Subunit library which was found.
``Subunit_INCLUDE_DIRS``
  Include directories needed to use Subunit.
``Subunit_LIBRARIES``
  Libraries needed to link to Subunit.
``Subunit_DEFINITIONS``
  Definitions to use when compiling code that uses Subunit.
``Subunit_OPTIONS``
  Options to use when compiling code that uses Subunit.

Cache Variables
^^^^^^^^^^^^^^^

This module will set the following cache variables:

``Subunit_ROOT``
  The directory containing Subunit installation, i.e.
  containing dirs ``include`` and ``lib``.
``Subunit_INCLUDE_DIR``
  The directory containing ``cache.h``.
``Subunit_LIBRARY``
  The path to the Subunit library.
``Cppunit_Subunit_LIBRARY``
  The path to the Subunit library.

Override Search
^^^^^^^^^^^^^^^

User can set the variable ``Subunit_ROOT`` on the command line
to override the search. The ``ROOT`` directory must contain
subdirectories lib and include. E.g.

  cmake -D Subunit_ROOT=<installation root>

#]=======================================================================]

if(Subunit_ROOT)
  find_path(Subunit_INCLUDE_DIR
    NAMES subunit/child.h
    PATHS ${Subunit_ROOT}
    DOC "Path to subunit header files."
  )
  find_library(Subunit_LIBRARY
    NAMES subunit
    PATHS ${Subunit_ROOT}
    DOC "Filepath to Subunit library"
  )
  find_library(Cppunit_Subunit_LIBRARY
    NAMES cppunit_subunit
    PATHS ${Subunit_ROOT}
    DOC "Filepath to Cppunit Subunit library"
  )
else()
  find_package(PkgConfig)
  pkg_check_modules(PC_subunit QUIET subunit)

  find_path(Subunit_INCLUDE_DIR
    NAMES subunit/child.h
    PATHS ${PC_Subunit_INCLUDE_DIRS}
    PATH_SUFFIXES subunit
    DOC "Path to subunit header files."
  )
  find_library(Subunit_LIBRARY
    NAMES subunit
    PATHS ${PC_Subunit_LIBRARY_DIRS}
    DOC "Filepath to Subunit library"
  )
  find_library(Cppunit_Subunit_LIBRARY
    NAMES cppunit_subunit
    PATHS ${PC_Subunit_LIBRARY_DIRS}
    DOC "Filepath to Cppunit Subunit library"
  )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Subunit
  FOUND_VAR Subunit_FOUND
  REQUIRED_VARS
    Subunit_LIBRARY
    Subunit_INCLUDE_DIR
)

# Exported variables
if(Subunit_FOUND)
  set(Subunit_LIBRARIES "${Subunit_LIBRARY} ${Cppunit_Subunit_LIBRARY}")
  set(Subunit_INCLUDE_DIRS "${Subunit_INCLUDE_DIR}")
  set(Subunit_DEFINITIONS "")
  set(Subunit_OPTIONS "${PC_Subunit_CFLAGS_OTHER}")
endif()

# Provide imported targets
if(Subunit_FOUND AND NOT TARGET Subunit::subunit)
  add_library(Subunit::subunit UNKNOWN IMPORTED)
  set_target_properties(Subunit::subunit PROPERTIES
    IMPORTED_LOCATION "${Subunit_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_Subunit_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${Subunit_INCLUDE_DIR}"
  )
endif()
if(Subunit_FOUND AND NOT TARGET Subunit::cppunit_subunit)
  add_library(Subunit::cppunit_subunit UNKNOWN IMPORTED)
  set_target_properties(Subunit::cppunit_subunit PROPERTIES
    IMPORTED_LOCATION "${Cppunit_Subunit_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_Subunit_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${Subunit_INCLUDE_DIR}"
  )
endif()


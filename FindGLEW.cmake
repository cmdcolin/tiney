include(LibFindMacros)

libfind_pkg_check_modules(GLEW_PKGCONF glew)

find_path(GLEW_INCLUDE_DIR
  NAMES GL/glew.h
  PATHS ${GLEW_PKGCONF_INCLUDE_DIRS}
)

find_library(GLEW_LIBRARY
  NAMES GLEW
  PATHS ${GLEW_PKGCONF_LIBRARY_DIRS}
)


libfind_process(GLEW)


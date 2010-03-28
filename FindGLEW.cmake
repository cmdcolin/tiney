# - Try to find GLEW
# Once done this will define
#  
#  GLEW_FOUND        - system has GLEW
#  GLEW_INCLUDE_DIR  - the GLEW include directory
#  GLEW_LIBRARY_DIR  - where the libraries are
#  GLEW_LIBRARY      - Link these to use GLEW
#   



IF (WIN32)
	IF (CYGWIN)
		FIND_PATH( GLEW_INCLUDE_DIR GL/glew.h 
			PATHS /usr/win32/include
			NO_DEFAULT_PATH)
		
		FIND_LIBRARY( GLEW_LIBRARY glew32
			PATHS /usr/win32/lib
			NO_DEFAULT_PATH)
	ELSE (CYGWIN)
		
		FIND_PATH( GLEW_INCLUDE_DIR gl/glew.h gl/wglew.h)
		
		FIND_LIBRARY( GLEW_LIBRARY glew32)

	ENDIF (CYGWIN)

else( WIN32 )
   FIND_PATH( GLEW_INCLUDE_DIR glew.h wglew.h
              PATHS /usr/local/include /usr/include
              PATH_SUFFIXES gl/ GL/ )
   SET( GLEW_NAMES glew GLEW )
   FIND_LIBRARY( GLEW_LIBRARY
                 NAMES ${GLEW_NAMES}
                 PATHS /usr/lib /usr/local/lib )
endif( WIN32 )


IF (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
   SET(GLEW_FOUND TRUE)
    SET( GLEW_LIBRARY_DIR ${GLEW_LIBRARY} )
ELSE (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
   SET( GLEW_FOUND FALSE )
   SET( GLEW_LIBRARY_DIR )
ENDIF (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)


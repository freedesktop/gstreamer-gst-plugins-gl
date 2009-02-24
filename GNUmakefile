include $(GNUSTEP_MAKEFILES)/common.make

LIBRARY_NAME = libgstopengl

libgstopengl_SUBPROJECTS = gst-libs/gst/gl gst/gl gst/gl/effects

ifeq ($(GNUSTEP_TARGET_OS), mingw32)
  libgstopengl_LIB_DIRS += \
    -LD:/workspace/glib/lib \
    -LC:/gstreamer/bin \
    -LD:/workspace/png/lib \
    -LD:/workspace/z/lib \
    -LD:/workspace/glew/bin
endif

libgstopengl_TOOL_LIBS = \
  -lglib-2.0 \
	-lgobject-2.0 \
	-lgmodule-2.0 \
	-lgthread-2.0 \
	-lgstreamer-0.10 \
	-lgstbase-0.10 \
	-lgstvideo-0.10 \
	-lgstinterfaces-0.10 \
  -lpng \
  -lz

ifeq ($(GNUSTEP_TARGET_OS), mingw32)
  libgstopengl_TOOL_LIBS += \
    -lglu32 \
	  -lopengl32 \
    -lglew32 \
    -lgdi32
endif

include $(GNUSTEP_MAKEFILES)/library.make
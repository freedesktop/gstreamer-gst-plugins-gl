include $(top_srcdir)/common/check.mak

CHECK_REGISTRY = $(top_builddir)/tests/check/test-registry.reg
TEST_FILES_DIRECTORY = $(top_srcdir)/tests/files

REGISTRY_ENVIRONMENT = \
	GST_REGISTRY=$(CHECK_REGISTRY)

TESTS_ENVIRONMENT = \
	$(REGISTRY_ENVIRONMENT)					\
	GST_PLUGIN_SYSTEM_PATH=					\
	GST_PLUGIN_PATH=$(top_builddir)/gst:$(top_builddir)/ext:$(top_builddir)/sys:$(GSTPB_PLUGINS_DIR):$(GST_PLUGINS_DIR)			\
	GST_TEST_FILES_PATH=$(TEST_FILES_DIRECTORY) \
	GST_STATE_IGNORE_ELEMENTS=""

# ths core dumps of some machines have PIDs appended
CLEANFILES = core.* test-registry.*

clean-local: clean-local-check

check_PROGRAMS = \
	generic/states \
	pipelines/simple-launch-lines \
	libs/gstglmemory \
	libs/gstglcontext \
	libs/gstglupload

VALGRIND_TO_FIX = 

TESTS = $(check_PROGRAMS)

# these tests don't even pass
# autodetect: temporarily disabled because of broken videosinks in -bad
#noinst_PROGRAMS = \
#	elements/autodetect

AM_CFLAGS = -I$(top_srcdir)/gst-libs -I$(top_builddir)/gst-libs \
    $(GST_OBJ_CFLAGS) $(GST_CHECK_CFLAGS) $(CHECK_CFLAGS) $(GST_OPTION_CFLAGS)
LDADD = $(GST_OBJ_LIBS) $(GST_CHECK_LIBS) $(CHECK_LIBS)

# valgrind testing
# videocrop disabled since it takes way too long in valgrind
VALGRIND_TESTS_DISABLE = \
	elements/videocrop \
	$(VALGRIND_TO_FIX)

SUPPRESSIONS = $(top_srcdir)/common/gst.supp


libs_gstglmemory_CFLAGS = \
	$(GL_CFLAGS) \
	$(GST_PLUGINS_GL_CFLAGS) \
	$(GST_PLUGINS_BASE_CFLAGS) \
	$(AM_CFLAGS)

libs_gstglmemory_LDADD = \
	$(top_builddir)/gst-libs/gst/gl/libgstgl-@GST_API_VERSION@.la \
	$(GST_PLUGINS_BASE_LIBS) -lgstvideo-$(GST_API_VERSION)\
	$(LDADD)

libs_gstglcontext_CFLAGS = \
	$(GL_CFLAGS) \
	$(GST_PLUGINS_GL_CFLAGS) \
	$(GST_PLUGINS_BASE_CFLAGS) \
	$(AM_CFLAGS)

libs_gstglcontext_LDADD = \
	$(top_builddir)/gst-libs/gst/gl/libgstgl-@GST_API_VERSION@.la \
	$(GST_PLUGINS_BASE_LIBS) -lgstvideo-$(GST_API_VERSION)\
	$(LDADD)

libs_gstglupload_CFLAGS = \
	$(GL_CFLAGS) \
	$(GST_PLUGINS_GL_CFLAGS) \
	$(GST_PLUGINS_BASE_CFLAGS) \
	$(AM_CFLAGS)

libs_gstglupload_LDADD = \
	$(top_builddir)/gst-libs/gst/gl/libgstgl-@GST_API_VERSION@.la \
	$(GST_PLUGINS_BASE_LIBS) -lgstvideo-$(GST_API_VERSION)\
	$(LDADD)

#include <GL/glew.h>
#include <gst/gst.h>
#include <gst/video/video.h>

#include <iostream>
#include <string>

static gboolean
bus_call (GstBus * bus, GstMessage * msg, gpointer data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_EOS:
      g_print ("End-of-stream\n");
      g_main_loop_quit (loop);
      break;
    case GST_MESSAGE_ERROR:
    {
      gchar *debug = NULL;
      GError *err = NULL;

      gst_message_parse_error (msg, &err, &debug);

      g_print ("Error: %s\n", err->message);
      g_error_free (err);

      if (debug) {
        g_print ("Debug deails: %s\n", debug);
        g_free (debug);
      }

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}

//client reshape callback
void
reshapeCallback (GLuint width, GLuint height)
{
  glViewport (0, 0, width, height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45, (gfloat) width / (gfloat) height, 0.1, 100);
  glMatrixMode (GL_MODELVIEW);
}


//client draw callback
gboolean
drawCallback (GLuint width, GLuint height, GLuint texture, GLhandleARB shader)
{
  static GLfloat xrot = 0;
  static GLfloat yrot = 0;
  static GLfloat zrot = 0;
  static GTimeVal current_time;
  static glong last_sec = current_time.tv_sec;
  static gint nbFrames = 0;

  g_get_current_time (&current_time);
  nbFrames++;

  if ((current_time.tv_sec - last_sec) >= 1) {
    std::cout << "GRPHIC FPS = " << nbFrames << std::endl;
    nbFrames = 0;
    last_sec = current_time.tv_sec;
  }

  glEnable (GL_DEPTH_TEST);

  glEnable (GL_TEXTURE_RECTANGLE_ARB);
  glBindTexture (GL_TEXTURE_RECTANGLE_ARB, texture);
  glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S,
      GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T,
      GL_CLAMP_TO_EDGE);
  glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glTranslatef (0.0f, 0.0f, -5.0f);

  glRotatef (xrot, 1.0f, 0.0f, 0.0f);
  glRotatef (yrot, 0.0f, 1.0f, 0.0f);
  glRotatef (zrot, 0.0f, 0.0f, 1.0f);

  //cube
  glBegin (GL_QUADS);
  // Front Face
  glTexCoord2f ((gfloat) width, 0.0f);
  glVertex3f (-1.0f, -1.0f, 1.0f);
  glTexCoord2f (0.0f, 0.0f);
  glVertex3f (1.0f, -1.0f, 1.0f);
  glTexCoord2f (0.0f, (gfloat) height);
  glVertex3f (1.0f, 1.0f, 1.0f);
  glTexCoord2f ((gfloat) width, (gfloat) height);
  glVertex3f (-1.0f, 1.0f, 1.0f);
  // Back Face
  glTexCoord2f (0.0f, 0.0f);
  glVertex3f (-1.0f, -1.0f, -1.0f);
  glTexCoord2f (0.0f, (gfloat) height);
  glVertex3f (-1.0f, 1.0f, -1.0f);
  glTexCoord2f ((gfloat) width, (gfloat) height);
  glVertex3f (1.0f, 1.0f, -1.0f);
  glTexCoord2f ((gfloat) width, 0.0f);
  glVertex3f (1.0f, -1.0f, -1.0f);
  // Top Face
  glTexCoord2f ((gfloat) width, (gfloat) height);
  glVertex3f (-1.0f, 1.0f, -1.0f);
  glTexCoord2f ((gfloat) width, 0.0f);
  glVertex3f (-1.0f, 1.0f, 1.0f);
  glTexCoord2f (0.0f, 0.0f);
  glVertex3f (1.0f, 1.0f, 1.0f);
  glTexCoord2f (0.0f, (gfloat) height);
  glVertex3f (1.0f, 1.0f, -1.0f);
  // Bottom Face
  glTexCoord2f ((gfloat) width, 0.0f);
  glVertex3f (-1.0f, -1.0f, -1.0f);
  glTexCoord2f (0.0f, 0.0f);
  glVertex3f (1.0f, -1.0f, -1.0f);
  glTexCoord2f (0.0f, (gfloat) height);
  glVertex3f (1.0f, -1.0f, 1.0f);
  glTexCoord2f ((gfloat) width, (gfloat) height);
  glVertex3f (-1.0f, -1.0f, 1.0f);
  // Right face
  glTexCoord2f (0.0f, 0.0f);
  glVertex3f (1.0f, -1.0f, -1.0f);
  glTexCoord2f (0.0f, (gfloat) height);
  glVertex3f (1.0f, 1.0f, -1.0f);
  glTexCoord2f ((gfloat) width, (gfloat) height);
  glVertex3f (1.0f, 1.0f, 1.0f);
  glTexCoord2f ((gfloat) width, 0.0f);
  glVertex3f (1.0f, -1.0f, 1.0f);
  // Left Face
  glTexCoord2f ((gfloat) width, 0.0f);
  glVertex3f (-1.0f, -1.0f, -1.0f);
  glTexCoord2f (0.0f, 0.0f);
  glVertex3f (-1.0f, -1.0f, 1.0f);
  glTexCoord2f (0.0f, (gfloat) height);
  glVertex3f (-1.0f, 1.0f, 1.0f);
  glTexCoord2f ((gfloat) width, (gfloat) height);
  glVertex3f (-1.0f, 1.0f, -1.0f);
  glEnd ();

  xrot += 0.3f;
  yrot += 0.2f;
  zrot += 0.4f;

  //return TRUE causes a postRedisplay
  return FALSE;
}


//equivalent command line: 
//gst-launch-0.10 videotestsrc num_buffers=400 ! glupload ! gldownload ! 
//ffenc_mpeg4 ! avimux ! filesink location="record.avi"
// or
//gst-launch-0.10 videotestsrc num_buffers=400 ! glupload !  video/x-raw-gl, width=320, height=240 ! glfiltercube ! video/x-raw-gl, width=720, height=576 ! 
//gldownload ! ffenc_mpeg4 ! avimux ! filesink location="record.avi"
gint
main (gint argc, gchar * argv[])
{
  GstStateChangeReturn ret;
  GstElement *pipeline, *videosrc, *glupload, *glfilterapp, *gldownload,
      *ffenc_mpeg4, *avimux, *filesink;
  GMainLoop *loop;
  GstBus *bus;

  /* initialization */
  gst_init (&argc, &argv);
  loop = g_main_loop_new (NULL, FALSE);

  /* create elements */
  pipeline = gst_pipeline_new ("pipeline");

  /* watch for messages on the pipeline's bus (note that this will only
   * work like this when a GLib main loop is running) */
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, bus_call, loop);
  gst_object_unref (bus);

  /* create elements */
  videosrc = gst_element_factory_make ("videotestsrc", "videotestsrc0");
  glupload = gst_element_factory_make ("glupload", "glupload0");
  glfilterapp = gst_element_factory_make ("glfilterapp", "glfilterapp0");
  gldownload = gst_element_factory_make ("gldownload", "gldownload0");
  ffenc_mpeg4 = gst_element_factory_make ("ffenc_mpeg4", "ffenc_mpeg40");
  avimux = gst_element_factory_make ("avimux", "avimux0");
  filesink = gst_element_factory_make ("filesink", "filesink0");


  if (!videosrc || !glupload || !glfilterapp || !gldownload || !ffenc_mpeg4
      || !avimux || !filesink) {
    g_print ("one element could not be found \n");
    return -1;
  }

  /* change video source caps */
  GstCaps *caps = gst_caps_new_simple ("video/x-raw-yuv",
      "format", GST_TYPE_FOURCC, GST_MAKE_FOURCC ('U', 'Y', 'V', 'Y'),
      "width", G_TYPE_INT, 320,
      "height", G_TYPE_INT, 240,
      "framerate", GST_TYPE_FRACTION, 25, 1,
      NULL);

  /* change video source caps */
  GstCaps *outcaps = gst_caps_new_simple ("video/x-raw-yuv",
      "width", G_TYPE_INT, 640,
      "height", G_TYPE_INT, 480,
      NULL);

  /* configure elements */
  g_object_set (G_OBJECT (videosrc), "num-buffers", 400, NULL);
  g_object_set (G_OBJECT (glfilterapp), "client-reshape-callback",
      reshapeCallback, NULL);
  g_object_set (G_OBJECT (glfilterapp), "client-draw-callback", drawCallback,
      NULL);
  g_object_set (G_OBJECT (filesink), "location", "record.avi", NULL);

  /* add elements */
  gst_bin_add_many (GST_BIN (pipeline), videosrc, glupload, glfilterapp,
      gldownload, ffenc_mpeg4, avimux, filesink, NULL);

  /* link elements */
  gboolean link_ok = gst_element_link_filtered (videosrc, glupload, caps);
  gst_caps_unref (caps);
  if (!link_ok) {
    g_warning ("Failed to link videosrc to glupload!\n");
    return -1;
  }
  if (!gst_element_link_many (glupload, glfilterapp, gldownload, NULL)) {
    g_print ("Failed to link one or more elements!\n");
    return -1;
  }
  link_ok = gst_element_link_filtered (gldownload, ffenc_mpeg4, outcaps);
  gst_caps_unref (outcaps);
  if (!link_ok) {
    g_warning ("Failed to link glvideomaker to ffenc_mpeg4!\n");
    return -1;
  }
  if (!gst_element_link_many (ffenc_mpeg4, avimux, filesink, NULL)) {
    g_print ("Failed to link one or more elements!\n");
    return -1;
  }


  /* run */
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_print ("Failed to start up pipeline!\n");

    /* check if there is an error message with details on the bus */
    GstMessage *msg = gst_bus_poll (bus, GST_MESSAGE_ERROR, 0);
    if (msg) {
      GError *err = NULL;

      gst_message_parse_error (msg, &err, NULL);
      g_print ("ERROR: %s\n", err->message);
      g_error_free (err);
      gst_message_unref (msg);
    }
    return -1;
  }

  g_main_loop_run (loop);

  /* clean up */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);

  return 0;

}

#include <gst/gst.h>
#include <iostream>
#include <sstream>

GstElement *pipeline = NULL;

typedef struct stream_props{
  int xpos;
  int ypos;
  int width;
  int height;
  int alpha;
  int top;
  int bottom;
  int left;
  int right;
} stream_props_t;


typedef struct layout{
  std::string name;
  int streams;
  stream_props_t stream1;
  stream_props_t stream2;
  stream_props_t stream3;
  stream_props_t stream4;
} layout_t;

static layout_t layouts[] = {
  {"empty",
   0,
   {0, 0, 1024, 768, 1, 0, 0, 0, 0},
   {0, 0, 1, 1, 2, 0, 0, 0, 0},
   {0, 0, 1, 1, 2, 0, 0, 0, 0},
   {0, 0, 1, 1, 2, 0, 0, 0, 0}
  },
  {"single",
   1,
   {0, 0, 1024, 768, 1, 0, 0, 0, 0},
   {0, 0, 1, 1, 2, 0, 0, 0, 0},
   {0, 0, 1, 1, 3, 0, 0, 0, 0},
   {0, 0, 1, 1, 3, 0, 0, 0, 0}
  },
  {"side-by-side",
   2,
   {0, 0, 512, 768, 1, 0, 0, 256, 256},
   {512, 0, 512, 768, 1, 0, 0, 256, 256},
   {0, 0, 1, 1, 0, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0, 0}
  },
  {"pip2_1",
   2,
   {0, 0, 1024, 768, 1, 0, 0, 0, 0},
   {600, 100, 360, 240, 2, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0, 0}
  },
  {"pip2_2",
   2,
   {600, 100, 360, 240, 2, 0, 0, 0, 0},
   {0, 0, 1024, 768, 1, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0, 0}
  },
  {"3",
   3,
   {0, 0, 1024, 768, 1, 0, 0, 0, 0},
   {1024-360, 0, 360, 240, 2, 0, 0, 0, 0},
   {1024-360, 250, 360, 240, 2, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0, 0}
  },
  {"4_pined_1",
   4,
   {0, 0, 1024, 768, 1, 0, 0, 0, 0},
   {1024-360, 0, 360, 240, 2, 0, 0, 0, 0},
   {1024-360, 240, 360, 240, 2, 0, 0, 0, 0},
   {1024-360, 480, 360, 240, 2, 0, 0, 0, 0}
  },
  {"4_mosaic",
   4,
   {0, 0, 512, 360, 1, 0, 0, 0, 0},
   {512, 0, 512, 360, 1, 0, 0, 0, 0},
   {0, 360, 512, 360, 1, 0, 0, 0, 0},
   {512, 360, 512, 360, 1, 0, 0, 0, 0}
  }
};

static int sources = 0;
char src1[] = "1.avi";

const layout_t& get_layout(const std::string& name){
  for(int i=0;i<sizeof(layouts)/sizeof(layout_t);++i){
    if(layouts[i].name == name){
      return layouts[i];
    }
  }
  throw std::runtime_error("undefined layout");
}

gboolean set_layout(const std::string& name){
  try{
    auto l = get_layout(name);
    GstElement* mix = gst_bin_get_by_name(GST_BIN(pipeline), "mix");
    GstPad* pad = gst_element_get_static_pad(mix, "sink_0");
    g_object_set(pad, "xpos", l.stream1.xpos, NULL);
    g_object_set(pad, "ypos", l.stream1.ypos, NULL);
    g_object_set(pad, "zorder", l.stream1.alpha, NULL);
    gst_object_unref(pad);

    pad = gst_element_get_static_pad(mix, "sink_1");
    g_object_set(pad, "xpos", l.stream2.xpos, NULL);
    g_object_set(pad, "ypos", l.stream2.ypos, NULL);
    g_object_set(pad, "zorder", l.stream2.alpha, NULL);
    gst_object_unref(pad);
    pad = gst_element_get_static_pad(mix, "sink_2");
    g_object_set(pad, "xpos", l.stream3.xpos, NULL);
    g_object_set(pad, "ypos", l.stream3.ypos, NULL);
    g_object_set(pad, "zorder", l.stream3.alpha, NULL);
    gst_object_unref(pad);
    pad = gst_element_get_static_pad(mix, "sink_3");
    g_object_set(pad, "xpos", l.stream4.xpos, NULL);
    g_object_set(pad, "ypos", l.stream4.ypos, NULL);
    g_object_set(pad, "zorder", l.stream4.alpha, NULL);
    gst_object_unref(pad);
    gst_object_unref(mix);

    GstElement* caps = gst_bin_get_by_name(GST_BIN(pipeline), "caps1");
    GstCaps *filtercaps = NULL;
    filtercaps = gst_caps_new_simple ("video/x-raw", "width", G_TYPE_INT, l.stream1.width, "height", G_TYPE_INT, l.stream1.height, NULL);
    g_object_set(caps, "caps", filtercaps, NULL);
    gst_caps_unref(filtercaps);
    gst_object_unref(caps);
    GstElement* crop = gst_bin_get_by_name(GST_BIN(pipeline), "crop1");
    g_object_set(crop, "top", l.stream1.top, NULL);
    g_object_set(crop, "bottom", l.stream1.bottom, NULL);
    g_object_set(crop, "left", l.stream1.left, NULL);
    g_object_set(crop, "right", l.stream1.right, NULL);
    gst_object_unref(crop);


    caps = gst_bin_get_by_name(GST_BIN(pipeline), "caps2");
    filtercaps = gst_caps_new_simple ("video/x-raw", "width", G_TYPE_INT, l.stream2.width, "height", G_TYPE_INT, l.stream2.height, NULL);
    g_object_set(caps, "caps", filtercaps, NULL);
    gst_caps_unref(filtercaps);
    gst_object_unref(caps);
    crop = gst_bin_get_by_name(GST_BIN(pipeline), "crop2");
    g_object_set(crop, "top", l.stream2.top, NULL);
    g_object_set(crop, "bottom", l.stream2.bottom, NULL);
    g_object_set(crop, "left", l.stream2.left, NULL);
    g_object_set(crop, "right", l.stream2.right, NULL);
    gst_object_unref(crop);

    caps = gst_bin_get_by_name(GST_BIN(pipeline), "caps3");
    filtercaps = gst_caps_new_simple ("video/x-raw", "width", G_TYPE_INT, l.stream3.width, "height", G_TYPE_INT, l.stream3.height, NULL);
    g_object_set(caps, "caps", filtercaps, NULL);
    gst_caps_unref(filtercaps);
    gst_object_unref(caps);
    crop = gst_bin_get_by_name(GST_BIN(pipeline), "crop3");
    g_object_set(crop, "top", l.stream3.top, NULL);
    g_object_set(crop, "bottom", l.stream3.bottom, NULL);
    g_object_set(crop, "left", l.stream3.left, NULL);
    g_object_set(crop, "right", l.stream3.right, NULL);
    gst_object_unref(crop);

    caps = gst_bin_get_by_name(GST_BIN(pipeline), "caps4");
    filtercaps = gst_caps_new_simple ("video/x-raw", "width", G_TYPE_INT, l.stream4.width, "height", G_TYPE_INT, l.stream4.height, NULL);
    g_object_set(caps, "caps", filtercaps, NULL);
    gst_caps_unref(filtercaps);
    gst_object_unref(caps);
    crop = gst_bin_get_by_name(GST_BIN(pipeline), "crop4");
    g_object_set(crop, "top", l.stream4.top, NULL);
    g_object_set(crop, "bottom", l.stream4.bottom, NULL);
    g_object_set(crop, "left", l.stream4.left, NULL);
    g_object_set(crop, "right", l.stream4.right, NULL);
    gst_object_unref(crop);

  }catch(std::runtime_error& e){
    std::cerr << e.what() << std::endl;
    return FALSE;
  }
  return TRUE;
}

static GstPadProbeReturn event_probe_cb(GstPad *pad, GstPadProbeInfo *info, gpointer data){
  std::cerr << "222" << std::endl;
  if(GST_EVENT_TYPE(GST_PAD_PROBE_INFO_DATA(info)) != GST_EVENT_EOS){
    return GST_PAD_PROBE_PASS;
  }
  std::cerr << "111" << std::endl;
  gst_pad_remove_probe(pad, GST_PAD_PROBE_INFO_ID(info));
  std::stringstream s, ss, sss;
  s << "src" << sources+1;
  ss << "caps" << sources+1 << "in";
  GstElement *srcOld = gst_bin_get_by_name(GST_BIN(pipeline), s.str().c_str());
  if(srcOld){
    GstElement *decoder = gst_bin_get_by_name(GST_BIN(pipeline), ss.str().c_str());
    std::cerr << "111" << std::endl;
    gst_element_unlink(srcOld, decoder);
    gst_bin_remove(GST_BIN(pipeline), srcOld);
    GstElement *srcNew = gst_element_factory_make("filesrc", s.str().c_str());
    g_object_set(srcNew, "location", "1.avi", NULL);
    //      g_signal_connect(G_OBJECT(rtspsrcNew), "pad-added", G_CALLBACK(on_rtsp_pad_added), data);
    gst_bin_add(GST_BIN(pipeline), srcNew);
    gst_element_link_many(srcNew, decoder, NULL);
    gst_element_set_state(GST_ELEMENT(srcNew), GST_STATE_PLAYING);
    std::cerr << "333" << std::endl;
    ++sources;
    return GST_PAD_PROBE_DROP;
  }
  return GST_PAD_PROBE_DROP;
}

static GstPadProbeReturn pad_probe_cb (GstPad * pad, GstPadProbeInfo * info, gpointer user_data){
  gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));
  std::stringstream s, ss, sss;
  s << "decoder" << sources+1;
  ss << "caps" << sources+1;
  GstElement* caps = gst_bin_get_by_name(GST_BIN(pipeline), "vc_out");
  GstPad* srcpad = gst_element_get_static_pad (caps, "src");
  gst_pad_add_probe (srcpad, (GstPadProbeType)(GST_PAD_PROBE_TYPE_BLOCK | GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM), event_probe_cb, user_data, NULL);
  //  gst_object_unref (srcpad);
  //  gst_object_unref (caps);
  //  gst_object_unref (srcpad);
  GstElement* decoder = gst_bin_get_by_name(GST_BIN(pipeline), "caps1in");
  GstPad* sinkpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_send_event(sinkpad, gst_event_new_eos());
  //  gst_object_unref (sinkpad);
  //  gst_object_unref (decoder);
  decoder = gst_bin_get_by_name(GST_BIN(pipeline), "decoder2");
  sinkpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_send_event(sinkpad, gst_event_new_eos());
  //  gst_object_unref (sinkpad);
  //  gst_object_unref (decoder);
  decoder = gst_bin_get_by_name(GST_BIN(pipeline), "decoder3");
  sinkpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_send_event(sinkpad, gst_event_new_eos());
  //  gst_object_unref (sinkpad);
  //  gst_object_unref (decoder);
  decoder = gst_bin_get_by_name(GST_BIN(pipeline), "decoder4");
  sinkpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_send_event(sinkpad, gst_event_new_eos());
  //  gst_object_unref (sinkpad);
  //  gst_object_unref (decoder);
  return GST_PAD_PROBE_OK;
}

gboolean add_src(char* path){
  if(sources == 4){
    return FALSE;
  }
  std::stringstream s, ss, sss;
  ss << "caps" << sources+1 << "in";
  GstElement* decoder = gst_bin_get_by_name(GST_BIN(pipeline), ss.str().c_str());
  GstPad* blockpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_add_probe (blockpad, GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, pad_probe_cb, &path, NULL);
  return TRUE;
}

int current_layout = 0;

gboolean changer_cb(gpointer user_data){
  ++current_layout;
  if(current_layout > (sizeof(layouts)/sizeof(layout_t)-1)){
    current_layout = 0;
  }
  std::cerr << layouts[current_layout].name << std::endl;
  set_layout(layouts[current_layout].name);
  return TRUE;
}

int main (int argc, char **argv){
  gst_init(&argc, &argv);
  GMainLoop *loop = g_main_loop_new (NULL, FALSE);


  GError *error = NULL;
  pipeline = gst_parse_launch("videomixer name=mix background=2 "
                              "sink_0::alpha=1.0 "
                              "sink_0::ypos=0 "
                              "sink_0::xpos=0 "
                              "sink_1::alpha=1.0 "
                              "sink_1::ypos=0 "
                              "sink_1::xpos=664 "
                              "sink_2::alpha=1.0 "
                              "sink_2::ypos=240 "
                              "sink_2::xpos=664 "
                              "sink_3::alpha=1.0 "
                              "sink_3::ypos=480 "
                              "sink_3::xpos=664 "
                              "! videoconvert ! autovideosink "
                              //                              "rtspsrc location=\"rtsp://192.168.0.161:554/1\"  name=src1 "
                              "filesrc location=1.avi name=src1 "
                              "! decodebin name=decoder1 ! videoconvert ! videoscale "
                              "! videocrop top=0 left=0 right=0 bottom=0 name=crop1 "
                              "! capsfilter name=caps1 "
                              "! mix.sink_0 "
                              //                              "rtspsrc location=rtsp://192.168.0.162:554/1 name=src2 "
                              "filesrc location=2.avi name=src2 "
                              "! decodebin name=decoder2 ! videoconvert ! videoscale "
                              "! videocrop top=0 left=0 right=0 bottom=0 name=crop2 "
                              "! capsfilter name=caps2 "
                              "! mix.sink_1 "
                              //                              "rtspsrc location=rtsp://192.168.0.163:554/1 name=src3 "
                              "filesrc location=3.avi name=src3 "
                              "! decodebin name=decoder3 ! videoconvert ! videoscale "
                              "! videocrop top=0 left=0 right=0 bottom=0 name=crop3 "
                              "! capsfilter name=caps3 "
                              "! mix.sink_2 "
                              //                              "rtspsrc location=rtsp://192.168.0.161:554/1 name=src4 "
                              "filesrc location=4.avi name=src4 "
                              "! decodebin name=decoder4 ! videoconvert ! videoscale "
                              "! videocrop top=0 left=0 right=0 bottom=0 name=crop4 "
                              "! capsfilter name=caps4 "
                              "! mix.sink_3", &error);
  if (error) {
    std::cout << error->message << std::endl;
    return 1;
  }
  set_layout("empty");
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  g_timeout_add_seconds (5, changer_cb, loop);
  g_main_loop_run (loop);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);

  return 0;
}

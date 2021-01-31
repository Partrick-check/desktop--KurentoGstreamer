#include "gstmnscmixer.h"

#include <kurento/commons/kmsagnosticcaps.h>
#include <kurento/commons/kmshubport.h>
#include <kurento/commons/kmsloop.h>
#include <kurento/commons/kmsrefstruct.h>
#include <kurento/commons/kms-core-marshal.h>
#include <math.h>

#define GST_MNSCMIXER_LOCK(mixer) (g_rec_mutex_lock(&((Gstmnscmixer*)(mixer))->priv->mutex))
#define GST_MNSCMIXER_UNLOCK(mixer) (g_rec_mutex_unlock(&((Gstmnscmixer*)(mixer))->priv->mutex))

GST_DEBUG_CATEGORY_STATIC(gst_mnscmixer_debug_category);
#define GST_CAT_DEFAULT gst_mnscmixer_debug_category
#define LATENCY 600
#define PLUGIN_NAME "mnscmixer"

#define GST_MNSCMIXER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GST_TYPE_MNSCMIXER, gst_mnscmixer_Private))

static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE("sink_", GST_PAD_SINK, GST_PAD_SOMETIMES, GST_STATIC_CAPS(KMS_AGNOSTIC_RAW_VIDEO_CAPS));

struct _gst_mnscmixer_Private{
  GstElement *videomixer;
  GHashTable *ports;
  GstElement *mixer_video_agnostic;
  KmsLoop *loop;
  GRecMutex mutex;
  gint n_elems;
  gint focus;
  gint output_width, output_height;
};

G_DEFINE_TYPE_WITH_CODE(Gstmnscmixer, gst_mnscmixer, KMS_TYPE_BASE_HUB, GST_DEBUG_CATEGORY_INIT(gst_mnscmixer_debug_category, PLUGIN_NAME, 0, "debug category for mnscmixer element"));

enum
  {
    SIGNAL_FOCUS,
    LAST_SIGNAL
  };

static guint obj_signals[LAST_SIGNAL] = { 0 };

typedef struct _gst_mnscmixer_Data{
  KmsRefStruct parent;
  gint id;
  Gstmnscmixer *mixer;
  GstElement* capsfilter;
  GstElement *videocrop;
  GstElement *tee;
  GstElement *fakesink;
  gboolean input;
  gboolean removing;
  gboolean eos_managed;
  gulong probe_id;
  gulong link_probe_id;
  gulong latency_probe_id;
  GstPad *tee_sink_pad;
  GstPad *video_mixer_pad;
} gst_mnscmixer_Data;

#define GST_MNSCMIXER_REF(data) kms_ref_struct_ref(KMS_REF_STRUCT_CAST(data))
#define GST_MNSCMIXER_UNREF(data) kms_ref_struct_unref(KMS_REF_STRUCT_CAST(data))

static void gst_destroy_mncsmixer_data(gst_mnscmixer_Data * data){
  g_slice_free(gst_mnscmixer_Data, data);
}

static gst_mnscmixer_Data *create_gst_mnscmixer_data(){
  gst_mnscmixer_Data* data;
  data = g_slice_new0(gst_mnscmixer_Data);
  kms_ref_struct_init(KMS_REF_STRUCT_CAST(data), (GDestroyNotify)gst_destroy_mncsmixer_data);
  return data;
}

static gint compare_port_data(gconstpointer a, gconstpointer b){
  gst_mnscmixer_Data* port_data_a = (gst_mnscmixer_Data*)a;
  gst_mnscmixer_Data* port_data_b = (gst_mnscmixer_Data*)b;
  return port_data_a->id-port_data_b->id;
}

static void gst_mnscmixer_recalculate_sizes(gpointer data){
  GST_DEBUG("gst_mnscmixer_recalculate_sizes");
  Gstmnscmixer *self = GST_MNSCMIXER(data);
  GstCaps *filtercaps;
  gint width, height, top, left, counter, n_columns, n_rows;
  GList *l;
  GList *values = g_hash_table_get_values(self->priv->ports);
  if(self->priv->n_elems <= 0){
    return;
  }
  GST_DEBUG("gst_mnscmixer_recalculate_sizes2");
  counter = 0;
  values = g_list_sort(values, compare_port_data);
  n_columns = (gint) ceil(sqrt(self->priv->n_elems));
  n_rows = (gint) ceil((float)self->priv->n_elems / (float)n_columns);
  GST_DEBUG_OBJECT(self, "columns %d rows %d", n_columns, n_rows);
  width = self->priv->output_width / n_columns;
  height = self->priv->output_height / n_rows;
  for(l = values; l != NULL; l = l->next){
    gst_mnscmixer_Data* port_data = l->data;
    if(port_data->input == FALSE){
      continue;
    }
    if(self->priv->n_elems == 2){
      g_object_set(G_OBJECT(port_data->videocrop), "left", self->priv->output_width/4, "right", self->priv->output_width/4, NULL);
    }
    else{
      g_object_set(G_OBJECT(port_data->videocrop), "left", 0, "right", 0, NULL);
    }
    filtercaps = gst_caps_new_simple("video/x-raw", "width", G_TYPE_INT, width, "height", G_TYPE_INT, height, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1, NULL);
    g_object_set(port_data->capsfilter, "caps", filtercaps, NULL);
    gst_caps_unref(filtercaps);
    top = ((counter / n_columns) * height);
    left = ((counter % n_columns) * width);
    g_object_set(port_data->video_mixer_pad, "xpos", left, "ypos", top, "alpha", 1.0, NULL);
    counter++;
    GST_DEBUG_OBJECT(self, "counter %d id_port %d ", counter, port_data->id);
    GST_DEBUG_OBJECT(self, "top %d left %d width %d height %d", top, left, width, height);
  }
  g_list_free(values);
}

static void gst_mnscmixer_recalculate_sizes_a(gpointer data){
  GST_DEBUG("gst_mnscmixer_recalculate_sizes_a");
  Gstmnscmixer *self = GST_MNSCMIXER(data);
  if(self->priv->focus == 0){
    return gst_mnscmixer_recalculate_sizes(data);
  }
  GstCaps *filtercaps;
  gint width, height, top, left, counter, counter2, n_columns, n_rows;
  GList *l;
  GList *values = g_hash_table_get_values(self->priv->ports);
  if(self->priv->n_elems <= 0){
    return;
  }
  GST_DEBUG("gst_mnscmixer_recalculate_sizes2");
  counter = 0;
  counter2 = 0;
  values = g_list_sort(values, compare_port_data);
  n_columns = 1;
  n_rows = self->priv->n_elems-1;
  GST_DEBUG_OBJECT(self, "columns %d rows %d", n_columns, n_rows);
  width = self->priv->output_width / 4;
  height = self->priv->output_height / 4;
  for(l = values; l != NULL; l = l->next){
    gst_mnscmixer_Data* port_data = l->data;
    if(port_data->input == FALSE){
      continue;
    }
    g_object_set(G_OBJECT(port_data->videocrop), "left", 0, "right", 0, NULL);
    if(counter == (self->priv->focus -1)){
      filtercaps = gst_caps_new_simple("video/x-raw", "width", G_TYPE_INT, self->priv->output_width, "height", G_TYPE_INT, self->priv->output_height, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1, NULL);
      g_object_set(port_data->capsfilter, "caps", filtercaps, NULL);
      gst_caps_unref(filtercaps);
      g_object_set(port_data->video_mixer_pad, "xpos", 0, "ypos", 0, "alpha", 1.0, "zorder", 1, NULL);
      GST_DEBUG_OBJECT(self, "counter %d id_port %d ", counter, port_data->id);
      GST_DEBUG_OBJECT(self, "top %d left %d width %d height %d", top, left, width, height);
    }else{
      filtercaps = gst_caps_new_simple("video/x-raw", "width", G_TYPE_INT, width, "height", G_TYPE_INT, height, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1, NULL);
      g_object_set(port_data->capsfilter, "caps", filtercaps, NULL);
      gst_caps_unref(filtercaps);
      top = counter2 * height;
      left = self->priv->output_width - width;
      g_object_set(port_data->video_mixer_pad, "xpos", left, "ypos", top, "alpha", 1.0, "zorder", 2, NULL);
      counter2++;
      GST_DEBUG_OBJECT(self, "counter %d id_port %d ", counter, port_data->id);
      GST_DEBUG_OBJECT(self, "top %d left %d width %d height %d", top, left, width, height);
    }
    counter++;
  }
  g_list_free(values);
}


static gboolean remove_elements_from_pipeline(gst_mnscmixer_Data* port_data){
  Gstmnscmixer *self = port_data->mixer;
  GST_MNSCMIXER_LOCK(self);
  gst_element_unlink(port_data->capsfilter, self->priv->videomixer);
  if(port_data->latency_probe_id > 0){
    gst_pad_remove_probe(port_data->video_mixer_pad, port_data->latency_probe_id);
    port_data->latency_probe_id = 0;
  }
  if(port_data->video_mixer_pad != NULL){
    gst_element_release_request_pad(self->priv->videomixer, port_data->video_mixer_pad);
    g_object_unref(port_data->video_mixer_pad);
    port_data->video_mixer_pad = NULL;
  }
  gst_bin_remove_many(GST_BIN(self), g_object_ref(port_data->capsfilter), g_object_ref(port_data->tee), g_object_ref(port_data->fakesink), g_object_ref(port_data->videocrop), NULL);

  kms_base_hub_unlink_video_src(KMS_BASE_HUB(self), port_data->id);
  kms_base_hub_unlink_data_src(KMS_BASE_HUB (self), port_data->id);
  GST_MNSCMIXER_UNLOCK(self);
  gst_element_set_state(port_data->capsfilter, GST_STATE_NULL);
  gst_element_set_state (port_data->tee, GST_STATE_NULL);
  gst_element_set_state (port_data->fakesink, GST_STATE_NULL);
  gst_element_set_state (port_data->videocrop, GST_STATE_NULL);

  g_object_unref(port_data->capsfilter);
  g_object_unref (port_data->tee);
  g_object_unref (port_data->videocrop);
  g_object_unref (port_data->fakesink);
  g_object_unref (port_data->tee_sink_pad);


  port_data->tee_sink_pad = NULL;
  port_data->capsfilter = NULL;
  port_data->tee = NULL;
  port_data->fakesink = NULL;
  port_data->videocrop = NULL;

  return G_SOURCE_REMOVE;
}

static GstPadProbeReturn cb_EOS_received(GstPad* pad, GstPadProbeInfo* info, gpointer data){
  gst_mnscmixer_Data* port_data = (gst_mnscmixer_Data*)data;
  Gstmnscmixer* self = port_data->mixer;

  if (GST_EVENT_TYPE (gst_pad_probe_info_get_event (info)) != GST_EVENT_EOS) {
    return GST_PAD_PROBE_OK;
  }

  GST_MNSCMIXER_LOCK (self);

  if (!port_data->removing) {
    port_data->eos_managed = TRUE;
    GST_MNSCMIXER_UNLOCK (self);
    return GST_PAD_PROBE_OK;
  }

  if (port_data->probe_id > 0) {
    gst_pad_remove_probe(pad, port_data->probe_id);
    port_data->probe_id = 0;
  }

  GST_MNSCMIXER_UNLOCK(self);

  GstEvent* event = gst_event_new_eos();
  gst_pad_send_event(pad, event);

  kms_loop_idle_add_full(self->priv->loop, G_PRIORITY_DEFAULT, (GSourceFunc)remove_elements_from_pipeline, GST_MNSCMIXER_REF(port_data), (GDestroyNotify)kms_ref_struct_unref);
  return GST_PAD_PROBE_OK;
}

static GstPadProbeReturn
cb_latency (GstPad * pad, GstPadProbeInfo * info, gpointer data)
{
  if (GST_QUERY_TYPE (GST_PAD_PROBE_INFO_QUERY (info)) != GST_QUERY_LATENCY) {
    return GST_PAD_PROBE_OK;
  }

  GST_LOG_OBJECT (pad, "Modifing latency query. New latency %" G_GUINT64_FORMAT,
      (guint64) (LATENCY * GST_MSECOND));

  gst_query_set_latency (GST_PAD_PROBE_INFO_QUERY (info),
      TRUE, 0, LATENCY * GST_MSECOND);

  return GST_PAD_PROBE_HANDLED;
}

static void gst_mnscmixer_port_data_destroy(gpointer data){
  gst_mnscmixer_Data *port_data = (gst_mnscmixer_Data*)data;
  Gstmnscmixer* self = port_data->mixer;
  GST_MNSCMIXER_LOCK(self);
  port_data->removing = TRUE;
  kms_base_hub_unlink_video_sink(KMS_BASE_HUB (self), port_data->id);
  if(port_data->input){
    GstEvent *event;
    gboolean result;
    GstPad *pad;
    if(port_data->capsfilter == NULL){
      GST_MNSCMIXER_UNLOCK (self);
      return;
    }
    pad = gst_element_get_static_pad(port_data->capsfilter, "sink");
    if(pad == NULL){
      GST_MNSCMIXER_UNLOCK(self);
      return;
    }
    if(!GST_OBJECT_FLAG_IS_SET(pad, GST_PAD_FLAG_EOS)){
      if(GST_PAD_IS_FLUSHING(pad)) {
        gst_pad_send_event(pad, gst_event_new_flush_stop(FALSE));
      }
      event = gst_event_new_eos();
      result = gst_pad_send_event(pad, event);
      if(port_data->input && self->priv->n_elems > 0){
        port_data->input = FALSE;
        self->priv->n_elems--;
        self->priv->focus = 0;
        gst_mnscmixer_recalculate_sizes_a(self);
      }
      GST_MNSCMIXER_UNLOCK(self);
      if(!result){
        GST_WARNING("EOS event did not send");
      }
    } else {
      gboolean remove = FALSE;
      remove = port_data->eos_managed;
      GST_MNSCMIXER_UNLOCK(self);
      if(remove){
        kms_loop_idle_add_full(self->priv->loop, G_PRIORITY_DEFAULT, (GSourceFunc)remove_elements_from_pipeline, GST_MNSCMIXER_REF(port_data), (GDestroyNotify)kms_ref_struct_unref);
      }
    }
    gst_element_unlink(port_data->videocrop, port_data->capsfilter);
    gst_element_unlink(port_data->capsfilter, port_data->tee);
    g_object_unref(pad);
  } else {
    if(port_data->probe_id > 0){
      gst_pad_remove_probe(port_data->video_mixer_pad, port_data->probe_id);
    }
    if(port_data->latency_probe_id > 0){
      gst_pad_remove_probe(port_data->tee_sink_pad, port_data->latency_probe_id);
    }
    GST_MNSCMIXER_UNLOCK (self);
    gst_element_unlink(port_data->videocrop, port_data->capsfilter);
    gst_element_unlink(port_data->capsfilter, port_data->tee);
    gst_element_unlink(port_data->tee, port_data->fakesink);

    gst_bin_remove(GST_BIN(self), g_object_ref(port_data->capsfilter));
    gst_element_set_state(port_data->capsfilter, GST_STATE_NULL);
    g_object_unref(port_data->capsfilter);
    port_data->capsfilter = NULL;

    gst_bin_remove(GST_BIN(self), g_object_ref(port_data->videocrop));
    gst_element_set_state(port_data->videocrop, GST_STATE_NULL);
    g_object_unref(port_data->videocrop);
    port_data->videocrop = NULL;

    gst_bin_remove(GST_BIN(self), g_object_ref(port_data->tee));
    gst_element_set_state(port_data->tee, GST_STATE_NULL);
    g_object_unref(port_data->tee);
    port_data->tee = NULL;

    gst_bin_remove(GST_BIN(self), g_object_ref(port_data->fakesink));
    gst_element_set_state(port_data->fakesink, GST_STATE_NULL);
    g_object_unref(port_data->fakesink);
    port_data->fakesink = NULL;
  }
}

static GstPadProbeReturn link_to_videomixer(GstPad* pad, GstPadProbeInfo* info, gst_mnscmixer_Data* data){
  if (GST_EVENT_TYPE(gst_pad_probe_info_get_event(info)) != GST_EVENT_STREAM_START) {
    return GST_PAD_PROBE_PASS;
  }

  Gstmnscmixer* mixer = GST_MNSCMIXER(data->mixer);
  GST_DEBUG("stream start detected %d", data->id);
  GST_MNSCMIXER_LOCK(mixer);

  data->link_probe_id = 0;
  data->latency_probe_id = 0;

  GstPadTemplate* sink_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS (mixer->priv->videomixer), "sink_%u");

  if(G_UNLIKELY(sink_pad_template == NULL)){
    GST_ERROR_OBJECT (mixer, "Error taking a new pad from videomixer");
    GST_MNSCMIXER_UNLOCK (mixer);
    return GST_PAD_PROBE_DROP;
  }

  data->input = TRUE;

  data->video_mixer_pad = gst_element_request_pad(mixer->priv->videomixer, sink_pad_template, NULL, NULL);

  GstPad* tee_src = gst_element_get_request_pad (data->tee, "src_%u");
  gst_element_link_pads(data->tee, GST_OBJECT_NAME(tee_src), mixer->priv->videomixer, GST_OBJECT_NAME(data->video_mixer_pad));
  g_object_unref(tee_src);

  data->probe_id = gst_pad_add_probe(data->video_mixer_pad, GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM, (GstPadProbeCallback) cb_EOS_received, GST_MNSCMIXER_REF(data), (GDestroyNotify)kms_ref_struct_unref);
  data->latency_probe_id = gst_pad_add_probe(data->video_mixer_pad, GST_PAD_PROBE_TYPE_QUERY_UPSTREAM, (GstPadProbeCallback)cb_latency, NULL, NULL);

  mixer->priv->n_elems++;
  gst_mnscmixer_recalculate_sizes_a(mixer);
  gst_bin_recalculate_latency(GST_BIN(mixer));
  GST_MNSCMIXER_UNLOCK (mixer);
  return GST_PAD_PROBE_REMOVE;
}

static void release_gint(gpointer data){
  g_slice_free(gint, data);
}

static gint* create_gint(gint value){
  gint *p = g_slice_new(gint);
  *p = value;
  return p;
}

static void gst_mnscmixer_unhandle_port(KmsBaseHub* mixer, gint id){
  Gstmnscmixer *self = GST_MNSCMIXER(mixer);
  GST_DEBUG("unhandle id %d", id);
  GST_MNSCMIXER_LOCK(self);
  g_hash_table_remove(self->priv->ports, &id);
  GST_MNSCMIXER_UNLOCK(self);
  KMS_BASE_HUB_CLASS(G_OBJECT_CLASS(gst_mnscmixer_parent_class))->unhandle_port(mixer, id);
}

static gst_mnscmixer_Data* gst_mnscmixer_port_data_create(Gstmnscmixer* mixer, gint id){
  GST_DEBUG("gst_mnscmixer_port_data_create");
  gst_mnscmixer_Data* data = create_gst_mnscmixer_data();
  data->mixer = mixer;
  data->id = id;

  data->tee = gst_element_factory_make ("tee", NULL);
  if(data->tee == NULL){
    GST_ERROR("gst_mnscmixer_port_data_create tee creation");
  }

  data->fakesink = gst_element_factory_make ("fakesink", NULL);
  if(data->fakesink == NULL){
    GST_ERROR("gst_mnscmixer_port_data_create fakesink creation");
  }
  g_object_set (G_OBJECT (data->fakesink), "async", FALSE, "sync", FALSE, NULL);

  data->capsfilter = gst_element_factory_make("capsfilter", NULL);
  if(data->capsfilter == NULL){
    GST_ERROR("gst_mnscmixer_port_data_create capfilter creation");
  }
  GstCaps* filtercaps =  gst_caps_new_simple("video/x-raw", "width", G_TYPE_INT, mixer->priv->output_width, "height", G_TYPE_INT, mixer->priv->output_height, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1, NULL);
  g_object_set(data->capsfilter, "caps", filtercaps, NULL);
  gst_caps_unref(filtercaps);

  data->videocrop = gst_element_factory_make("videocrop", NULL);
  if(data->capsfilter == NULL){
    GST_ERROR("gst_mnscmixer_port_data_create videocrop creation");
  }
  g_object_set (G_OBJECT (data->videocrop), "left", 0, "right", 0, NULL);

  gst_bin_add_many(GST_BIN (mixer), g_object_ref(data->capsfilter), g_object_ref(data->videocrop), g_object_ref(data->tee), g_object_ref(data->fakesink), NULL);

  gst_element_sync_state_with_parent (data->capsfilter);
  gst_element_sync_state_with_parent (data->videocrop);
  gst_element_sync_state_with_parent (data->tee);
  gst_element_sync_state_with_parent (data->fakesink);

  gboolean res = kms_base_hub_link_video_sink (KMS_BASE_HUB(mixer), id, data->videocrop, "sink", FALSE);
  if(!res){
    GST_ERROR("gst_mnscmixer_port_data_create5");
  }

  res = gst_element_link_pads(data->videocrop, NULL, data->capsfilter, NULL);
  if(!res){
    GST_ERROR("gst_mnscmixer_port_data_create connection capsfilter - videocrop");
  }

  data->tee_sink_pad = gst_element_get_static_pad(data->tee, "sink");
  res = gst_element_link_pads(data->capsfilter, NULL, data->tee, GST_OBJECT_NAME(data->tee_sink_pad));
  if(!res){
    GST_ERROR("gst_mnscmixer_port_data_create connection capsfilter - tee");
  }

  GstPad* tee_src = gst_element_get_request_pad(data->tee, "src_%u");
  res = gst_element_link_pads(data->tee, GST_OBJECT_NAME(tee_src), data->fakesink, "sink");
  if(!res){
    GST_ERROR("gst_mnscmixer_port_data_create connection tee - fakesink");
  }
  g_object_unref (tee_src);

  data->link_probe_id = gst_pad_add_probe(data->tee_sink_pad, GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM | GST_PAD_PROBE_TYPE_BLOCK, (GstPadProbeCallback)link_to_videomixer, GST_MNSCMIXER_REF (data), (GDestroyNotify)kms_ref_struct_unref);

  //  data->video_mixer_pad = gst_element_get_request_pad(mixer->priv->videomixer, "sink_%u");
  //  if(data->video_mixer_pad == NULL){
  //    GST_ERROR("gst_mnscmixer_port_data_create9");
  //  }
  //
  //  res = gst_element_link_pads(data->capsfilter, "src", mixer->priv->videomixer, GST_OBJECT_NAME(data->video_mixer_pad));
  //  if(!res){
  //    GST_ERROR("gst_mnscmixer_port_data_create10");
  //  }

  return data;
}

static gint get_stream_id_from_padname(const gchar* name){
  gint64 id;
  if(name == NULL)
    return -1;
  if(!g_str_has_prefix(name, AUDIO_SRC_PAD_PREFIX))
    return -1;
  id = g_ascii_strtoll(name + LENGTH_AUDIO_SRC_PAD_PREFIX, NULL, 10);
  if(id > G_MAXINT)
    return -1;
  return id;
}

static void video_pad_added_cb (GstElement* element, GstPad* pad, gpointer data){
  GST_DEBUG("Adding video pad %" GST_PTR_FORMAT, pad);
  gint id;
  Gstmnscmixer* self = GST_MNSCMIXER(data);
  if(gst_pad_get_direction(pad) != GST_PAD_SRC)
    return;
  id = get_stream_id_from_padname(GST_OBJECT_NAME(pad));
  if(id < 0){
    GST_ERROR_OBJECT(self, "Invalid HubPort for %" GST_PTR_FORMAT, pad);
    return;
  }
  GST_DEBUG("Adding video src pad %" GST_PTR_FORMAT, pad);
  gboolean res = kms_base_hub_link_video_src(KMS_BASE_HUB(self), id, self->priv->videomixer, GST_OBJECT_NAME(pad), TRUE);
  if(!res){
    GST_ERROR("video_pad_added_cb1");
  }

}

static void video_pad_removed_cb(GstElement* element, GstPad* pad, gpointer data){
  GST_DEBUG("Removed video pad %" GST_PTR_FORMAT, pad);
}

static gint gst_mnscmixer_handle_port(KmsBaseHub* mixer, GstElement* mixer_end_point){
  GST_DEBUG("gst_mnscmixer_handle_port");
  Gstmnscmixer* self = GST_MNSCMIXER(mixer);
  if(self->priv->n_elems>=4){
    return 0;
  }
  gst_mnscmixer_Data* port_data;
  gint port_id;
  GST_DEBUG("Handle new HubPort");
  port_id = KMS_BASE_HUB_CLASS(G_OBJECT_CLASS(gst_mnscmixer_parent_class))->handle_port(mixer, mixer_end_point);
  if (port_id < 0) {
    return port_id;
  }
  GST_MNSCMIXER_LOCK (self);
  if(self->priv->videomixer == NULL){
    self->priv->videomixer = gst_element_factory_make("videomixer", NULL);
    if(!self->priv->videomixer){
      GST_ERROR("gst_mnscmixer_handle_port1");
    }
    self->priv->mixer_video_agnostic = gst_element_factory_make("agnosticbin", NULL);
    gst_bin_add_many(GST_BIN (mixer), self->priv->videomixer, self->priv->mixer_video_agnostic, NULL);
    gboolean res = gst_element_link(self->priv->videomixer, self->priv->mixer_video_agnostic);
    if(!res){
      GST_ERROR("gst_mnscmixer_handle_port2");
    }
    res = g_signal_connect(self->priv->videomixer, "pad-added", G_CALLBACK(video_pad_added_cb), self);
    if(!res){
      GST_ERROR("gst_mnscmixer_handle_port3");
    }
    res = g_signal_connect(self->priv->videomixer, "pad-removed", G_CALLBACK(video_pad_removed_cb), self);
    if(!res){
      GST_ERROR("gst_mnscmixer_handle_port4");
    }
    gst_element_sync_state_with_parent(self->priv->videomixer);
    gst_element_sync_state_with_parent(self->priv->mixer_video_agnostic);
  }

  gboolean res = kms_base_hub_link_video_src(KMS_BASE_HUB (self), port_id,  self->priv->mixer_video_agnostic, "src_%u", TRUE);
  if(!res){
    GST_ERROR("gst_mnscmixer_handle_port5");
  }
  port_data = gst_mnscmixer_port_data_create(self, port_id);
  port_data->input = TRUE;
  g_hash_table_insert(self->priv->ports, create_gint(port_id), port_data);
  //  self->priv->n_elems++;
  self->priv->focus = 0;
  gst_mnscmixer_recalculate_sizes_a(self);
  GST_MNSCMIXER_UNLOCK (self);
  return port_id;
}

static void gst_mnscmixer_dispose(GObject* object){
  GST_DEBUG("gst_mnscmixer_finalize");
  Gstmnscmixer* self = GST_MNSCMIXER(object);
  GST_MNSCMIXER_LOCK (self);
  g_hash_table_remove_all(self->priv->ports);
  GST_MNSCMIXER_UNLOCK(self);
  g_clear_object(&self->priv->loop);
  G_OBJECT_CLASS(gst_mnscmixer_parent_class)->dispose(object);
}


static void gst_mnscmixer_finalize (GObject *object){
  GST_DEBUG("gst_mnscmixer_finalize");
  Gstmnscmixer *self = GST_MNSCMIXER(object);
  g_rec_mutex_clear(&self->priv->mutex);
  if(self->priv->ports != NULL){
    g_hash_table_unref(self->priv->ports);
    self->priv->ports = NULL;
  }
  G_OBJECT_CLASS(gst_mnscmixer_parent_class)->finalize(object);
}

static void gst_mnscmixer_init (Gstmnscmixer *self){
  GST_DEBUG("gst_mnscmixer_init");
  self->priv = GST_MNSCMIXER_GET_PRIVATE(self);
  g_rec_mutex_init(&self->priv->mutex);
  self->priv->ports = g_hash_table_new_full(g_int_hash, g_int_equal, release_gint, gst_mnscmixer_port_data_destroy);
  self->priv->output_height = 720;
  self->priv->output_width = 1280;
  self->priv->n_elems = 0;
  self->priv->focus = 0;
  self->priv->loop = kms_loop_new ();
}

static gboolean gst_mnscmixer_focus(Gstmnscmixer* self, guint sink_id, guint param){
  GST_DEBUG("gst_mnscmixer_focus %d %d", sink_id, param);
  self->priv->focus = sink_id;
  gst_mnscmixer_recalculate_sizes_a(self);
  return TRUE;
}

static void gst_mnscmixer_class_init(GstmnscmixerClass *klass){
  GST_DEBUG("gst_mnscmixer_class_init");
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);
  KmsBaseHubClass* base_hub_class = KMS_BASE_HUB_CLASS(klass);
  GstElementClass* gstelement_class = GST_ELEMENT_CLASS(klass);
  gst_element_class_set_static_metadata(GST_ELEMENT_CLASS (klass), "MNSC_Mixer", "Generic", "Mixer element that composes n input flows in one output flow", "Andrey MNatsakanov <andrey@3ig.kiev.ua>");
  gobject_class->dispose = GST_DEBUG_FUNCPTR(gst_mnscmixer_dispose);
  gobject_class->finalize = GST_DEBUG_FUNCPTR(gst_mnscmixer_finalize);
  base_hub_class->handle_port = GST_DEBUG_FUNCPTR(gst_mnscmixer_handle_port);
  base_hub_class->unhandle_port = GST_DEBUG_FUNCPTR(gst_mnscmixer_unhandle_port);
  gst_element_class_add_pad_template(gstelement_class, gst_static_pad_template_get(&sink_factory));
  klass->focus = GST_DEBUG_FUNCPTR(gst_mnscmixer_focus);

  obj_signals[SIGNAL_FOCUS] = g_signal_new ("focus", G_TYPE_FROM_CLASS (klass), G_SIGNAL_ACTION | G_SIGNAL_RUN_LAST, G_STRUCT_OFFSET (GstmnscmixerClass, focus), NULL, NULL, __kms_core_marshal_BOOLEAN__UINT_UINT, G_TYPE_BOOLEAN, 2, G_TYPE_UINT, G_TYPE_UINT);

  g_type_class_add_private(klass, sizeof(gst_mnscmixer_Private));
}

gboolean gst_mnscmixer_plugin_init (GstPlugin *plugin){
  return gst_element_register (plugin, PLUGIN_NAME, GST_RANK_NONE, GST_TYPE_MNSCMIXER);
}

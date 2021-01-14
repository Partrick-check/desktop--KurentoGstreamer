#ifndef _GST_MNSCMIXER_H_
#define _GST_MNSCMIXER_H_

#include <kurento/commons/kmsbasehub.h>

#define AUDIO_SINK_PAD_PREFIX  "audio_sink_"
#define AUDIO_SRC_PAD_PREFIX  "audio_src_"
#define LENGTH_AUDIO_SINK_PAD_PREFIX (sizeof(AUDIO_SINK_PAD_PREFIX) - 1)
#define LENGTH_AUDIO_SRC_PAD_PREFIX (sizeof(AUDIO_SRC_PAD_PREFIX) - 1)
#define AUDIO_SINK_PAD AUDIO_SINK_PAD_PREFIX "%u"
#define AUDIO_SRC_PAD AUDIO_SRC_PAD_PREFIX "%u"
#define VIDEO_SINK_PAD_PREFIX  "video_sink_"
#define VIDEO_SRC_PAD_PREFIX  "video_src_"
#define LENGTH_VIDEO_SINK_PAD_PREFIX (sizeof(VIDEO_SINK_PAD_PREFIX) - 1)
#define LENGTH_VIDEO_SRC_PAD_PREFIX (sizeof(VIDEO_SRC_PAD_PREFIX) - 1)
#define VIDEO_SINK_PAD VIDEO_SINK_PAD_PREFIX "%u"
#define VIDEO_SRC_PAD VIDEO_SRC_PAD_PREFIX "%u"

G_BEGIN_DECLS

#define GST_TYPE_MNSCMIXER   (gst_mnscmixer_get_type())
#define GST_MNSCMIXER(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MNSCMIXER,Gstmnscmixer))
#define GST_MNSCMIXER_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MNSCMIXER,gst_mnscmixerClass))
#define GST_IS_MNSCMIXER(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MNSCMIXER))
#define GST_IS_MNSCMIXER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MNSCMIXER))
typedef struct _Gstmnscmixer Gstmnscmixer;
typedef struct _GstmnscmixerClass GstmnscmixerClass;
typedef struct _gst_mnscmixer_Private gst_mnscmixer_Private;

struct _Gstmnscmixer{
  KmsBaseHub parent;
  gst_mnscmixer_Private *priv;
};

struct _GstmnscmixerClass{
  KmsBaseHubClass parent_class;
  gboolean (*focus)(Gstmnscmixer* self, guint sink_id, guint param);
};

GType gst_mnscmixer_get_type (void);

gboolean gst_mnscmixer_plugin_init (GstPlugin *plugin);

G_END_DECLS

#endif /* _GST_MNSCMIXER_H_ */

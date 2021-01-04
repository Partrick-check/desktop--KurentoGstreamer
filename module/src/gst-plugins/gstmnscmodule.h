#ifndef _GST_MNSCMODULE_H_
#define _GST_MNSCMODULE_H_

#include <gst/video/gstvideofilter.h>

G_BEGIN_DECLS

#define GST_TYPE_MNSCMODULE   (gst_mnscmodule_get_type())
#define GST_MNSCMODULE(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MNSCMODULE,Gstmnscmodule))
#define GST_MNSCMODULE_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MNSCMODULE,GstmnscmoduleClass))
#define GST_IS_MNSCMODULE(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MNSCMODULE))
#define GST_IS_MNSCMODULE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MNSCMODULE))
typedef struct _Gstmnscmodule Gstmnscmodule;
typedef struct _GstmnscmoduleClass GstmnscmoduleClass;
typedef struct _GstmnscmodulePrivate GstmnscmodulePrivate;

struct _Gstmnscmodule
{
  GstVideoFilter base;
  GstmnscmodulePrivate *priv;
};

struct _GstmnscmoduleClass
{
  GstVideoFilterClass base_mnscmodule_class;
};

GType gst_mnscmodule_get_type (void);

gboolean gst_mnscmodule_plugin_init (GstPlugin *plugin);

G_END_DECLS

#endif /* _GST_MNSCMODULE_H_ */

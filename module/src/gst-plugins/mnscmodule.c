#include <config.h>
#include <gst/gst.h>
#include "gstmnscmodule.h"

static gboolean init (GstPlugin *plugin){
  if (!gst_mnscmodule_plugin_init (plugin))
    return FALSE;
  return TRUE;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR, GST_VERSION_MINOR, mnscmodule, "Filter documentation", init, VERSION, GST_LICENSE_UNKNOWN, "PACKAGE_NAME", "origin")

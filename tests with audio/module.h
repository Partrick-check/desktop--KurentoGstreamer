#ifndef _KMS_module_MIXER_H_
#define _KMS_module_MIXER_H_

#include <commons/kmsbasehub.h>

#define AUDIO_SINK_PAD_PREFIX  "sink_"
#define AUDIO_SRC_PAD_PREFIX  "src_"
#define LENGTH_AUDIO_SINK_PAD_PREFIX (sizeof(AUDIO_SINK_PAD_PREFIX) - 1)
#define LENGTH_AUDIO_SRC_PAD_PREFIX (sizeof(AUDIO_SRC_PAD_PREFIX) - 1)
#define AUDIO_SINK_PAD AUDIO_SINK_PAD_PREFIX "%u"
#define AUDIO_SRC_PAD AUDIO_SRC_PAD_PREFIX "%u"

G_BEGIN_DECLS
#define KMS_TYPE_module_MIXER kms_module_mixer_get_type()
#define KMS_module_MIXER(obj) (      \
  G_TYPE_CHECK_INSTANCE_CAST(           \
    (obj),                              \
    KMS_TYPE_module_MIXER,           \
    KmsmoduleMixer                   \
  )                                     \
)
#define KMS_module_MIXER_CLASS(klass) (   \
  G_TYPE_CHECK_CLASS_CAST (                  \
    (klass),                                 \
    KMS_TYPE_module_MIXER,                \
    KmsmoduleMixerClass                   \
  )                                          \
)
#define KMS_IS_module_MIXER(obj) (        \
  G_TYPE_CHECK_INSTANCE_TYPE (               \
    (obj),                                   \
    KMS_TYPE_module_MIXER                 \
  )                                          \
)
#define KMS_IS_module_MIXER_CLASS(klass) (\
  G_TYPE_CHECK_CLASS_TYPE((klass),           \
  KMS_TYPE_module_MIXER)                  \
)

typedef struct _KmsmoduleMixer KmsmoduleMixer;
typedef struct _KmsmoduleMixerClass KmsmoduleMixerClass;
typedef struct _KmsmoduleMixerPrivate KmsmoduleMixerPrivate;

struct _KmsmoduleMixer
{
  KmsBaseHub parent;

  KmsmoduleMixerPrivate *priv;
};

struct _KmsmoduleMixerClass
{
  KmsBaseHubClass parent_class;
};

GType kms_module_mixer_get_type (void);

gboolean kms_module_mixer_plugin_init (GstPlugin * plugin);

G_END_DECLS
#endif
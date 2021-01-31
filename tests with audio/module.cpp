#include <gst/gst.h>
#include "MediaPipeline.hpp"
#include <moduleImplFactory.hpp>
#include "moduleImpl.hpp"
#include <jsonrpc/JsonSerializer.hpp>
#include <KurentoException.hpp>
#include <gst/gst.h>

#define GST_CAT_DEFAULT kurento_module_impl
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);
#define GST_DEFAULT_NAME "KurentomoduleImpl"

#define FACTORY_NAME "modulemixer"

namespace kurento
{

moduleImpl::moduleImpl (const boost::property_tree::ptree &conf,
                              std::shared_ptr<MediaPipeline> mediaPipeline) : HubImpl (conf,
                                    std::dynamic_pointer_cast<MediaObjectImpl> (mediaPipeline), FACTORY_NAME)
{
}

MediaObjectImpl *
moduleImplFactory::createObject (const boost::property_tree::ptree &conf,
                                    std::shared_ptr<MediaPipeline> mediaPipeline) const
{
  return new moduleImpl (conf, mediaPipeline);
}

moduleImpl::StaticConstructor moduleImpl::staticConstructor;

moduleImpl::StaticConstructor::StaticConstructor()
{
  GST_DEBUG_CATEGORY_INIT (GST_CAT_DEFAULT, GST_DEFAULT_NAME, 0,
                           GST_DEFAULT_NAME);
}


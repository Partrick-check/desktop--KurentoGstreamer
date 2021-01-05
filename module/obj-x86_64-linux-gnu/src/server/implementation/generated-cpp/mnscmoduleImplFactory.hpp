/* Autogenerated with kurento-module-creator */

#ifndef __MNSCMODULE_IMPL_FACTORY_HPP__
#define __MNSCMODULE_IMPL_FACTORY_HPP__

#include "mnscmoduleImpl.hpp"
#include "FilterImplFactory.hpp"
#include <Factory.hpp>
#include <MediaObjectImpl.hpp>
#include <boost/property_tree/ptree.hpp>

namespace kurento
{
namespace module
{
namespace mnscmodule
{

class mnscmoduleImplFactory : public virtual FilterImplFactory
{
public:
  mnscmoduleImplFactory() = default;

  std::string getName() const override {
    return "mnscmodule";
  };

private:

  MediaObjectImpl *createObjectPointer (
      const boost::property_tree::ptree &conf,
      const Json::Value &params) const override;

  MediaObjectImpl *createObject (const boost::property_tree::ptree &conf, std::shared_ptr<MediaPipeline> mediaPipeline) const;
};

} /* mnscmodule */
} /* module */
} /* kurento */

#endif /*  __MNSCMODULE_IMPL_FACTORY_HPP__ */
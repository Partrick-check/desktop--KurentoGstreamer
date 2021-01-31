#ifndef __module_IMPL_HPP__
#define __module_IMPL_HPP__

#include "HubImpl.hpp"
#include "module.hpp"
#include <EventHandler.hpp>

namespace kurento
{

class MediaPipeline;
class moduleImpl;

void Serialize (std::shared_ptr<moduleImpl> &object,
                JsonSerializer &serializer);

class moduleImpl : public HubImpl, public virtual module
{

public:

  moduleImpl (const boost::property_tree::ptree &conf,
                 std::shared_ptr<MediaPipeline> mediaPipeline);

  virtual ~moduleImpl () {};

  virtual bool connect (const std::string &eventType,
                        std::shared_ptr<EventHandler> handler);

  virtual void invoke (std::shared_ptr<MediaObjectImpl> obj,
                       const std::string &methodName, const Json::Value &params,
                       Json::Value &response);

  virtual void Serialize (JsonSerializer &serializer);

private:

  class StaticConstructor
  {
  public:
    StaticConstructor();
  };

  static StaticConstructor staticConstructor;

};

}

#endif
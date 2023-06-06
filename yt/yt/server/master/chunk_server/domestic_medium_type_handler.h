#pragma once

#include "public.h"

#include <yt/yt/server/master/object_server/type_handler.h>

namespace NYT::NChunkServer {

////////////////////////////////////////////////////////////////////////////////

NObjectServer::IObjectTypeHandlerPtr CreateDomesticMediumTypeHandler(
    NCellMaster::TBootstrap* bootstrap);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NChunkServer
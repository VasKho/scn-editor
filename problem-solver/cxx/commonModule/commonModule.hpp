#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "searchSemNeighborhoodKeynodes.hpp"
#include "searchSemNeighborhoodAgent.hpp"

#include "commonModule.generated.hpp"

namespace common_module {
  class commonModule : public ScModule {
    SC_CLASS(LoadOrder(100))
    SC_GENERATED_BODY()
    
    virtual sc_result
    
    InitializeImpl() override;
    
    virtual sc_result ShutdownImpl() override;
  };  
}  // namespace common_module

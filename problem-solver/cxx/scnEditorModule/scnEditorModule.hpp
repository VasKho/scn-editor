#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "selectScnPageKeynodes.hpp"
#include "selectScnPageAgent.hpp"
#include "createScnPageKeynodes.hpp"
#include "createScnPageAgent.hpp"
#include "openScnPageKeynodes.hpp"
#include "openScnPageAgent.hpp"

#include "scnEditorModule.generated.hpp"

namespace scn_editor_module {
  class scnEditorModule : public ScModule {
    SC_CLASS(LoadOrder(100))
    SC_GENERATED_BODY()
    
    virtual sc_result
    
    InitializeImpl() override;
    
    virtual sc_result ShutdownImpl() override;
  };  
}  // namespace scn_editor_module

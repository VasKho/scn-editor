#pragma once

#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "selectScnPageAgent.generated.hpp"

namespace scn_editor_module {
  class selectScnPageAgent : public ScAgent {
    SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
    SC_GENERATED_BODY()

    public:
    static ScAddr prepareActionInit(ScMemoryContext* ctx, ScAddr newCurrentPage);
    
    private:
    bool checkActionClass(ScAddr const & actionAddr);
  };

}  // namespace scn_editor_module

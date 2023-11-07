#pragma once

#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "createScnPageAgent.generated.hpp"

namespace scn_editor_module {
  class createScnPageAgent : public ScAgent {
    SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
    SC_GENERATED_BODY()

    private:
    bool checkActionClass(ScAddr const & actionAddr);
  };

}  // namespace scn_editor_module

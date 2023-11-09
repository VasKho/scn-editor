#pragma once

#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "searchSemNeighborhoodAgent.generated.hpp"

namespace common_module {
  class searchSemNeighborhoodAgent : public ScAgent {
    SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
    SC_GENERATED_BODY()

    public:
    static ScAddr prepareActionInit(ScMemoryContext* ctx, ScAddr rootNode);
    
    private:
    bool checkActionClass(ScAddr const & actionAddr);
    void addInputTriples(ScMemoryContext* ctx, ScAddr answer, ScAddr node);
    void addOutputTriples(ScMemoryContext* ctx, ScAddr answer, ScAddr node);
  };

}  // namespace common_module

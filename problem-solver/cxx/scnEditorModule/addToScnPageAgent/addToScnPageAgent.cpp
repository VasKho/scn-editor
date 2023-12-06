#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "addToScnPageKeynodes.hpp"
#include "addToScnPageAgent.hpp"

using namespace scn_editor_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(addToScnPageAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("addToScnPageAgent started");

  ScAddr const& elt = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!elt.IsValid()) {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
  ScAddr const& curPage = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, addToScnPageKeynodes::scn_editor, addToScnPageKeynodes::rrel_current_scn_page);
  
  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, curPage, elt);

  SC_LOG_INFO("addToScnPageAgent: Add new element to the sc.n-page successfully");

  return SC_RESULT_OK;
}

bool addToScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(addToScnPageKeynodes::action_add_to_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

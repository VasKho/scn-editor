#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "selectScnPageAgent.hpp"
#include "openScnPageKeynodes.hpp"
#include "openScnPageAgent.hpp"

using namespace scn_editor_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(openScnPageAgent) {
  ScAddr const & questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("openScnPageAgent started");
  
  ScAddr const& scnRootNode = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!scnRootNode.IsValid()) {
    SC_LOG_ERROR("openScnPageAgent: Invalid ScAddr");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }

  ScAddr action = m_memoryCtx.CreateNode(ScType::NodeConst);
  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, m_memoryCtx.HelperResolveSystemIdtf("action_search_semantic_neighborhood"), action);
  ScAddr edge = m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, action, scnRootNode);
  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::rrel_1, edge);
  utils::AgentUtils::getActionResultIfExists(&m_memoryCtx, action, 500);

  ScAddr answer = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, action, scAgentsCommon::CoreKeynodes::nrel_answer);

  ScTemplate templ;
  templ.Quintuple(
    openScnPageKeynodes::scn_editor,
    ScType::EdgeAccessVarPosPerm,
    answer,
    ScType::EdgeAccessVarPosPerm,
    openScnPageKeynodes::rrel_scn_page
  );

  ScTemplateGenResult result;
  if (!m_memoryCtx.HelperGenTemplate(templ, result)) {
    SC_LOG_ERROR("openScnPageAgent: Failed to create new sc.n-page");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }
  
  action = selectScnPageAgent::prepareActionInit(&m_memoryCtx, result[2]);
  utils::AgentUtils::getActionResultIfExists(&m_memoryCtx, action, 400);

  SC_LOG_INFO("openScnPageAgent: new sc.n-page opened successfully");
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, result[2], true);
  return SC_RESULT_OK;
}

bool openScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(openScnPageKeynodes::action_open_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

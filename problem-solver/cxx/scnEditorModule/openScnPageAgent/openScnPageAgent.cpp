#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "openScnPageKeynodes.hpp"
#include "selectScnPageAgent.hpp"

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
    return SC_RESULT_ERROR;
  }

  ScAddr const& inCurrent = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_2);
  bool inCurrentBool = false;
  if (inCurrent.IsValid()) {
    std::string str;
    m_memoryCtx.GetLinkContent(inCurrent, str);
    inCurrentBool = (str == "true");
  }

  ScAddr action = m_memoryCtx.CreateNode(ScType::NodeConst);
  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, action, scnRootNode);
  m_memoryCtx.CreateEdge(
    ScType::EdgeAccessConstPosPerm,
    m_memoryCtx.HelperResolveSystemIdtf("question_search_full_semantic_neighborhood"),
    action
  );

  m_memoryCtx.CreateEdge(
    ScType::EdgeAccessConstPosPerm,
    m_memoryCtx.HelperResolveSystemIdtf("question"),
    action
  );

  m_memoryCtx.CreateEdge(
    ScType::EdgeAccessConstPosPerm,
    m_memoryCtx.HelperResolveSystemIdtf("question_initiated"),
    action
  );

  ScAddr answer = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, action, scAgentsCommon::CoreKeynodes::nrel_answer);

  if (inCurrentBool) {
    // ScAddr const& currentPage = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, openScnPageKeynodes::scn_editor, scAgentsCommon::CoreKeynodes::rrel_current_scn_page);
    // m_memoryCtx.CreateEdge(ScType::);
  } else {
    ScTemplate templ;
    templ.TripleWithRelation(
      openScnPageKeynodes::scn_editor,
      ScType::EdgeAccessVarPosPerm,
      answer,
      ScType::EdgeAccessVarPosPerm,
      openScnPageKeynodes::rrel_scn_page
    );

    ScTemplateGenResult result;
    if (!m_memoryCtx.HelperGenTemplate(templ, result)) {
      SC_LOG_ERROR("openScnPageAgent: Failed to create new sc.n-page");
      return SC_RESULT_ERROR;
    }

    ScAddr action = selectScnPageAgent::prepareActionInit(&m_memoryCtx, result[2]);
    utils::AgentUtils::getActionResultIfExists(&m_memoryCtx, action, 400);
  }
  
  SC_LOG_ERROR(m_memoryCtx.GetElementType(answer).IsValid());
  
  return SC_RESULT_OK;
}

bool openScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(openScnPageKeynodes::action_open_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

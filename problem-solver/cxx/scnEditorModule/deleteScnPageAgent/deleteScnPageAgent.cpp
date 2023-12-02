#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "deleteScnPageKeynodes.hpp"
#include "deleteScnPageAgent.hpp"

using namespace scn_editor_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(deleteScnPageAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("deleteScnPageAgent started");

  ScAddr page = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!page.IsValid()) {
    SC_LOG_ERROR("deleteScnPageAgent: No such sc.n-page");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }

  if (m_memoryCtx.GetElementType(page).IsLink()) {
    std::string str;
    m_memoryCtx.GetLinkContent(page, str);
    page = m_memoryCtx.HelperResolveSystemIdtf(str);
  }

  ScAddr isCurrent = utils::IteratorUtils::getAnyByInRelation(&m_memoryCtx, page, deleteScnPageKeynodes::rrel_current_scn_page);
  m_memoryCtx.EraseElement(page);

  if (isCurrent.IsValid()) {
    ScAddr newCurPage = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, deleteScnPageKeynodes::scn_editor, deleteScnPageKeynodes::rrel_scn_page);
    if (newCurPage.IsValid()) {
      ScIterator3Ptr arc = m_memoryCtx.Iterator3(deleteScnPageKeynodes::scn_editor, ScType::EdgeAccessConstPosPerm, newCurPage);
      arc->Next();
      m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, deleteScnPageKeynodes::rrel_current_scn_page, arc->Get(1));
    }
  }

  SC_LOG_INFO("deleteScnPageAgent: sc.n-page deleted successfully");
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, true);
  return SC_RESULT_OK;
}

bool deleteScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(deleteScnPageKeynodes::action_delete_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

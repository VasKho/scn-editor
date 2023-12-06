#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "removeFromScnPageKeynodes.hpp"
#include "removeFromScnPageAgent.hpp"

using namespace scn_editor_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(removeFromScnPageAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("removeFromScnPageAgent started");

  ScAddr elt = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!elt.IsValid()) {
    return SC_RESULT_ERROR;
  }

  if (m_memoryCtx.GetElementType(elt).IsLink()) {
    std::string str;
    m_memoryCtx.GetLinkContent(elt, str);
    elt = m_memoryCtx.HelperResolveSystemIdtf(str);
  }

  ScAddr curPage = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, removeFromScnPageKeynodes::scn_editor, removeFromScnPageKeynodes::rrel_current_scn_page);
  if (!m_memoryCtx.HelperCheckEdge(curPage, elt, ScType::EdgeAccessConstPosPerm)) {
    SC_LOG_ERROR("removeFromScnPageAgent: Given element is not on current page");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }
  
  ScIterator3Ptr arcs3 = m_memoryCtx.Iterator3(curPage, ScType::EdgeAccessConstPosPerm, elt);
  while (arcs3-> Next()) {
    m_memoryCtx.EraseElement(arcs3->Get(1));
  }
  
  ScIterator5Ptr arcs = m_memoryCtx.Iterator5(
    elt,
    ScType::Unknown,
    ScType::Unknown,
    ScType::EdgeAccessConstPosPerm,
    curPage
  );

  while (arcs->Next()) {
    m_memoryCtx.EraseElement(arcs->Get(1));
  }

  arcs = m_memoryCtx.Iterator5(
    ScType::Unknown,
    ScType::Unknown,
    elt,
    ScType::EdgeAccessConstPosPerm,
    curPage
  );

  while (arcs->Next()) {
    m_memoryCtx.EraseElement(arcs->Get(1));
  }

  arcs3 = m_memoryCtx.Iterator3(elt, ScType::Unknown, ScType::Unknown);
  if (!arcs3->Next()) {
    arcs3 = m_memoryCtx.Iterator3(ScType::Unknown, ScType::Unknown, elt);
    if (!arcs3->Next()) {
      m_memoryCtx.EraseElement(arcs->Get(2));
    }
  }

  SC_LOG_INFO("removeFromScnPageAgent: Successfully removed element from sc.n-page");
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, true);
  return SC_RESULT_OK;
}

bool removeFromScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(removeFromScnPageKeynodes::action_remove_from_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "selectScnPageKeynodes.hpp"

#include "selectScnPageAgent.hpp"

using namespace scn_editor_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(selectScnPageAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("selectScnPageAgent started");

  ScAddr newCurScnPage = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!newCurScnPage.IsValid()) {
    SC_LOG_ERROR("selectScnPageAgent: Invalid ScAddr");
    return SC_RESULT_ERROR;
  }

  if (m_memoryCtx.GetElementType(newCurScnPage).IsLink()) {
    std::string str;
    m_memoryCtx.GetLinkContent(newCurScnPage, str);
    newCurScnPage = m_memoryCtx.HelperResolveSystemIdtf(str);
  }
  if (m_memoryCtx.GetElementType(newCurScnPage) != ScType::NodeConstStruct) {
    SC_LOG_ERROR("selectScnPageAgent: Give element is not a valid sc.n-page");
    return SC_RESULT_ERROR;
  }

  ScIterator5Ptr testOnScnPage = m_memoryCtx.Iterator5(
    selectScnPageKeynodes::scn_editor,
    ScType::EdgeAccessConstPosPerm,
    newCurScnPage,
    ScType::EdgeAccessConstPosPerm,
    selectScnPageKeynodes::rrel_scn_page
  );
  if (!testOnScnPage->Next()) {
    SC_LOG_ERROR("selectScnPageAgent: Given node is not an sc.n-page");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }

  ScIterator3Ptr curPage = m_memoryCtx.Iterator3(selectScnPageKeynodes::rrel_current_scn_page, ScType::EdgeAccessConstPosPerm, ScType::EdgeAccessConstPosPerm);
  while (curPage->Next()) {
    m_memoryCtx.EraseElement(curPage->Get(1));
  }

  curPage = m_memoryCtx.Iterator3(selectScnPageKeynodes::scn_editor, ScType::EdgeAccessConstPosPerm, newCurScnPage);
  if (curPage->Next()) {
    m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, selectScnPageKeynodes::rrel_current_scn_page, curPage->Get(1));
  }

  SC_LOG_INFO("selectScnPageAgent: New current sc.n-page selected successfully");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, newCurScnPage, false);
  return SC_RESULT_OK;
}

bool selectScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(selectScnPageKeynodes::action_select_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

ScAddr selectScnPageAgent::prepareActionInit(ScMemoryContext* ctx, ScAddr newCurrentPage) {
  ScAddr actionNode = ctx->CreateNode(ScType::NodeConst);
  ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, selectScnPageKeynodes::action_select_scn_page, actionNode);
  ScAddr edge = ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, actionNode, newCurrentPage);
  ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::rrel_1, edge);
  return actionNode;
}

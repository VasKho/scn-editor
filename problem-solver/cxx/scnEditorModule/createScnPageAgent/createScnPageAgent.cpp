#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "createScnPageKeynodes.hpp"

#include "createScnPageAgent.hpp"

using namespace scn_editor_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(createScnPageAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("createScnPageAgent started");

  ScAddr const& makeCurrent = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  bool makeCurrentBool = true;
  if (makeCurrent.IsValid()) {
    std::string str;
    m_memoryCtx.GetLinkContent(makeCurrent, str);
    makeCurrentBool = (str == "true");
  }

  ScTemplate templ;
  templ.TripleWithRelation(
    createScnPageKeynodes::scn_editor,
    ScType::EdgeAccessVarPosPerm,
    ScType::NodeVarStruct,
    ScType::EdgeAccessVarPosPerm,
    createScnPageKeynodes::rrel_scn_page
  );

  ScTemplateGenResult result;
  if (!m_memoryCtx.HelperGenTemplate(templ, result)) {
    SC_LOG_ERROR("createScnPageAgent: Failed to create new sc.n-page");
    return SC_RESULT_ERROR;
  } else if (makeCurrentBool) {
    ScIterator3Ptr curPage = m_memoryCtx.Iterator3(createScnPageKeynodes::rrel_current_scn_page, ScType::EdgeAccessConstPosPerm, ScType::EdgeAccessConstPosPerm);
    while (curPage->Next()) {
      m_memoryCtx.EraseElement(curPage->Get(1));
    }
    m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, createScnPageKeynodes::rrel_current_scn_page, result[1]);
  }

  ScAddr const& pageName = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_2);
  if (pageName.IsValid()) {
    std::string str;
    m_memoryCtx.GetLinkContent(pageName, str);
    m_memoryCtx.HelperSetSystemIdtf(str, result[2]);
  }

  SC_LOG_INFO("createScnPageAgent: New sc.n-page created successfully.");

  return SC_RESULT_OK;
}

bool createScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(createScnPageKeynodes::action_create_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

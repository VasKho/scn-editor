#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "selectScnPageKeynodes.hpp"
#include "selectScnPageAgent.hpp"

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

  ScAddr const& pageName = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_2);
  std::string pageIdtf = "";
  if (pageName.IsValid() && m_memoryCtx.GetElementType(pageName).IsLink()) {
    m_memoryCtx.GetLinkContent(pageName, pageIdtf);
    if (m_memoryCtx.HelperResolveSystemIdtf(pageIdtf).IsValid()) {
      SC_LOG_ERROR("createScnPageAgent: Element with given system identifier already exists");
      utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
      return SC_RESULT_ERROR;
    }
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
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }

  if (pageIdtf != "") {
    m_memoryCtx.HelperSetSystemIdtf(pageIdtf, result[2]);
  }

  SC_LOG_INFO("createScnPageAgent: New sc.n-page created successfully");

  if (makeCurrentBool) {
    ScAddr action = selectScnPageAgent::prepareActionInit(&m_memoryCtx, result[2]);
    utils::AgentUtils::getActionResultIfExists(&m_memoryCtx, action, 400);
  }
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, result[2], true);
  return SC_RESULT_OK;
}

bool createScnPageAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(createScnPageKeynodes::action_create_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

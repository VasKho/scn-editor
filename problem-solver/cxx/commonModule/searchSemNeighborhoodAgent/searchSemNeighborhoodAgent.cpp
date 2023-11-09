#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "searchSemNeighborhoodAgent.hpp"

using namespace common_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(searchSemNeighborhoodAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("searchSemNeighborhoodAgent started");

  // ScAddr const& makeCurrent = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  // bool makeCurrentBool = true;
  // if (makeCurrent.IsValid()) {
  //   std::string str;
  //   m_memoryCtx.GetLinkContent(makeCurrent, str);
  //   makeCurrentBool = (str == "true");
  // }

  // ScTemplate templ;
  // templ.TripleWithRelation(
  //   createScnPageKeynodes::scn_editor,
  //   ScType::EdgeAccessVarPosPerm,
  //   ScType::NodeVarStruct,
  //   ScType::EdgeAccessVarPosPerm,
  //   createScnPageKeynodes::rrel_scn_page
  // );

  // ScTemplateGenResult result;
  // if (!m_memoryCtx.HelperGenTemplate(templ, result)) {
  //   SC_LOG_ERROR("createScnPageAgent: Failed to create new sc.n-page");
  //   return SC_RESULT_ERROR;
  // }

  // ScAddr const& pageName = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_2);
  // if (pageName.IsValid()) {
  //   std::string str;
  //   m_memoryCtx.GetLinkContent(pageName, str);
  //   m_memoryCtx.HelperSetSystemIdtf(str, result[2]);
  // }

  // SC_LOG_INFO("createScnPageAgent: New sc.n-page created successfully.");

  // if (makeCurrentBool) {
  //   ScAddr action = selectScnPageAgent::prepareActionInit(&m_memoryCtx, result[2]);
  //   utils::AgentUtils::getActionResultIfExists(&m_memoryCtx, action, 400);
  // }

  return SC_RESULT_OK;
}

bool searchSemNeighborhoodAgent::checkActionClass(ScAddr const & actionAddr) {
  return false; //m_memoryCtx.HelperCheckEdge(createScnPageKeynodes::action_create_scn_page, actionAddr, ScType::EdgeAccessConstPosPerm);
}

#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "searchSemNeighborhoodKeynodes.hpp"
#include "searchSemNeighborhoodAgent.hpp"

using namespace common_module;
using namespace scAgentsCommon;

SC_AGENT_IMPLEMENTATION(searchSemNeighborhoodAgent) {
  ScAddr const& questionNode = otherAddr;
  if (!checkActionClass(questionNode)) {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("searchSemNeighborhoodAgent started");
  
  ScAddr rootNode = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!rootNode.IsValid()) {
    SC_LOG_ERROR("searchSemNeighborhoodAgent: Invalid ScAddr");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }

  ScTemplate templ;
  templ.TripleWithRelation(
    questionNode,
    ScType::EdgeDCommonVar,
    ScType::NodeVarStruct,
    ScType::EdgeAccessVarPosPerm,
    scAgentsCommon::CoreKeynodes::nrel_answer
  );

  ScTemplateGenResult result;
  if (!m_memoryCtx.HelperGenTemplate(templ, result)) {
    SC_LOG_ERROR("searchSemNeighborhoodAgent: Failed to generate answer node");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, false);
    return SC_RESULT_ERROR;
  }

  addInputTriples(&m_memoryCtx, result[2], rootNode);
  addOutputTriples(&m_memoryCtx, result[2], rootNode);

  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, result[2], rootNode);

  SC_LOG_INFO("searchSemNeighborhoodAgent: Answer generated");
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, questionNode, result[2], true);
  return SC_RESULT_OK;
}

bool searchSemNeighborhoodAgent::checkActionClass(ScAddr const & actionAddr) {
  return m_memoryCtx.HelperCheckEdge(searchSemNeighborhoodKeynodes::action_search_sem_neighborhood, actionAddr, ScType::EdgeAccessConstPosPerm);
}

void searchSemNeighborhoodAgent::addInputTriples(ScMemoryContext* ctx, ScAddr answer, ScAddr node) {
  ScIterator3Ptr inArcs = ctx->Iterator3(ScType::Unknown, ScType::Unknown, node);
  while (inArcs->Next()) {
    ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, inArcs->Get(0));
    ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, inArcs->Get(1));
    ScIterator3Ptr inArcs2 = ctx->Iterator3(ScType::Unknown, ScType::Unknown, inArcs->Get(1));
    while (inArcs2->Next()) {
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, inArcs2->Get(0));
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, inArcs2->Get(1));
    }
    ScIterator3Ptr outArcs2 = ctx->Iterator3(inArcs->Get(1), ScType::Unknown, ScType::Unknown);
    while (outArcs2->Next()) {
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, outArcs2->Get(0));
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, outArcs2->Get(1));
    }
  }
}

void searchSemNeighborhoodAgent::addOutputTriples(ScMemoryContext* ctx, ScAddr answer, ScAddr node) {
  ScIterator3Ptr outArcs = ctx->Iterator3(node, ScType::Unknown, ScType::Unknown);
  while (outArcs->Next()) {
    ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, outArcs->Get(2));
    ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, outArcs->Get(1));
    ScIterator3Ptr inArcs2 = ctx->Iterator3(ScType::Unknown, ScType::Unknown, outArcs->Get(1));
    while (inArcs2->Next()) {
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, inArcs2->Get(0));
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, inArcs2->Get(1));
    }
    ScIterator3Ptr outArcs2 = ctx->Iterator3(outArcs->Get(1), ScType::Unknown, ScType::Unknown);
    while (outArcs2->Next()) {
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, outArcs2->Get(0));
      ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, outArcs2->Get(1));
    }
  }
}

ScAddr searchSemNeighborhoodAgent::prepareActionInit(ScMemoryContext* ctx, ScAddr rootNode) {
  ScAddr actionNode = ctx->CreateNode(ScType::NodeConst);
  ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, searchSemNeighborhoodKeynodes::action_search_sem_neighborhood, actionNode);
  ScAddr edge = ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, actionNode, rootNode);
  ctx->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::rrel_1, edge);
  return actionNode;
}

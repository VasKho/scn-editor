#include "commonModule.hpp"

using namespace common_module;

SC_IMPLEMENT_MODULE(commonModule)

sc_result commonModule::InitializeImpl() {
  if (!searchSemNeighborhoodKeynodes::InitGlobal()) {
    SC_LOG_ERROR("searchSemNeighborhoodAgent keynodes initialization failed");
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "commonModule");
  SC_AGENT_REGISTER(common_module::searchSemNeighborhoodAgent);

  return SC_RESULT_OK;
}

sc_result commonModule::ShutdownImpl() {
  SC_AGENT_UNREGISTER(common_module::searchSemNeighborhoodAgent);

  return SC_RESULT_OK;
}

#include "scnEditorModule.hpp"

using namespace scn_editor_module;

SC_IMPLEMENT_MODULE(scnEditorModule)

sc_result scnEditorModule::InitializeImpl() {
  if (!selectScnPageKeynodes::InitGlobal()) {
    SC_LOG_ERROR("selectScnPageAgent keynodes initialization failed");
    return SC_RESULT_ERROR;
  }
  if (!createScnPageKeynodes::InitGlobal()) {
    SC_LOG_ERROR("createScnPageAgent keynodes initialization failed");
    return SC_RESULT_ERROR;
  }
  if (!openScnPageKeynodes::InitGlobal()) {
    SC_LOG_ERROR("openScnPageAgent keynodes initialization failed");
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "scnEditorModule");
  SC_AGENT_REGISTER(scn_editor_module::selectScnPageAgent);
  SC_AGENT_REGISTER(scn_editor_module::createScnPageAgent);
  SC_AGENT_REGISTER(scn_editor_module::openScnPageAgent);

  return SC_RESULT_OK;
}

sc_result scnEditorModule::ShutdownImpl() {
  SC_AGENT_UNREGISTER(scn_editor_module::selectScnPageAgent);
  SC_AGENT_UNREGISTER(scn_editor_module::createScnPageAgent);
  SC_AGENT_UNREGISTER(scn_editor_module::openScnPageAgent);

  return SC_RESULT_OK;
}

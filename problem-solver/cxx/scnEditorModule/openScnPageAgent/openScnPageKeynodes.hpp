#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "openScnPageKeynodes.generated.hpp"

namespace scn_editor_module {
  class openScnPageKeynodes : public ScObject {
    SC_CLASS()
    SC_GENERATED_BODY()

    public:
    SC_PROPERTY(Keynode("action_open_scn_page"), ForceCreate)
    static ScAddr action_open_scn_page;

    SC_PROPERTY(Keynode("nrel_root_scn_element"), ForceCreate)
    static ScAddr nrel_root_scn_element;
  };

}  // namespace scn_editor_module

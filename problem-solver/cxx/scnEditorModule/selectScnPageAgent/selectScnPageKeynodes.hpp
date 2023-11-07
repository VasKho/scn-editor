#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "selectScnPageKeynodes.generated.hpp"

namespace scn_editor_module {
  class selectScnPageKeynodes : public ScObject {
    SC_CLASS()
    SC_GENERATED_BODY()

    public:
    SC_PROPERTY(Keynode("scn_editor"), ForceCreate)
    static ScAddr scn_editor;
    
    SC_PROPERTY(Keynode("action_select_scn_page"), ForceCreate)
    static ScAddr action_select_scn_page;

    SC_PROPERTY(Keynode("rrel_scn_page"), ForceCreate)
    static ScAddr rrel_scn_page;
    
    SC_PROPERTY(Keynode("rrel_current_scn_page"), ForceCreate)
    static ScAddr rrel_current_scn_page;
  };

}  // namespace scn_editor_module

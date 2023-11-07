#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "createScnPageKeynodes.generated.hpp"

namespace scn_editor_module {
  class createScnPageKeynodes : public ScObject {
    SC_CLASS()
    SC_GENERATED_BODY()

    public:
    SC_PROPERTY(Keynode("scn_editor"), ForceCreate)
    static ScAddr scn_editor;
    
    SC_PROPERTY(Keynode("action_create_scn_page"), ForceCreate)
    static ScAddr action_create_scn_page;

    SC_PROPERTY(Keynode("rrel_scn_page"), ForceCreate)
    static ScAddr rrel_scn_page;
    
    SC_PROPERTY(Keynode("rrel_current_scn_page"), ForceCreate)
    static ScAddr rrel_current_scn_page;
  };

}  // namespace scn_editor_module

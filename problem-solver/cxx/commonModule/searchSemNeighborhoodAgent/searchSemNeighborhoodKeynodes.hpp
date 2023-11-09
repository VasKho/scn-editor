#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "searchSemNeighborhoodKeynodes.generated.hpp"

namespace common_module {
  class searchSemNeighborhoodKeynodes : public ScObject {
    SC_CLASS()
    SC_GENERATED_BODY()

    public:
    SC_PROPERTY(Keynode("action_search_semantic_neighborhood"), ForceCreate)
    static ScAddr action_search_sem_neighborhood;
  };

}  // namespace common_module

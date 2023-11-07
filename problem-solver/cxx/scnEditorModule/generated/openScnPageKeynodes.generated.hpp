#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define openScnPageKeynodes_hpp_11_init  bool _InitInternal(ScAddr const & outputStructure = ScAddr::Empty) override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "openScnPageKeynodes::_InitInternal"); \
    ScSystemIdentifierFiver fiver; \
    bool result = true; \
    return result; \
}


#define openScnPageKeynodes_hpp_11_initStatic static bool _InitStaticInternal(ScAddr const & outputStructure = ScAddr::Empty)  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "openScnPageKeynodes::_InitStaticInternal"); \
    ScSystemIdentifierFiver fiver; \
    bool result = true; \
	ctx.HelperResolveSystemIdtf("action_open_scn_page", ScType::NodeConst, fiver);action_open_scn_page = fiver.addr1; result = result && action_open_scn_page.IsValid(); if (outputStructure.IsValid()) {ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr1);ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr2);ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr3);ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr4);}; \
	ctx.HelperResolveSystemIdtf("nrel_root_scn_element", ScType::NodeConst, fiver);nrel_root_scn_element = fiver.addr1; result = result && nrel_root_scn_element.IsValid(); if (outputStructure.IsValid()) {ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr1);ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr2);ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr3);ctx.CreateEdge(ScType::EdgeAccessConstPosPerm, outputStructure, fiver.addr4);}; \
    return result; \
}


#define openScnPageKeynodes_hpp_11_decl 

#define openScnPageKeynodes_hpp_openScnPageKeynodes_impl 

#undef ScFileID
#define ScFileID openScnPageKeynodes_hpp


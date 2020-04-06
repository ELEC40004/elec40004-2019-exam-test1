#include "mu0.hpp"

#include <cctype>
#include <cassert>

bool mu0_is_label_decl(const string &s)
{
    // TODO
    return false;
}

bool mu0_is_data(const string &s)
{
    // TODO
    return false;
}

// TODO: overload for mu0_is_instruction which takes a string

bool mu0_instruction_has_operand(const string &s)
{
    assert(mu0_is_instruction(s));
    return !( s=="STP" || s=="INP"||s=="OUT" );
}

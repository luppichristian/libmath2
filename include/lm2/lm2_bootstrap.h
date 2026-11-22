#pragma once

// Load declarations first because implementation headers have cyclic dependencies.
#define LM2_PRIVATE_DECLARATION_PHASE
#include <lm2.h>
#undef LM2_PRIVATE_DECLARATION_PHASE

#include <lm2/lm2_implementation.h>
#ifdef LM2_ENABLE_UNPREFIXED_NAMES
#  include <lm2/extensions/lm2_unprefixed_names.h>
#endif

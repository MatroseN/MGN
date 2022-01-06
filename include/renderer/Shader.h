#pragma once

#include "core/core.h"

namespace MGN {
    struct Shader {
        uint32 programId;

		void bind();
		void compile();
    };
}
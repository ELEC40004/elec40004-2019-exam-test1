#!/bin/bash
set -euo pipefail
g++ simulator.cpp mu0_simulate.cpp mu0_disassembly.cpp mu0_io.cpp mu0_assembly.cpp -o simulator
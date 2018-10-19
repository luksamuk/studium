#!/bin/bash
rm callgrind.out.*
valgrind --tool=callgrind ./bin/studium-test
kcachegrind callgrind.out.*


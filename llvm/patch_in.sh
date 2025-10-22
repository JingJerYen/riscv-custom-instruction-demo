#!/bin/bash
git checkout llvmorg-17.0.6
git am 0001-add-my-own-extension-xstar-with-a-single-instruction.patch
git am 0002-add-vwcmul-and-vrotate-instruction-for-complex-numbe.patch

#!/bin/bash
git checkout 76858cc3aa178446584eae52f82e0a933e71f8db
git am 0001-add-my-own-insn-xmac.patch
git am 0002-add-support-to-vwcmul-and-vrotate-for-complex-number.patch
git am 0003-use-CUSTOM-OPCODE3-for-this-xstar-extension.patch

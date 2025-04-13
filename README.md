# RISC-V Custom Instruction Demo

This repository demonstrates how to add a **custom RISC-V instruction** across the full toolchain stack:

- [x] LLVM (compiler support)
- [x] Spike (ISA-level simulator)
- [] QEMU (full system emulator)
- [] Disassembler integration
- [] Assembly & C test case

The goal is to help developers, researchers, and hobbyists understand how to extend the RISC-V ISA in a practical, end-to-end way.

---

## What This Repo Covers

| Component | What's Added |
|----------|--------------|
| **LLVM** | Instruction encoding, pattern matching, codegen support |
| **Spike** | Instruction decoding + execution |
| **QEMU** | Instruction decode + emulation logic |
| **Disassembler** | Readable mnemonic shown for the new opcode |
| **C test case** | Simple program that uses the new instruction |

---

## Instruction Overview

This demo adds a fictional instruction:

```text
xmac rd, rs1, rs2   // rd = (rs1 * rs2) + rd
```

---

## Usage

To apply these patches, change into your llvm-project, spike, or qemu source directory and run the patch script:

```bash
cd llvm-project
../patch_in.sh
```

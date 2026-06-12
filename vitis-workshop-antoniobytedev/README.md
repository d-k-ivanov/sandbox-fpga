# learn-vitis-assets
FPGAs (Field Programmable Gate Arrays) offer a unique balance between flexibility and performance, allowing developers to create highly parallel, low-latency hardware architectures tailored to specific workloads. However, designing hardware in the traditional way by using languages like VHDL or Verilog and often requires deep knowledge of digital logic, timing closure, and microarchitecture design. This barrier makes FPGA development difficult to approach for students, software engineers, and researchers who come from a high-level programming background.

**Vitis HLS** (High-Level Synthesis) bridges that gap.  
Instead of writing RTL by hand, you describe hardware behavior using **C/C++**, and Vitis generates the corresponding hardware implementation. This enables a workflow where algorithms can be **prototyped and iterated quickly**, while still achieving the benefits of FPGA acceleration: parallelism, custom datapaths, and optimized memory access patterns.

But there is a catch.

Writing code in C/C++ is *not enough* to obtain efficient hardware.  
To achieve high performance, low latency, or minimal resource usage, developers must understand how Vitis HLS interprets high-level code and how to **guide synthesis** using *pragmas*, such as:

- `#pragma HLS PIPELINE`
- `#pragma HLS UNROLL`
- `#pragma HLS DATAFLOW`
- `#pragma HLS INLINE`
- `#pragma HLS ARRAY_PARTITION`
- `#pragma HLS ARRAY_RESHAPE`
- `#pragma HLS LOOP_FLATTEN`
- `#pragma HLS LOOP_MERGE`

Each pragma influences how loops execute, how memory is accessed, how architectures are parallelized, and how hardware resources are allocated. Choosing the correct transformation requires understanding both:

1. The **computational structure** of the algorithm  
2. The **hardware implications** of each pragma  

This repository exists to make that learning process **practical, incremental, and hands-on**.

---

## What This Tutorial Provides

This tutorial is structured as a **progressive collection of exercises**, each focusing on a specific optimization concept. Instead of explaining pragmas in isolation, every section:

- Introduces a hardware-relevant concept  
- Presents a working C/C++ example  
- Applies HLS pragmas step-by-step  
- Shows how synthesis changes the architecture  
- Encourages experimentation and measurement  

You will not only *use* the pragmas, you will understand **why and when** to use them.

---

## Who This Tutorial Is For

This repository is designed for:

- Students learning FPGA acceleration for the first time  
- Software developers transitioning into hardware design  
- Researchers exploring hardware-software co-design  
- Engineers preparing to optimize compute kernels on FPGA  

Having Vitis installed and basic C/C++ experience is enough to begin.
---

## Learning Outcomes

By following the sequence of exercises, you will learn to:

- Pipeline loops to improve throughput  
- Unroll loops to expose parallel datapaths  
- Use dataflow to create concurrent hardware tasks  
- Partition arrays to avoid memory access bottlenecks  
- Control resource utilization (LUTs, FFs, DSPs, BRAMs)  
- Refactor algorithms to make them synthesis-friendly  
- Read and interpret Vitis HLS synthesis reports  

These are the core skills needed to design efficient FPGA accelerators.

---

## Repository Structure

| Section | Focus | Key Pragmas |
|--------|--------|-------------|
| **Pipeline** | Pipelining and temporal parallelism| `PIPELINE`|
| **Spatial parallelism** | Unroll and area duplication | `UNROLL`|
| **Internal memory use** | Different types of memory and how to partition them| `ARRAY_PARTITION`,`ARRAY_RESHAPE` |
| **Loop optimization** | Learning to distinguish different types on loops and how to operate with them| `LOOP_MERGE`,`LOOP_FLATTEN` |
|**High level optimization**|Working with sub functions and architecture shaping|`inline`,`DATAFLOW`|
|**Advanced**|These sections include harder exercises that might need deeper understanding of Vitis|**All of the above**|

Start from the first section and proceed in order.  
Every section exercise builds on the previous ones but advanced exercises might need you to revisit them after you've 
finished other sections. 

## Goal of the Repository

The goal is not just to “make code faster.”  
The goal is to **learn to think in hardware**.

Once you understand how code translates to circuits — datapaths, pipelines, memory ports, parallel execution you will be able to design FPGA accelerators that are:

- Faster  
- Smaller  
- More resource efficient

This skillset is rare and valuable and this repository will betraining ground.

---
**All synthesis results have been obtained using  the xa7a12tcpg238-2I part and on Vitis 2024.2**
---



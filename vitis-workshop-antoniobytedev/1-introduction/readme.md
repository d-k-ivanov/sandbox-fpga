# Creating a Vitis HLS Project and Running C Synthesis — Step-by-step

This section describes, in a sequence of concrete steps, how to create a Vitis HLS project, configure its settings, perform C simulation and run C synthesis.

## A. Preparatory Remarks

Before starting a project in Vitis HLS, ensure the following:

- Source files (`.cpp/.c/.h`) and an optional **C testbench** file are available in a known folder.  
- The **top-level function** (the function to be synthesized) must be implemented in the sources.  
- Loop bounds and array sizes used for synthesis should ideally be **compile-time constants**.  
- If using command-line flow, a terminal with access to the `vitis_hls` executable must be available.  
- Preserve synthesis outputs — results and reports are stored under the **solution directory**.  


## B. Creating a New Project (GUI Flow)

### 1. Launch Vitis HLS
Open the Vitis HLS application.

### 2. Create a New Project
Navigate to:
File → New Component → HLS
Fill in the dialog:

- **Project name** (e.g., `my_hls_project`)
- **Project location** (folder where the project will be saved)

- Click **Next**.

### 3. Add Source Files
Add your C/C++ source files containing the **top function** and helper functions.  
You may also add header files.  
Click **Next**.

### 4. Set the Top Function
Select the function that Vitis should synthesize (e.g., `top_function`).  
Click **Next**.

### 5. Choose FPGA Device
Select the FPGA family and chip model to match your deployment.  
This ensures accurate timing and resource estimation.
For this tutorial we will use the xa7a12tcpg238-2I part.

Click **Next**.

### 6. Setting clock and flow
- Set a clock target of 10 ns
- Set flow target to Vivado Ip Flow Target
- Press next


Verify settings and click **Finish**.



## Running C Synthesis 
Run C Synthesis

**1. Click Run C Synthesis on the bottom left corner.**

- The tool performs source analysis, scheduling, and RTL generation. The console shows progress and messages: warnings and errors.

**2. Monitor console messages**

- If synthesis fails, the console will report errors (e.g., illegal code for synthesis, unsupported constructs).

**3. Fix the reported issues in the source code and repeat synthesis.**

**4. Open reports**

After successful synthesis, open the generated reports:

csynth.rpt — synthesis summary.

csynth_design_size.rpt — instruction/operation counts.

csynth.rpt contains Latency, II, pipeline status, and resource summary.

Project folder structure (typical):
```
<project_root>/
  project.tcl
  hls/
    Output/
        report/
          csynth.rpt
        vhdl/ or verilog/
      sim/
```

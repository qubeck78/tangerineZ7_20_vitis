# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_20_wrapper_freertos_eth\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_20_wrapper_freertos_eth\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {tangerineZ7_20_wrapper_freertos_eth}\
-hw {C:\Users\qubeck\Documents\Development\ProjektyVHDL\Zynq7020CoreBoard\tangerineZ7_20\tangerineZ7_20_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -out {C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace}

platform write
platform generate -domains 
platform active {tangerineZ7_20_wrapper_freertos_eth}
domain active {zynq_fsbl}
bsp reload
domain active {freertos10_xilinx_domain}
bsp reload
bsp setlib -name lwip213 -ver 1.0
bsp setlib -name xilffs -ver 5.0
bsp config use_lfn "2"
bsp write
bsp reload
catch {bsp regenerate}
catch {bsp regenerate}
bsp config api_mode "SOCKET_API"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform generate
platform active {tangerineZ7_20_wrapper_freertos_eth}
platform generate -domains 
platform generate
platform generate

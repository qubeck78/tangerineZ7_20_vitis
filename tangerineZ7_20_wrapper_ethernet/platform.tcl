# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_20_wrapper_ethernet\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_20_wrapper_ethernet\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {tangerineZ7_20_wrapper_ethernet}\
-hw {C:\Users\qubeck\Documents\Development\ProjektyVHDL\Zynq7020CoreBoard\tangerineZ7_20\tangerineZ7_20_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace}

platform write
platform generate -domains 
platform active {tangerineZ7_20_wrapper_ethernet}
bsp reload
bsp setlib -name lwip213 -ver 1.0
bsp setlib -name xilffs -ver 5.0
bsp config use_lfn "2"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform generate

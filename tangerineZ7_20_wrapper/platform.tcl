# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_20_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_20_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {tangerineZ7_20_wrapper}\
-hw {C:\Users\qubeck\Documents\Development\ProjektyVHDL\Zynq7020CoreBoard\tangerineZ7_20\tangerineZ7_20_wrapper.xsa}\
-out {C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform write
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp write
platform clean
platform generate
bsp config use_lfn "2"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains zynq_fsbl 
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp setlib -name xilffs -ver 5.0
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
bsp removelib -name xilffs
bsp write
bsp reload
catch {bsp regenerate}
bsp setlib -name xilffs -ver 5.0
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_ps7_cortexa9_0}
bsp setlib -name xiltimer -ver 1.2
bsp write
bsp reload
catch {bsp regenerate}
bsp config use_lfn "2"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
platform clean
bsp reload
bsp config en_interval_timer "true"
bsp config interval_timer "ps7_scutimer_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform active {tangerineZ7_20_wrapper}
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {tangerineZ7_20_wrapper}
platform config -updatehw {C:/Users/qubeck/Documents/Development/ProjektyVHDL/Zynq7020CoreBoard/tangerineZ7_20/tangerineZ7_20_wrapper.xsa}
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {tangerineZ7_20_wrapper}
bsp reload
bsp reload
platform generate -domains 
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {tangerineZ7_20_wrapper}
platform generate -domains 
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {tangerineZ7_20_wrapper}
platform config -updatehw {C:/Users/qubeck/Documents/Development/ProjektyVHDL/Zynq7020CoreBoard/tangerineZ7_20/tangerineZ7_20_wrapper.xsa}
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {tangerineZ7_20_wrapper}
platform config -updatehw {C:/Users/qubeck/Documents/Development/ProjektyVHDL/Zynq7020CoreBoard/tangerineZ7_20/tangerineZ7_20_wrapper.xsa}
platform clean
platform generate
bsp reload
bsp reload
bsp write
bsp removelib -name xiltimer
bsp write
bsp reload
catch {bsp regenerate}
catch {bsp regenerate}
bsp write
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate

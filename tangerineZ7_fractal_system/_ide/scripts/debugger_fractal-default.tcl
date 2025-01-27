# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_fractal_system\_ide\scripts\debugger_fractal-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7Workspace\tangerineZ7_fractal_system\_ide\scripts\debugger_fractal-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Platform Cable USB II 00001510415d01" && level==0 && jtag_device_ctx=="jsn-DLC10-00001510415d01-4ba00477-0"}
fpga -file C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace/fractal/_ide/bitstream/tangerineZ7_20_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/hw/tangerineZ7_20_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace/fractal/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7Workspace/fractal/Debug/fractal.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con

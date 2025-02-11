#
# This file was created by Xilinx Vitis tool.
#


#
# tools
#

RM = rm -f
RMDIR = rm -rf



#
# variables
#

SDCARD_GEN = sdcard_gen
GENERATE_BIF = ::scw::generate_bif

XPFM_PATH = C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/tangerineZ7_20_wrapper.xpfm
SYS_CONFIG = tangerineZ7_20_wrapper
DOMAINS = standalone_domain
BIF_PATH = C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/commanche_system/Debug/system.bif

BITSTREAM_PATH = C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/commanche/_ide/bitstream/tangerineZ7_20_wrapper.bit
SD_FILES = --elf C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/commanche/Debug/commanche.elf,ps7_cortexa9_0

#
# primary build targets
#

package:
	-@echo Generating bif file for the system project
	generate_system_bif.bat 53295 ${XPFM_PATH} ${DOMAINS} ${BIF_PATH}
	${SDCARD_GEN} --xpfm ${XPFM_PATH} --sys_config ${SYS_CONFIG} --bif ${BIF_PATH} --bitstream ${BITSTREAM_PATH} ${SD_FILES}

clean:
	$(RMDIR) ./_sds
	${RMDIR} package
	${RM} system.bif

.PHONY: all package clean

all: package



#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=avr-gcc
CCC=avr-g++
CXX=avr-g++
FC=gfortran
AS=avr-as

# Macros
CND_PLATFORM=AVR2.1-GCC13.2-Linux
CND_DLIB_EXT=so
CND_CONF=Custom
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include /home/dode/dev/avrtft/Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/48b9b4a1/avrtft.o \
	${OBJECTDIR}/_ext/48b9b4a1/bitmaps.o \
	${OBJECTDIR}/_ext/48b9b4a1/cmd.o \
	${OBJECTDIR}/_ext/48b9b4a1/dejavu.o \
	${OBJECTDIR}/_ext/48b9b4a1/display.o \
	${OBJECTDIR}/_ext/48b9b4a1/font.o \
	${OBJECTDIR}/_ext/48b9b4a1/spi.o \
	${OBJECTDIR}/_ext/48b9b4a1/tft.o \
	${OBJECTDIR}/_ext/48b9b4a1/unifont.o \
	${OBJECTDIR}/_ext/48b9b4a1/usart.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/avrtft

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/avrtft: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/avrtft ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/48b9b4a1/avrtft.o: /home/dode/dev/avrtft/avrtft.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/avrtft.o /home/dode/dev/avrtft/avrtft.c

${OBJECTDIR}/_ext/48b9b4a1/bitmaps.o: /home/dode/dev/avrtft/bitmaps.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/bitmaps.o /home/dode/dev/avrtft/bitmaps.c

${OBJECTDIR}/_ext/48b9b4a1/cmd.o: /home/dode/dev/avrtft/cmd.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/cmd.o /home/dode/dev/avrtft/cmd.c

${OBJECTDIR}/_ext/48b9b4a1/dejavu.o: /home/dode/dev/avrtft/dejavu.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/dejavu.o /home/dode/dev/avrtft/dejavu.c

${OBJECTDIR}/_ext/48b9b4a1/display.o: /home/dode/dev/avrtft/display.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/display.o /home/dode/dev/avrtft/display.c

${OBJECTDIR}/_ext/48b9b4a1/font.o: /home/dode/dev/avrtft/font.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/font.o /home/dode/dev/avrtft/font.c

${OBJECTDIR}/_ext/48b9b4a1/spi.o: /home/dode/dev/avrtft/spi.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/spi.o /home/dode/dev/avrtft/spi.c

${OBJECTDIR}/_ext/48b9b4a1/tft.o: /home/dode/dev/avrtft/tft.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/tft.o /home/dode/dev/avrtft/tft.c

${OBJECTDIR}/_ext/48b9b4a1/unifont.o: /home/dode/dev/avrtft/unifont.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/unifont.o /home/dode/dev/avrtft/unifont.c

${OBJECTDIR}/_ext/48b9b4a1/usart.o: /home/dode/dev/avrtft/usart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b9b4a1
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b9b4a1/usart.o /home/dode/dev/avrtft/usart.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
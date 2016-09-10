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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/example/GenSounds.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/Analysis.o \
	${OBJECTDIR}/src/Buffer.o \
	${OBJECTDIR}/src/Edit.o \
	${OBJECTDIR}/src/Effect.o \
	${OBJECTDIR}/src/File.o \
	${OBJECTDIR}/src/Generator.o \
	${OBJECTDIR}/src/Helper.o \
	${OBJECTDIR}/src/Sample.o \
	${OBJECTDIR}/src/loop_generator/Effet.o \
	${OBJECTDIR}/src/loop_generator/EffetFactory.o \
	${OBJECTDIR}/src/loop_generator/LoopGenerator.o \
	${OBJECTDIR}/src/loop_generator/Sound.o \
	${OBJECTDIR}/src/loop_generator/effet/GenSaw.o \
	${OBJECTDIR}/src/loop_generator/effet/GenSine.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audioeditor.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audioeditor.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audioeditor ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/example/GenSounds.o: example/GenSounds.cpp 
	${MKDIR} -p ${OBJECTDIR}/example
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/example/GenSounds.o example/GenSounds.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/Analysis.o: src/Analysis.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Analysis.o src/Analysis.cpp

${OBJECTDIR}/src/Buffer.o: src/Buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Buffer.o src/Buffer.cpp

${OBJECTDIR}/src/Edit.o: src/Edit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Edit.o src/Edit.cpp

${OBJECTDIR}/src/Effect.o: src/Effect.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Effect.o src/Effect.cpp

${OBJECTDIR}/src/File.o: src/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/File.o src/File.cpp

${OBJECTDIR}/src/Generator.o: src/Generator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Generator.o src/Generator.cpp

${OBJECTDIR}/src/Helper.o: src/Helper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Helper.o src/Helper.cpp

${OBJECTDIR}/src/Sample.o: src/Sample.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Sample.o src/Sample.cpp

${OBJECTDIR}/src/loop_generator/Effet.o: src/loop_generator/Effet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/loop_generator
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/loop_generator/Effet.o src/loop_generator/Effet.cpp

${OBJECTDIR}/src/loop_generator/EffetFactory.o: src/loop_generator/EffetFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/loop_generator
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/loop_generator/EffetFactory.o src/loop_generator/EffetFactory.cpp

${OBJECTDIR}/src/loop_generator/LoopGenerator.o: src/loop_generator/LoopGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/loop_generator
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/loop_generator/LoopGenerator.o src/loop_generator/LoopGenerator.cpp

${OBJECTDIR}/src/loop_generator/Sound.o: src/loop_generator/Sound.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/loop_generator
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/loop_generator/Sound.o src/loop_generator/Sound.cpp

${OBJECTDIR}/src/loop_generator/effet/GenSaw.o: src/loop_generator/effet/GenSaw.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/loop_generator/effet
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/loop_generator/effet/GenSaw.o src/loop_generator/effet/GenSaw.cpp

${OBJECTDIR}/src/loop_generator/effet/GenSine.o: src/loop_generator/effet/GenSine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/loop_generator/effet
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/loop_generator/effet/GenSine.o src/loop_generator/effet/GenSine.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audioeditor.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

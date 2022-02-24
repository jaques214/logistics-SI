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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/API_Leitura/API_Leitura.o \
	${OBJECTDIR}/API_Leitura/API_Utils.o \
	${OBJECTDIR}/MyLibs/extras.o \
	${OBJECTDIR}/MyLibs/gestao_encomendas.o \
	${OBJECTDIR}/MyLibs/gestao_faturas.o \
	${OBJECTDIR}/MyLibs/gestao_precos.o \
	${OBJECTDIR}/MyLibs/gestao_utilizadores.o \
	${OBJECTDIR}/MyLibs/menus.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lei_lp_37.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lei_lp_37.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lei_lp_37 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/API_Leitura/API_Leitura.o: API_Leitura/API_Leitura.c
	${MKDIR} -p ${OBJECTDIR}/API_Leitura
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/API_Leitura/API_Leitura.o API_Leitura/API_Leitura.c

${OBJECTDIR}/API_Leitura/API_Utils.o: API_Leitura/API_Utils.c
	${MKDIR} -p ${OBJECTDIR}/API_Leitura
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/API_Leitura/API_Utils.o API_Leitura/API_Utils.c

${OBJECTDIR}/MyLibs/extras.o: MyLibs/extras.c
	${MKDIR} -p ${OBJECTDIR}/MyLibs
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLibs/extras.o MyLibs/extras.c

${OBJECTDIR}/MyLibs/gestao_encomendas.o: MyLibs/gestao_encomendas.c
	${MKDIR} -p ${OBJECTDIR}/MyLibs
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLibs/gestao_encomendas.o MyLibs/gestao_encomendas.c

${OBJECTDIR}/MyLibs/gestao_faturas.o: MyLibs/gestao_faturas.c
	${MKDIR} -p ${OBJECTDIR}/MyLibs
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLibs/gestao_faturas.o MyLibs/gestao_faturas.c

${OBJECTDIR}/MyLibs/gestao_precos.o: MyLibs/gestao_precos.c
	${MKDIR} -p ${OBJECTDIR}/MyLibs
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLibs/gestao_precos.o MyLibs/gestao_precos.c

${OBJECTDIR}/MyLibs/gestao_utilizadores.o: MyLibs/gestao_utilizadores.c
	${MKDIR} -p ${OBJECTDIR}/MyLibs
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLibs/gestao_utilizadores.o MyLibs/gestao_utilizadores.c

${OBJECTDIR}/MyLibs/menus.o: MyLibs/menus.c
	${MKDIR} -p ${OBJECTDIR}/MyLibs
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyLibs/menus.o MyLibs/menus.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

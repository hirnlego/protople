# Project Name
TARGET ?= protople

DEBUG = 1
OPT = -O0
#OPT = -O3

# Sources
CPP_SOURCES = protople.cpp
C_INCLUDES = -IDaisySP/Source -IlibDaisy/src

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

USE_FATFS = 1

# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
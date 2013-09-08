include $(BASE)/configuration.mk

BUILDPATH = $(BUILDBASE)/$(NAME)
OBJECTS = $(addprefix $(BUILDPATH)/, $(addsuffix .o, $(COMPILATION_UNITS)))
STATIC_LIBS = $(addprefix $(BUILDPATH_LIB)/, $(addsuffix .o, $(LIBS)))
DEPENDENCY_TARGETS = $(addsuffix /.DEPENDENCY, $(DEPENDENCY))
DEPENDENCY_OBJECTS = $(addprefix $(BUILDPATH)/, $(addsuffix .o, $(DEPENDENCY)))

ifdef COMPILE_FOR_LOCAL_UNIT_TEST
LIB_BUILD_ENV_VARS = COMPILE_FOR_LOCAL_UNIT_TEST=1
endif

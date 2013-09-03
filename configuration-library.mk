include $(BASE)/configuration.mk

BUILDPATH = $(BUILDBASE)/lib/$(NAME)
OBJECTS = $(addprefix $(BUILDPATH)/, $(addsuffix .o, $(COMPILATION_UNITS)))
STATIC_LIBS = $(addprefix $(BUILDPATH_LIB)/, $(addsuffix .o, $(LIBS)))
DEPENDENCY_TARGETS = $(addsuffix /.DEPENDENCY, $(DEPENDENCY))
DEPENDENCY_OBJECTS = $(addprefix $(BUILDPATH)/, $(addsuffix .o, $(DEPENDENCY)))

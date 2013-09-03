include $(BASE)/build.mk

$(BUILDPATH_LIB)/%.o:
	make -C $(SRC_LIB)/`basename $@ .o`


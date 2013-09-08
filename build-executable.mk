include $(BASE)/build.mk

$(BUILDPATH_LIB)/%.o:
	$(LIB_BUILD_ENV_VARS) make -C $(SRC_LIB)/`basename $@ .o`


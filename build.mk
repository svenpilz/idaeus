$(BUILDPATH):
	mkdir -p $@

$(BUILDPATH)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ $<
	
$(BUILDPATH)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILDPATH)/%.o: %.s
	$(CC) $(CFLAGS) -o $@ $<

$(DEPENDENCY_TARGETS):
	make -C $(dir $@)
	
clean:
	rm -rf $(BUILDPATH)

SUBDIRS = src test prog

.PHONY: subdirs $(SUBDIRS) clean

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ -s


clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir -s; \
		done

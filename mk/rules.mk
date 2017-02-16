.PHONY: doc
UNAME_S   := $(shell uname -s)

ifeq ($(DOC),True)
doc: doc_files
	@rm -f $(BASE)/doc/inc
	@rm -f $(BASE)/doc/src
	@ln -s $(BUILD)/include $(BASE)/doc/inc
	@ln -s $(BUILD)/src $(BASE)/doc/src
ifeq ($(VERBOSE),True)
	make -C $(BASE)/doc html 2>&1 | tee $(DTMP)/doc.out
	@! grep -q -E "WARNING|ERROR" $(DTMP)/doc.out
else
	@echo DOC
	@make -C $(BASE)/doc html 2>&1 | tee $(DTMP)/doc.out > /dev/null
	@! grep -E "WARNING|ERROR" $(DTMP)/doc.out
endif
else
doc:
	@echo Please reconfigure with ./configure --doc.; false
endif

ifeq ($(UNAME_S),Darwin)
STRPCMD := strip -S
else
STRPCMD:= strip --strip-debug
endif

ifneq ($(UNAME_S),Darwin)
CFLAGS += -pthread
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -lrt
else
CFLAGS += -I/usr/local/opt/openssl/include
LDFLAGS += -Wl,-dead_strip
LDFLAGS += -L/usr/local/opt/openssl/lib
endif


$(BUILD)/%.o: $(BASE)/%.c
	@mkdir -p "$(dir $@)"
ifeq ($(VERBOSE),True)
	$(CC) -c -o "$@" "$<" $(CFLAGS)
else
	@echo CC $<
	@$(CC) -c -o "$@" "$<" $(CFLAGS)
endif

$(BUILD)/%.c.rst: $(BASE)/%.c
	@mkdir -p "$(dir $@)"
ifeq ($(VERBOSE),True)
	$(BASE)/mk/c2rst $< $@
else
	@echo RST $<
	@$(BASE)/mk/c2rst $< $@

endif

$(BUILD)/%.h.rst: $(BASE)/%.h
	@mkdir -p "$(dir $@)"
ifeq ($(VERBOSE),True)
	$(BASE)/mk/c2rst $< $@
else
	@echo RST $<
	@$(BASE)/mk/c2rst $< $@
endif

$(BUILD)/libchirp.a: $(LIB_OBJECTS)
ifeq ($(VERBOSE),True)
	ar $(ARFLAGS) $@ $(LIB_OBJECTS) > /dev/null 2> /dev/null
ifeq ($(STRIP),True)
	$(STRPCMD) $@
endif
else
	@echo AR $@
	@ar $(ARFLAGS) $@ $(LIB_OBJECTS) > /dev/null 2> /dev/null
ifeq ($(STRIP),True)
	@echo STRIP $@
	@$(STRPCMD) $@
endif
endif

$(BUILD)/libchirp.so: $(LIB_OBJECTS)
ifeq ($(VERBOSE),True)
	$(CC) -shared -o $@ $(LIB_OBJECTS) $(LDFLAGS)
ifeq ($(STRIP),True)
	$(STRPCMD) $@
endif
else
	@echo LD $@
	@$(CC) -shared -o $@ $(LIB_OBJECTS) $(LDFLAGS)
ifeq ($(STRIP),True)
	@echo STRIP $@
	@$(STRPCMD) $@
endif
endif

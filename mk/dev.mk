.DEFAULT_GOAL := help

CFLAGS := \
	-std=gnu99 \
	-fPIC \
	-Wall \
	-Wextra \
	-pedantic \
	-ffunction-sections \
	-fdata-sections \
	-Wno-unused-function \
	-O0 \
	-ggdb3 \
	--coverage \
	-I"$(BASE)/include" \
	-I"$(BUILD)" \
	$(CFLAGS)

LDFLAGS := \
	--coverage \
	-L"$(BUILD)" \
	-luv \
	-lssl \
	-lm \
	-lpthread \
	-lcrypto

help:  ## Display this help
	@cat $(MAKEFILE_LIST) | grep -E '^[0-9a-zA-Z_-]+:.*?## .*$$' | sort -k1,1 | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

include $(BASE)/mk/rules.mk

$(BUILD)/%_etest: $(BUILD)/%_etest.o libchirp.a
ifeq ($(VERBOSE),True)
	$(CC) -o $@ $< $(BUILD)/libchirp.a $(LDFLAGS)
ifeq ($(STRIP),True)
	$(STRPCMD) $@
endif
else
	@echo LD $@
	@$(CC) -o $@ $< $(BUILD)/libchirp.a $(LDFLAGS)
ifeq ($(STRIP),True)
	@echo STRIP $@
	@$(STRPCMD) $@
endif
endif

$(BUILD)/%.c.gcov: $(BUILD)/%.o
ifeq ($(CC),clang)
	xcrun llvm-cov gcov $<
else
	gcov $<
endif
ifeq ($(IGNORE_COV),True)
	!(grep -v "// NOCOV" $@ | grep -E "\s+#####:"); true
else
	!(grep -v "// NOCOV" $@ | grep -E "\s+#####:")
endif

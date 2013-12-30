
CACOCOS_SRC_FILES := $(shell pushd $(LOCAL_PATH) 1>&2;/bin/find ../../Libraries/cacocos/cacocos -name '*.cpp'; popd 1>&2)

CACOCOS_C_INCLUDES := $(LOCAL_PATH)/../../Libraries/cacocos

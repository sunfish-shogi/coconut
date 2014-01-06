
COCONUT_SRC_FILES := $(shell pushd $(LOCAL_PATH) 1>&2;/bin/find ../../Libraries/coconut/coconut -name '*.cpp'; popd 1>&2)

COCONUT_C_INCLUDES := $(LOCAL_PATH)/../../Libraries/coconut

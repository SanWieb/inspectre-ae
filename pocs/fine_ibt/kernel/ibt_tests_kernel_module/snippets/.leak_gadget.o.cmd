savedcmd_/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o := clang-16 -Wp,-MMD,/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/.leak_gadget.o.d -nostdinc -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ --target=x86_64-linux-gnu -fintegrated-as -Werror=unknown-warning-option -Werror=ignored-optimization-argument -Werror=option-ignored -Werror=unused-command-line-argument -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -m64 -DCC_USING_NOP_MCOUNT -DCC_USING_FENTRY -g -gdwarf-4  -DMODULE  -c -o /home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o /home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.S 

source_/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o := /home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.S

deps_/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \

/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o: $(deps_/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o)

$(deps_/home/ubuntu/native-bhi/InspectorGadget/ae/pocs/fine_ibt/kernel/ibt_tests_kernel_module/./snippets/leak_gadget.o):

# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x64)
  raylib_config = debug_x64
  simple_raytracer_config = debug_x64
  raytracer_config = debug_x64
endif
ifeq ($(config),debug_x86)
  raylib_config = debug_x86
  simple_raytracer_config = debug_x86
  raytracer_config = debug_x86
endif
ifeq ($(config),debug_arm64)
  raylib_config = debug_arm64
  simple_raytracer_config = debug_arm64
  raytracer_config = debug_arm64
endif
ifeq ($(config),release_x64)
  raylib_config = release_x64
  simple_raytracer_config = release_x64
  raytracer_config = release_x64
endif
ifeq ($(config),release_x86)
  raylib_config = release_x86
  simple_raytracer_config = release_x86
  raytracer_config = release_x86
endif
ifeq ($(config),release_arm64)
  raylib_config = release_arm64
  simple_raytracer_config = release_arm64
  raytracer_config = release_arm64
endif

PROJECTS := raylib simple-raytracer raytracer

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

raylib:
ifneq (,$(raylib_config))
	@echo "==== Building raylib ($(raylib_config)) ===="
	@${MAKE} --no-print-directory -C _build -f raylib.make config=$(raylib_config)
endif

simple-raytracer: raylib
ifneq (,$(simple_raytracer_config))
	@echo "==== Building simple-raytracer ($(simple_raytracer_config)) ===="
	@${MAKE} --no-print-directory -C _build -f simple-raytracer.make config=$(simple_raytracer_config)
endif

raytracer: raylib
ifneq (,$(raytracer_config))
	@echo "==== Building raytracer ($(raytracer_config)) ===="
	@${MAKE} --no-print-directory -C _build -f raytracer.make config=$(raytracer_config)
endif

clean:
	@${MAKE} --no-print-directory -C _build -f raylib.make clean
	@${MAKE} --no-print-directory -C _build -f simple-raytracer.make clean
	@${MAKE} --no-print-directory -C _build -f raytracer.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x64"
	@echo "  debug_x86"
	@echo "  debug_arm64"
	@echo "  release_x64"
	@echo "  release_x86"
	@echo "  release_arm64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   raylib"
	@echo "   simple-raytracer"
	@echo "   raytracer"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"
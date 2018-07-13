# NOTE: This makefile is designed to be run from one level up in the directory
# hierarchy compared to where it resides. For instance, if this makefile is
# located at 'output/build/Makefile', then it can be launched as:
# 'make -f build/Makefile' from the 'output' directory.

SHELL=/bin/bash
ifeq ($(CXX),)
  CXX=g++
endif
ifeq ($(CXX_LN),)
  CXX_LN=g++
endif
PKGCONFIG := /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/bin/dst-pe-pkg-config.sh
SPL_BUNDLE_BUILDER := /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/system/impl/bin/spl-bundle-builder
SO_INCLUDE := $(shell $(PKGCONFIG) --cflags dst-spl-pe-install)
SO_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install)
SO_STAND_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install-standalone)
SPL_CXXFLAGS = -Wall -Wno-unused -Wno-sign-compare
SPL_CXXFLAGS += -D_REENTRANT -fPIC -finline-functions -fmessage-length=0
SPL_CXXFLAGS += $(SO_INCLUDE) -O3 -DNDEBUG  -std=gnu++98 
SPL_LDFLAGS = $(SO_LIB)

SPL_TYPES = build/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.o \
            build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o \
            build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o 
SPL_FUNCTIONS = 
SPL_OPERATORS = build/operator/TradeQuoteSrc.o \
                build/operator/InStream.o \
                build/operator/Strategy.o \
                build/operator/Result.o \
                build/operator/PrintHello.o 
SPL_SO_BINS = bin/TradeQuoteSrc.so \
              bin/InStream.so \
              bin/Strategy.so \
              bin/Result.so \
              bin/PrintHello.so 

SPL_ADL_FILE = trading.strategy.Main.adl

SPL_OUTPUT_DIR_ROOT = $(shell printf '%q' '/homes/hny1/Yan.Tian/StreamsDevelopment/NaiveTrading/output/trading.strategy.Main')
SPL_OUTPUT_DIR = $(shell printf '%q' 'BuildConfig')

.PHONY: distclean clean all types functions operators sos bundle toolkits standalone sablink

all: bin types functions operators sos standalone bundle sablink

distclean clean:
	@rm -fr bin/* build/type build/function build/operator build/bundle build/standalone trading.strategy.Main.sab

bin:
	@mkdir -m 775 bin

types: $(SPL_TYPES)

build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o: \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{csv,txt,bin,block,line}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp

build/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.o: \
	    src/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.h \
	    src/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<rstring ticker,rstring date,rstring time,float64 askprice>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.cpp

build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o: \
	    src/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.h \
	    src/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<float64 price,int32 strategy,float64 revenue>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.cpp

build/type:
	-@mkdir -m 775 build/type

operators: $(SPL_OPERATORS)

-include build/operator/TradeQuoteSrc.d
build/operator/TradeQuoteSrc.o: \
	    src/operator/TradeQuoteSrc.h \
	    src/operator/TradeQuoteSrc.cpp\
	    build/dep/operator/TradeQuoteSrc.dep \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] TradeQuoteSrc'
	@$(CXX) -o $@ -MD -I /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/toolkits/spl/impl/nl/include -I /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"trading.strategy.Main.adl\" -c $(SPL_CXXFLAGS) src/operator/TradeQuoteSrc.cpp

-include build/operator/InStream.d
build/operator/InStream.o: \
	    src/operator/InStream.h \
	    src/operator/InStream.cpp\
	    build/dep/operator/InStream.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] InStream'
	@$(CXX) -o $@ -MD -I /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/toolkits/spl/impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"trading.strategy.Main.adl\" -c $(SPL_CXXFLAGS) src/operator/InStream.cpp

-include build/operator/Strategy.d
build/operator/Strategy.o: \
	    src/operator/Strategy.h \
	    src/operator/Strategy.cpp\
	    build/dep/operator/Strategy.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Strategy'
	@$(CXX) -o $@ -MD -I ../../.././impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"trading.strategy.Main.adl\" -c $(SPL_CXXFLAGS) src/operator/Strategy.cpp

-include build/operator/Result.d
build/operator/Result.o: \
	    src/operator/Result.h \
	    src/operator/Result.cpp\
	    build/dep/operator/Result.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Result'
	@$(CXX) -o $@ -MD -I ../../.././impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"trading.strategy.Main.adl\" -c $(SPL_CXXFLAGS) src/operator/Result.cpp

-include build/operator/PrintHello.d
build/operator/PrintHello.o: \
	    src/operator/PrintHello.h \
	    src/operator/PrintHello.cpp\
	    build/dep/operator/PrintHello.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] PrintHello'
	@$(CXX) -o $@ -MD -I /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/toolkits/spl/impl/nl/include -I /homes/hny1/Yan.Tian/IStreamInstallTest/InfoSphere_Streams/4.2.6.0.20180604023502/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"trading.strategy.Main.adl\" -c $(SPL_CXXFLAGS) src/operator/PrintHello.cpp

build/operator:
	-@mkdir -m 775 -p build/operator

functions: $(SPL_FUNCTIONS)

sos: $(SPL_SO_BINS)

SOTradeQuoteSrc = \
	    build/operator/TradeQuoteSrc.o \
	    build/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.o \
	    build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o 

bin/TradeQuoteSrc.so: \
	$(SOTradeQuoteSrc) \
	build/dep/TradeQuoteSrc.so \
	build/ldOptions
	@echo ' [LD-so] so TradeQuoteSrc'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/TradeQuoteSrc.so -fPIC -shared $(SOTradeQuoteSrc) -lstreams-stdtk-runtime -lstreams_boost_iostreams -lstreams_boost_filesystem -lstreams_boost_system $(SPL_LDFLAGS)

SOInStream = \
	    build/operator/InStream.o \
	    build/type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.o \
	    build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o 

bin/InStream.so: \
	$(SOInStream) \
	build/dep/InStream.so \
	build/ldOptions
	@echo ' [LD-so] so InStream'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/InStream.so -fPIC -shared $(SOInStream) $(SPL_LDFLAGS)

SOStrategy = \
	    build/operator/Strategy.o \
	    build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o 

bin/Strategy.so: \
	$(SOStrategy) \
	build/dep/Strategy.so \
	build/ldOptions
	@echo ' [LD-so] so Strategy'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/Strategy.so -fPIC -shared $(SOStrategy) $(SPL_LDFLAGS)

SOResult = \
	    build/operator/Result.o \
	    build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o 

bin/Result.so: \
	$(SOResult) \
	build/dep/Result.so \
	build/ldOptions
	@echo ' [LD-so] so Result'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/Result.so -fPIC -shared $(SOResult) $(SPL_LDFLAGS)

SOPrintHello = \
	    build/operator/PrintHello.o \
	    build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o 

bin/PrintHello.so: \
	$(SOPrintHello) \
	build/dep/PrintHello.so \
	build/ldOptions
	@echo ' [LD-so] so PrintHello'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/PrintHello.so -fPIC -shared $(SOPrintHello) -lstreams-stdtk-runtime -lstreams_boost_iostreams -lstreams_boost_filesystem -lstreams_boost_system $(SPL_LDFLAGS)

SOStrategyWriter = \
	    build/operator/PrintHello.o \
	    build/type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.o 

bin/StrategyWriter.so: \
	$(SOStrategyWriter) \
	build/dep/StrategyWriter.so \
	build/ldOptions
	@echo ' [LD-so] so StrategyWriter'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/StrategyWriter.so -fPIC -shared $(SOStrategyWriter) -lstreams-stdtk-runtime -lstreams_boost_iostreams -lstreams_boost_filesystem -lstreams_boost_system $(SPL_LDFLAGS)

standalone: bin/standalone.exe

build/standalone/standalone.o: \
	    src/standalone/standalone.h \
	    src/standalone/standalone.cpp  \
	    build/cppOptions \
	    | build/standalone
	@echo ' [CXX-standalone] standalone'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/standalone/standalone.cpp

bin/standalone.exe: build/standalone/standalone.o build/ldOptions
	@echo ' [LD-standalone] standalone'
	@$(CXX_LN) $(SPL_CXXFLAGS) -o bin/standalone.exe build/standalone/standalone.o $(SO_STAND_LIB)
	@echo ' [LN-standalone] standalone '
	@ln -sf standalone bin/trading.strategy.Main
build/standalone:
	-@mkdir -m 775 build/standalone

sablink:

	@ln -sf ../trading.strategy.Main.sab bin/sab

bundle: trading.strategy.Main.sab

-include build/dep/trading.strategy.Main.sab.d
trading.strategy.Main.sab: $(SPL_SO_BINS) $(SPL_ADL_FILE) build/dep/trading.strategy.Main.sab.d bin/standalone.exe
	@echo ' [Bundle] trading.strategy.Main.sab'
	@$(SPL_BUNDLE_BUILDER) $(SPL_OUTPUT_DIR_ROOT) $(SPL_OUTPUT_DIR) $(SPL_ADL_FILE) trading.strategy.Main.sab


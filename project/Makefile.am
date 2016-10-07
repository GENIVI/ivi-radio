EXTRA_DIST = autogen.sh

AM_CXXFLAGS = ${COMMON_API_CFLAGS} ${COMMON_API_DBUS_CFLAGS} -DWITH_ADDITIONAL_SERVICES -pthread
AM_LDFLAGS  = ${COMMON_API_LIBS} ${COMMON_API_DBUS_LIBS} -pthread 

AM_CPPFLAGS = \
		-I$(top_srcdir)/src \
		-I$(top_srcdir)/src-gen

CLEANFILES = *~

MAINTAINERCLEANFILES = aclocal.m4 compile config.guess \
                       config.sub configure depcomp install-sh \
                       ltmain.sh Makefile.in missing \
                       config.h config.h.in \
                       *-poky-linux-libtool

bin_PROGRAMS = \
    bin/Middleware \
    bin/Client

bin_Client_SOURCES = \
    src/Client.cpp \
    src/TerminalIO.cpp \
    src-gen/IVIRadio/Station/StationDBusProxy.cpp \
    src-gen/IVIRadio/Station/StationTypes.cpp \
    src-gen/IVIRadio/Types/Types.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceDBusProxy.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceTypesOptions.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceTypes.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationDBusProxy.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationOptions.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationOptionsGetter.cpp

bin_Middleware_SOURCES = \
    src/main.cpp \
    src-gen/IVIRadio/Station/StationStubDefault.cpp \
    src-gen/IVIRadio/Station/StationDBusStubAdapter.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationStubDefault.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationDBusStubAdapter.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationOptions.cpp \
    src-gen/IVIRadio/Configuration/ConfigurationOptionsGetter.cpp \
    src-gen/IVIRadio/Station/StationTypes.cpp \
    src-gen/IVIRadio/Types/Types.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceStubDefault.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceDBusStubAdapter.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceTypesOptions.cpp \
    src-gen/IVIRadio/AdditionalService/AdditionalServiceTypes.cpp \
    src/Interfaces/TunerAdditionalServiceIndividualStub.cpp \
    src/Interfaces/TunerStationIndividualStub.cpp \
    src/Interfaces/TunerConfigurationIndividualStub.cpp \
    src/Dataservices/Announcement.cpp \
    src/Dataservices/DataHelper.cpp \
    src/Dataservices/EPGEvent.cpp \
    src/Dataservices/JournalineObject.cpp \
    src/Dataservices/SubtitleStream.cpp \
    src/Dataservices/Dataservices.cpp \
    src/Dataservices/XMLReader.cpp \
    src/Configuration/CountryVariantConfiguration.cpp \
    src/Configuration/FollowingConfiguration.cpp \
    src/Configuration/AvailableBandConfiguration.cpp \
    src/Configuration/CoverageArea.cpp \
    src/Configuration/Configuration.cpp \
    src/StationManagement.cpp \
    src/Middleware.cpp \
    src/Seek.cpp \
    src/StartTune.cpp \
    src/TerminalIO.cpp \
    src/FileIO.cpp \
    src/Tuner.cpp \
    src/DABTuner.cpp \
    src/FMTuner.cpp \
    src/HMI.cpp \
    src/HMIList.cpp \
    src/TunerList.cpp    

bin_Client_LDADD = ${COMMON_API_LIBS} 
bin_Client_CPPFLAGS = ${AM_CPPFLAGS} ${COMMON_API_CFLAGS} 
bin_Client_CXXFLAGS = ${AM_CXXFLAGS} -std=c++0x 


bin_Middleware_LDADD = ${COMMON_API_LIBS} 
bin_Middleware_CPPFLAGS = ${AM_CPPFLAGS} ${COMMON_API_CFLAGS}
bin_Middleware_CXXFLAGS = ${AM_CXXFLAGS} -std=c++0x

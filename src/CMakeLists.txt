cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(src
        common/CTimer.cpp
        common/CTimer.h
        models/CFrelement.cpp
        models/CFrelement.h
        models/CHyperTime.cpp
        models/CHyperTime.h
        models/CMises.cpp
        models/CMises.h
        models/CPerGaM.cpp
        models/CPerGaM.h
        models/CPythonHyperTime.cpp
        models/CPythonHyperTime.h
        models/CStrategy.cpp
        models/CStrategy.h
        models/CTemporal.cpp
        models/CTemporal.h
        models/CTimeAdaptiveHist.cpp
        models/CTimeAdaptiveHist.h
        models/CTimeHist.cpp
        models/CTimeHist.h
        models/CTimeMean.cpp
        models/CTimeMean.h
        models/CTimeNone.cpp
        models/CTimeNone.h
        featureExtraction.cpp
        featureHolder.cpp
        featureTesting.cpp
        mapMatchInfoListener.cpp
        mapper.cpp
        mapPreprocessor.cpp
        navigator.cpp
        odometryMonitor.cpp
        rosbag.cpp
        statistics.cpp
        statistics.h
        supervisor.cpp
        visualisation.cpp)

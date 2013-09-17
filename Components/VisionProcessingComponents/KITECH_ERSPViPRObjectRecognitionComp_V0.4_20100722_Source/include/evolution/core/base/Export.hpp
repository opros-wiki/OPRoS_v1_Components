//  Copyright (C) 2001-2007, Evolution Robotics, Inc.
//  Any reproduction is strictly prohibited without the explicit
//  written permission of Evolution Robotics, Inc.  All rights reserved.

#ifndef INCLUDE_EVOLUTION_BASE_EXPORT_HPP
#define INCLUDE_EVOLUTION_BASE_EXPORT_HPP


/**
 * @file   evolution/core/base/Export.hpp
 * @brief  Symbol export definitions.
 * @author Copyright (C) 2001-2007, Evolution Robotics, Inc.
 * @ingroup core_base
 */


#include <evolution/core/base/Config.hpp>

/**
 * @def EVOLUTION_EXPORT
 * @brief Symbol export definition.
 */
/**
 * @def EVOLUTION_IMPORT
 * @brief Symbol import definition.
 */
#if     EVOLUTION_PLATFORM_WIN32 && !BUILD_STATIC
#define EVOLUTION_EXPORT  __declspec(dllexport)
#define EVOLUTION_IMPORT  __declspec(dllimport)
#else
#define EVOLUTION_EXPORT
#define EVOLUTION_IMPORT
#endif


#ifndef DOXYGEN_INTERNAL
/* core/base */
#ifdef  EVOLUTION_BUILD_BASE
#define EVOLUTION_EXPORT_BASE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_BASE EVOLUTION_IMPORT
#endif

/* core/util */
#ifdef  EVOLUTION_BUILD_UTIL
#define EVOLUTION_EXPORT_UTIL EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_UTIL EVOLUTION_IMPORT
#endif

/* core/math */
#ifdef  EVOLUTION_BUILD_MATH
#define EVOLUTION_EXPORT_MATH EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_MATH EVOLUTION_IMPORT
#endif

/* core/objrec */
#ifdef  EVOLUTION_BUILD_OBJREC
#define EVOLUTION_EXPORT_OBJREC EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_OBJREC EVOLUTION_IMPORT
#endif

/* core/vision */
#ifdef  EVOLUTION_BUILD_VISION
#define EVOLUTION_EXPORT_VISION EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_VISION EVOLUTION_IMPORT
#endif

/* core/speech */
#ifdef  EVOLUTION_BUILD_SPEECH
#define EVOLUTION_EXPORT_SPEECH EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_SPEECH EVOLUTION_IMPORT
#endif

/* core/objrec */
#ifdef  EVOLUTION_BUILD_OBJREC
#define EVOLUTION_EXPORT_OBJREC EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_OBJREC EVOLUTION_IMPORT
#endif

/* core/resource */
#ifdef  EVOLUTION_BUILD_RESOURCE
#define EVOLUTION_EXPORT_RESOURCE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_RESOURCE EVOLUTION_IMPORT
#endif

/* core/behavior */
#ifdef  EVOLUTION_BUILD_BEHAVIOR
#define EVOLUTION_EXPORT_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_BEHAVIOR EVOLUTION_IMPORT
#endif

/* core/behavior/tests */
#ifdef  EVOLUTION_BUILD_TEST_BEHAVIOR
#define EVOLUTION_EXPORT_TEST_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TEST_BEHAVIOR EVOLUTION_IMPORT
#endif

/* core/task */
#ifdef  EVOLUTION_BUILD_TASK
#define EVOLUTION_EXPORT_TASK EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK EVOLUTION_IMPORT
#endif

/* core/gui */
#ifdef  EVOLUTION_BUILD_GUI
#define EVOLUTION_EXPORT_GUI EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_GUI EVOLUTION_IMPORT
#endif

/* core/bridge */
#ifdef  EVOLUTION_BUILD_BRIDGE
#define EVOLUTION_EXPORT_BRIDGE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_BRIDGE EVOLUTION_IMPORT
#endif

/* core/navigation */
#ifdef  EVOLUTION_BUILD_NAVIGATION
#define EVOLUTION_EXPORT_NAVIGATION EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_NAVIGATION EVOLUTION_IMPORT
#endif

/* core/qt */
#ifdef  EVOLUTION_BUILD_QT
#define EVOLUTION_EXPORT_QT EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_QT EVOLUTION_IMPORT
#endif


/* drivers/audiodriver */
#ifdef  EVOLUTION_BUILD_AUDIODRIVER
#define EVOLUTION_EXPORT_AUDIODRIVER EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_AUDIODRIVER EVOLUTION_IMPORT
#endif

/* drivers/base */
#ifdef  EVOLUTION_BUILD_DRIVERS_BASE
#define EVOLUTION_EXPORT_DRIVERS_BASE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_DRIVERS_BASE EVOLUTION_IMPORT
#endif

/* drivers/morphedface */
#ifdef  EVOLUTION_BUILD_MORPHED_FACE
#define EVOLUTION_EXPORT_MORPHED_FACE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_MORPHED_FACE EVOLUTION_IMPORT
#endif

/* drivers/slam */
#ifdef  EVOLUTION_BUILD_DRIVERS_NORTHSTAR_DRIVER
#define EVOLUTION_EXPORT_DRIVERS_NORTHSTAR_DRIVER EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_DRIVERS_NORTHSTAR_DRIVER EVOLUTION_IMPORT
#endif

/* drivers/rcm */
#ifdef  EVOLUTION_BUILD_RCM
#define EVOLUTION_EXPORT_RCM EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_RCM EVOLUTION_IMPORT
#endif

/* drivers/rcmdriver */
#ifdef  EVOLUTION_BUILD_RCMDRIVER
#define EVOLUTION_EXPORT_RCMDRIVER EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_RCMDRIVER EVOLUTION_IMPORT
#endif

/* drivers/rcm4 */
#ifdef  EVOLUTION_BUILD_RCM4
#define EVOLUTION_EXPORT_RCM4 EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_RCM4 EVOLUTION_IMPORT
#endif

/* drivers/slam */
#ifdef  EVOLUTION_BUILD_DRIVERS_SLAM
#define EVOLUTION_EXPORT_DRIVERS_SLAM EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_DRIVERS_SLAM EVOLUTION_IMPORT
#endif

/* drivers/usbhid */
#ifdef  EVOLUTION_BUILD_USBHID
#define EVOLUTION_EXPORT_USBHID EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_USBHID EVOLUTION_IMPORT
#endif

/* drivers/viavoice */
#ifdef  EVOLUTION_BUILD_VIAVOICE
#define EVOLUTION_EXPORT_VIAVOICE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_VIAVOICE EVOLUTION_IMPORT
#endif

/* drivers/msspeech */
#ifdef  EVOLUTION_BUILD_MSSPEECH
#define EVOLUTION_EXPORT_MSSPEECH EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_MSSPEECH EVOLUTION_IMPORT
#endif

/* drivers/northstar */
#ifdef  EVOLUTION_BUILD_NORTHSTAR
#define EVOLUTION_EXPORT_NORTHSTAR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_NORTHSTAR EVOLUTION_IMPORT
#endif


/* behaviors/emotion */
#ifdef  EVOLUTION_BUILD_EMOTION_BEHAVIOR
#define EVOLUTION_EXPORT_EMOTION_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_EMOTION_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/gui */
#ifdef  EVOLUTION_BUILD_GUI_BEHAVIOR
#define EVOLUTION_EXPORT_GUI_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_GUI_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/navigation */
#ifdef  EVOLUTION_BUILD_NAVIGATION_BEHAVIOR
#define EVOLUTION_EXPORT_NAVIGATION_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_NAVIGATION_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/operator */
#ifdef  EVOLUTION_BUILD_OPERATOR_BEHAVIOR
#define EVOLUTION_EXPORT_OPERATOR_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_OPERATOR_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/resource */
#ifdef  EVOLUTION_BUILD_RESOURCE_BEHAVIOR
#define EVOLUTION_EXPORT_RESOURCE_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_RESOURCE_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/speech */
#ifdef  EVOLUTION_BUILD_SPEECH_BEHAVIOR
#define EVOLUTION_EXPORT_SPEECH_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_SPEECH_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/util */
#ifdef  EVOLUTION_BUILD_UTIL_BEHAVIOR
#define EVOLUTION_EXPORT_UTIL_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_UTIL_BEHAVIOR EVOLUTION_IMPORT
#endif

/* behaviors/vision */
#ifdef  EVOLUTION_BUILD_VISION_BEHAVIOR
#define EVOLUTION_EXPORT_VISION_BEHAVIOR EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_VISION_BEHAVIOR EVOLUTION_IMPORT
#endif

/* gui/wxwindows */
#ifdef  EVOLUTION_BUILD_WXWINDOWS
#define EVOLUTION_EXPORT_WXWINDOWS EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_WXWINDOWS EVOLUTION_IMPORT
#endif

/* tasks/util */
#ifdef  EVOLUTION_BUILD_TASK_UTIL
#define EVOLUTION_EXPORT_TASK_UTIL EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK_UTIL EVOLUTION_IMPORT
#endif

/* tasks/navigation */
#ifdef  EVOLUTION_BUILD_TASK_NAVIGATION
#define EVOLUTION_EXPORT_TASK_NAVIGATION EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK_NAVIGATION EVOLUTION_IMPORT
#endif

/* tasks/vision */
#ifdef  EVOLUTION_BUILD_TASK_VISION
#define EVOLUTION_EXPORT_TASK_VISION EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK_VISION EVOLUTION_IMPORT
#endif

/* tasks/speech */
#ifdef  EVOLUTION_BUILD_TASK_SPEECH
#define EVOLUTION_EXPORT_TASK_SPEECH EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK_SPEECH EVOLUTION_IMPORT
#endif

/* tasks/sensor */
#ifdef  EVOLUTION_BUILD_TASK_RESOURCE
#define EVOLUTION_EXPORT_TASK_RESOURCE EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK_RESOURCE EVOLUTION_IMPORT
#endif

/* tasks/net */
#ifdef  EVOLUTION_BUILD_TASK_NET
#define EVOLUTION_EXPORT_TASK_NET EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_TASK_NET EVOLUTION_IMPORT
#endif

/* tools/python/task */
#ifdef  EVOLUTION_BUILD_PYTHON_TASK_EMBED
#define EVOLUTION_EXPORT_PYTHON_TASK_EMBED EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_PYTHON_TASK_EMBED EVOLUTION_IMPORT
#endif

#ifdef  EVOLUTION_BUILD_PYTHON_TASK_INTERP
#define EVOLUTION_EXPORT_PYTHON_TASK_INTERP EVOLUTION_EXPORT
#else
#define EVOLUTION_EXPORT_PYTHON_TASK_INTERP EVOLUTION_IMPORT
#endif

#endif // DOXYGEN_INTERNAL


#endif  /* INCLUDE_EVOLUTION_BASE_EXPORT_HPP */
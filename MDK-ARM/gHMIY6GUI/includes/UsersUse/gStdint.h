#ifndef _gStdint_h
#define _gStdint_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function module: Common data type definition
 *Implemented functions.
 
 *                              
 * List of functions
 *
 *V1.01: Function Implementation
 *
 *V1.02£º
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
 extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Some common data types
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    /* exact-width signed integer types */
typedef   signed          char gui_int8;
typedef   signed short     int gui_int16;
typedef   signed           int gui_int32;
typedef   signed       __int64 gui_int64;

    /* exact-width unsigned integer types */
typedef unsigned          char gui_uint8;
typedef unsigned short     int gui_uint16;
typedef unsigned           int gui_uint32;
typedef unsigned       __int64 gui_uint64;
	 
typedef gui_uint16             gui_color;
	 
    /* minimum values of exact-width signed integer types */
#define GUI_INT8_MIN                   -128
#define GUI_INT16_MIN                -32768
#define GUI_INT32_MIN          (~0x7fffffff)   /* -2147483648 is unsigned */
#define GUI_INT64_MIN  (~0x7fffffffffffffffll) /* -9223372036854775808 is unsigned */

    /* maximum values of exact-width signed integer types */
#define GUI_INT8_MAX                    127
#define GUI_INT16_MAX                 32767
#define GUI_INT32_MAX            2147483647
#define GUI_INT64_MAX   9223372036854775807ll

    /* maximum values of exact-width unsigned integer types */
#define GUI_UINT8_MAX                   255
#define GUI_UINT16_MAX                65535
#define GUI_UINT32_MAX           4294967295u
#define GUI_UINT64_MAX 18446744073709551615ull	 

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
	
#ifndef GUI_NULL
#define GUI_NULL 0
#endif

#ifndef GUI_ALIGN4
#define	GUI_ALIGN4				__align(4)
#endif 


#ifdef __cplusplus
}
#endif

#endif

// File name: "EnumToString.h"
#undef DECL_ENUM_ELEMENT
#undef DECL_ENUM_CASUAL_ELEMENT
#undef DECL_ENUM
#undef BEGIN_ENUM
#undef END_ENUM
#ifndef GENERATE_ENUM_STRINGS
    #define DECL_ENUM(element) element
    #define DECL_ENUM_ELEMENT(element,msg) element
    #define DECL_ENUM_CASUAL_ELEMENT(element,number,msg) element=number
    #define BEGIN_ENUM( ENUM_NAME ) typedef enum tag##ENUM_NAME
    #define END_ENUM( ENUM_NAME ) ENUM_NAME; const char *GetString##ENUM_NAME(enum tag##ENUM_NAME index);
#else
    #define DECL_ENUM(element) #element
    #define DECL_ENUM_ELEMENT(element,msg) #msg
    #define DECL_ENUM_CASUAL_ELEMENT(element,number,msg) #msg
    #define BEGIN_ENUM( ENUM_NAME ) const char* gs_##ENUM_NAME [] =
    #define END_ENUM( ENUM_NAME ) ; const char *GetString##ENUM_NAME(tag##ENUM_NAME index){ return gs_##ENUM_NAME [index]; }
#endif

#ifndef UEE_TYPES_H
#define UEE_TYPES_H


namespace uee
{
	namespace core
	{

#define UEE_NULL 0;
#define UEE_TRUE 1
#define UEE_FALSE 0

		typedef signed char UEEchar8;
		typedef unsigned char UEEuchar8;
		typedef signed short UEEint16;
		typedef unsigned short UEEuint16;
		typedef signed int  UEEint32;
		typedef unsigned int  UEEuint32;
		typedef signed long  UEEint64;
		typedef unsigned long UEEuint64;
		typedef unsigned char UEEbool;

#define UEE_ENUM_PADDING_ 0x7fffffff

		typedef enum UEEpointer_types {
			UEE_INT16,
			UEE_INT32,
			UEE_INT64,
			UEE_UINT16,
			UEE_UINT32,
			UEE_UINT64,
			UEE_FLOAT,
			UEE_DOUBLE,
			UEEpointer_types_padding = UEE_ENUM_PADDING_
		}tPointer;

		typedef enum UEEface_types {
			UEE_TRIS = 3,
			UEE_QUADS = 4,
			UEEface_types_padding = UEE_ENUM_PADDING_
		}tFace;

		typedef enum UEEresource_types {
			UEE_MESH,
			UEE_AUDIO,
			UEE_ANIMATION,
			UEE_SPRITE,
			UEE_UNKNOWN,
			UEEresource_types_padding = UEE_ENUM_PADDING_
		}tResourceType;

		typedef enum UEEresource_mode {
			UEE_OBJ,
			UEE_3DS,
			UEE_FBX,
			UEE_MP3,
			UEE_ANIMATION_,
			UEE_DEFAULT,
			UEEresource_mode_padding = UEE_ENUM_PADDING_
		}tResourceMode;


		typedef enum UEEface_element_format
		{
			UEE_VTN,
			UEE_VN,
			UEE_VT,
			UEE_V,
			UEE_NONE,
			UEEface_element_format_padding = UEE_ENUM_PADDING_
		}efFace;



		inline int UEEsize_of(tPointer pt)
		{
			switch (pt)
			{
			case UEE_INT16:
				return sizeof(UEEint16);
			case UEE_INT32:
				return sizeof(UEEint32);
			case UEE_INT64:
				return sizeof(UEEint64);
			case UEE_UINT16:
				return sizeof(UEEuint16);
			case UEE_UINT32:
				return sizeof(UEEuint32);
			case UEE_UINT64:
				return sizeof(UEEuint64);
			case UEE_FLOAT:
				return sizeof(float);
			case UEE_DOUBLE:
				return sizeof(double);
			default:
				return sizeof(UEEuchar8);
			}
		}

	}
}
#endif
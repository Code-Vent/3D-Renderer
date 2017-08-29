#ifndef UEE_MATHF_H
#define UEE_MATHF_H

#include<math.h>

#define UEE_PI 3.1415926535897932f
#define SINGLE_PRECISION 0.0000001f
#define FAST_PRECISION 0.001f

namespace uee
{
	namespace math
	{
		struct Mathf
		{
			inline static float Clampf(float value, float min, float max)
			{
				return (value > min) ? ((value < max) ? value : max) : min;
			}

			inline static float Cos(float angle)
			{
				return cos(angle);
			}

			inline static float Sin(float angle)
			{
				return sin(angle);
			}

			inline static float Tan(float angle)
			{
				return tan(angle);
			}

			inline static float Acos(float angle)
			{
				return acos(angle);
			}

			inline static float Asin(float angle)
			{
				return asin(angle);
			}

			inline static float Atan(float angle)
			{
				return tan(angle);
			}

			inline static float Atan2(float y, float x)
			{
				return atan2(y, x);
			}

			inline static float Sqrt(float value)
			{
				return sqrt(value);
			}

			inline static float OneOverSqrt(float value)
			{
				return 1.0f / sqrt(value);
			}

			inline static bool IsFLTEqual(float a, float b, float prec)
			{
				if (a == b)
					return true;
				return (((a - prec) <= b) && (b <= (a + prec)));
			}

			inline static float ToRadians(float degrees)
			{
				return (degrees * (UEE_PI / 180.0f));
			}

			inline static float ToDegrees(float radians)
			{
				return (radians * (180.0f / UEE_PI));
			}

			inline static float Max(float f1, float f2, int*pi = nullptr)
			{
				if (pi)
					return (f1 > f2) ? (*pi = 1, f1) : (*pi = 2, f2);
				return (f1 > f2) ? f1 : f2;
			}

			inline static float Max(float f1, float f2, float f3, int*pi = nullptr)
			{
				if (pi)
					return (f1 > f2) ? ((f1 > f3) ? (*pi = 1, f1) :
						(*pi = 3, f3)) : ((f2 > f3) ? (*pi = 2, f2) : (*pi = 3, f3));

				return (f1 > f2) ? ((f1 > f3) ? (f1) :
					(f3)) : ((f2 > f3) ? (f2) : (f3));
			}

			inline static float Max(float f1, float f2, float f3, float f4, int*pi = nullptr)
			{
				int i = 0, j = 0, k = 0;
				float max1, max2, max3;

				max1 = Max(f1, f2, &j);
				max2 = Max(f3, f4, &k);
				max3 = Max(max1, max2, &i);
				switch (i)
				{
				case 1:
					*pi = j;
					break;
				case 2:
					*pi = k + 2;
					break;
				default:
					break;
				}
				return max3;
			}
		};
	}
}
#endif
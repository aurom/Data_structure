#ifndef _GENERIC_H
#define _GENERIC_H
	typedef struct anytype T;

	struct anytype
	{
		enum 
		{
			typint;
			typlong;
			typulong;
			typuint;
			typfloat;
			typdouble;
			typchar;
			typstring;
			
			typundefined;
		}
		void* value;
	};

#endif
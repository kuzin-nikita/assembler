#include <iostream>
#include <math.h>

double cos(double x, double epsilon)
{
	double res = 0;
	int buf = 0;

	__asm {
		finit

		fldpi

		fadd st(0), st(0)
		fld qword ptr x

		fdiv st(0), st(1)

		fstcw word ptr buf
		mov bx, word ptr buf
		or word ptr buf, 0x400
		fldcw word ptr buf

		frndint

		fmul st(0), st(1)
		fld qword ptr x
		fsub st(0), st(1)
		fxch st(2)

		fstp st(0)
		fstp st(0)

		fmul st(0), st(0) 
		fld qword ptr epsilon 
		fxch st(1)
		fldz

		fld1 
		fld1 

		CALCULATIONS :
		fchs 
			fmul st(0), st(3) 
			fld1 
			faddp st(3), st(0) 
			fdiv st(0), st(2) 
			fld1
			faddp st(3), st(0) 
			fdiv st(0), st(2) 

			fadd st(1), st(0)

			fld st(0)
			fabs 
			fcomp st(5)

			fstsw ax
			sahf

			ja CALCULATIONS

			fld st(1)
			fstp[res]
	}
	return res;
}

int main()
{
	double res = cos(1000000000.0, 0.01);
	printf("%.10lf", res);
	printf("\n");
}

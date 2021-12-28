#include <cstdio>
#include <stdlib.h>

double cos(double x, double eps)
{
	double result = 0;

	__asm
	{
		finit
		fld		eps
		fld		x
		fmul	st(0), st(0)
		fldz 
		fld1 
		fld1 

		CALCULATIONS:
		fchs // ïîòîìó ÷òî çíàêî÷åðåäóåòñÿ ðÿä êîñèíóñà
			fmul    st(0), st(3)
			fld1
			faddp   st(3), st(0)
			fdiv    st(0), st(2)
			fld1
			faddp   st(3), st(0)
			fdiv    st(0), st(2)

			fadd    st(1), st(0) // sum += s[n]

			fld     st(0)
			fabs
			fcomp   st(5)
			fstsw   ax
			sahf
			ja      CALCULATIONS

			fld     st(1)
			fstp	qword ptr result
	}

	return result;
}

int main()
{
	double res1 = cos(0, 0.001);
	double res2 = cos(3.14159265359, 0.001);
	double res3 = cos(6.28318530718, 0.001);


	printf("cos(0) = ");
	printf("%.15lf", res1);
	printf("\n");
	printf("cos(pi) = "); // ïî÷òè Ïè 
	printf("%.15lf", res2);
	printf("\n");
	printf("cos(2*pi) = "); // ïî÷òè 2 Ïè :)
	printf("%.15lf", res3);
	return 0;
}

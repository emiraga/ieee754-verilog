#include <stdio.h>
#include <ctype.h>

float str2float(char *a)
{
	unsigned long out=0,i;
	for(i=0;a[i];i++)
	{
		out *= 2;
		if(a[i] == '1')
			out++;
	}
	return *((float*)&out);
}

void float2str(float in, char *out)
{
	unsigned long a = *(unsigned long*)(&in);
	int i;
	out[32] = 0;
	for(i=31;i>=0;i--)
	{
		out[i] = (a % 2) + '0';
		a /= 2;
	}
}

int main()
{
	float A,B,C;
	int t_success=0, t_count=0;
	char inA[70],inB[70],outC[70];
	
	if( sizeof(long) != sizeof(float) )
	{
		puts("error sizeof long != sizeof float");
		return -1;
	}
	
	while(scanf("%5s",inA) == 1)
	{
		if(strcmp(inA,"TEST1") != 0)
		{
			while(getchar() != '\n');//skip until end of the line
			continue;
		}
		scanf("%s %s %s", inA, inB, outC);
		A = str2float(inA);
		B = str2float(inB);
		C = str2float(outC);
		if(A + B != C)
		{
			char correct[35];
			float2str(A + B, correct);
			printf("Test failed: %f + %f = %f != %f\n",A,B,A+B,C);
			printf("%5s %s + %s = \n%s\n%s\n","", inA, inB, correct, outC);
		}
		else
		{
			printf("Test OK! (%.2f + %.2f = %.2f)\n", A, B, C);
			t_success++;
		}
		t_count++;
	}
	printf("Sucess: %.2lf%%\n",100 * t_success / (double)t_count );
	return 0;
}


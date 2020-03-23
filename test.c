#include <stdio.h>

main()
{
	int a[3] = {1, 2, 3};
	for (int i = 0; i < 3; ++i) printf("%ls", &a[0]);
}

#include <unistd.h>
#include <wchar.h>
#include <stdio.h>

int	main(void)
{
	printf("%zu\n", sizeof(wchar_t));
	wchar_t wc = L'a';
	write(1, &wc, 4);
	return (0);
}

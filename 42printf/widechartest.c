#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main()
{
	char *locale;
	locale = setlocale(LC_CTYPE, "UTF-8");
//	printf("locale: %s\n", locale);
	wchar_t char1 = L'Ñ';

	printf("%ls\n", L"你好，世界");
	printf("%ls\n", L"あああ");
	printf("%ls\n", L"hello");
	printf("%ls\n", L"Ñ");
	printf("%lc\n", char1);
	printf("test string: %s\n", "testing testing");
}

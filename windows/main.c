#include <stdlib.h>  
#include <windows.h> // заголовочный файл, содержащий функции API


// Основная функция - аналог int main() в консольном приложении:
int WINAPI WinMain(HINSTANCE hInstance, // дескриптор экземпляра приложения
		HINSTANCE hPrevInstance, // в Win32 не используется
		LPSTR lpCmdLine, // нужен для запуска окна в режиме командной строки
		int nCmdShow) // режим отображения окна
{
	// Функция вывода окна с кнопкой "ОК" на экран (о параметрах позже)
	MessageBoxW(NULL, L"Данные сохранены.", L"Успех", MB_OK);
	return EXIT_SUCCESS; // возвращаем значение функции
}

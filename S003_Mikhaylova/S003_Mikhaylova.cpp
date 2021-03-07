// S003_Mikhaylova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
	//строка для дальнейшего удаления подстроки
	char string[256];
	//результирующий буффер, куда помещается итоговая строка
	char buffer[256];

	//переменная, отвечающая за значение индекса начала удаляемой подстроки
	int index; 
	//переменная, отвечающая за длину удаляемой подстроки
	int Len;
	//переменная, отвечающая за длину строки, введенной пользователем
	int lengthStr;

	char f[] = "%s";
	char fd[] = "%d";

	std::cout << "Enter your string: ";
	char dataIndex[256] = "Enter the index (start position of the deletion): ";
	char dataLen[256] = "Enter the length of the deletion: ";

	__asm
	{
		//помещаем ссылку на string в esi
		lea esi, string
		push esi

		lea ecx, f
		push ecx

		//ввод с консоли пользователем
		call scanf
		add esp, 8

		lea ebx, dataIndex
		push ebx

		lea ecx, f
		push ecx

		//вывод на консоль данных 
		call printf
		add esp, 8

		lea ebx, index
		push ebx

		lea ecx, fd
		push ecx
		
		call scanf
		add esp, 8

		lea ebx, dataLen
		push ebx

		lea ecx, f
		push ecx

		call printf
		add esp, 8

		lea ebx, Len
		push ebx

		lea ecx, fd
		push ecx

		call scanf
		add esp, 8

		lea ecx, fd
		//кладем в регистр -1
		mov ecx, -1
		dec esi

		push edx
		mov edx, index

		lea ebx, string
		push ebx
		dec ebx

		//ниже происходит определение длины введенной строки 
		LengthOfString :

		//увеличиваем на 1 для задания шага цикла
		inc ecx
			inc ebx
			mov al, [ebx]
			cmp al, 0

			//переход если не равно
			jnz LengthOfString
			push ecx
			
			StartOfDelete :
		cmp index, 0

			//переход если больше или равно
			jge LengthDelete

			mov index, 0

			LengthDelete :
			cmp Len, 0

			//Переход если меньше
			jl NoChange

			indexBiggerLength :
		cmp index, ecx

			//Переход если больше
			jg NoChange

			add esp, 8
			mov lengthStr, ecx
			mov ecx, 0
			dec esi

			lea esi, [string]
			lea edi, [buffer]
			push edi

			mov edx, index

			cmp edx, 1
			jl AddLength

			//переписываем исходные символы до индекса циклом
			StartWrite :
		inc ecx
			lodsb
			stosb
			cmp ecx, edx

			//Переход если не равно
			jne StartWrite

			AddLength :
		add edx, Len
			mov eax, lengthStr

			//исключительная ситуация, если индекс+длина удаляемой строки > длины исходной строки
			cmp edx, eax
			
			jbe EndWrite
			mov edx, eax

			EndWrite :
		inc esi
			inc ecx
			cmp ecx, edx
			jne EndWrite

			ContinueEndWrite :
		lodsb
			stosb
			cmp al, 0
			jnz ContinueEndWrite

			jmp End

			NoChange :
		add esp, 8
			mov ecx, -1
			dec esi
			lea esi, [string]
			lea edi, [buffer]
			push edi

			ContinueNoChange :
		lodsb
			stosb
			cmp al, 0
			jnz ContinueNoChange

			End :
		pop edi
			pop esi
	}

	//выводим результирующую строку после удаления подстроки
	std::cout << "Result string: ";
	std::cout << buffer;
}




// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

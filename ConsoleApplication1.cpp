#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

std::string city_institute; // Глобальная переменная с названием основоного города  
struct Student{ // Структура с информацией об одном ученике. 
	std::string name; 
	std::string city;
	std::string school; 
};


struct Data { // Создание структуры, где будут находится вектор со стундентами, и два словаря, с количеством городов и школ. 
	std::vector<Student> stundent; 
	std::map<std::string, unsigned> city_num;
	std::map<std::string, unsigned> school_max;
};
void qsortRecursive(std::vector<std::string>& a, int n) { // Сортировка пузырьком читай https://nicknixer.ru/programmirovanie/algoritm-puzyrkovoj-sortirovki-odnomernogo-massiva-na-c/
	bool sorted{};
	
	do {
		sorted = true; 
		std::string temp;
		for (int i{ 1 }; i < n; i++) {
			if (a[i - 1] > a[i]) {
				temp = a[i];
				a[i] = a[i-1];
				a[i - 1] = temp;
				sorted = false;
 			}
		}
	
	} while (!sorted);
}

void merge(std::vector<int>& a, int n) // Сортировка слиянием https://prog-cpp.ru/sort-merge
{
	int mid = n / 2; 
	if (n % 2 == 1)
		mid++;
	int h = 1;  
	int* c = (int*)malloc(n * sizeof(int));
	int step;
	while (h < n)
	{
		step = h;
		int i = 0;    
		int j = mid; 
		int k = 0;    
		while (step <= mid)
		{
			while ((i < step) && (j < n) && (j < (mid + step)))
			{  
				if (a[i] < a[j])
				{
					c[k] = a[i];
					i++; k++;
				}
				else {
					c[k] = a[j];
					j++; k++;
				}
			}
			while (i < step)
			{  
				c[k] = a[i];
				i++; k++;
			}
			while ((j < (mid + step)) && (j < n))
			{  
				c[k] = a[j];
				j++; k++;
			}
			step = step + h; 
		}
		h = h * 2;
		 
		for (i = 0; i < n; i++)
			a[i] = c[i];
	}
	 
}
void print_menu() { // функция, которая будет выводить информацию в консоль
	system("cls");  
	printf("Город института\n");
	printf("1. Добавление\n");
	printf("2. Вывод по городам\n");
	printf("3. Вывод всех\n");
	printf("4. Сортировка номеров школ\n");
	printf("5. Сортировка по именам \n");
	printf("6. Сортировка по городам \n");
	printf(">");
}


void adding() {  // функция для добавления студента
	Student student; 
	std::cout << "name";  // Ввод информации 
	std::cin >> student.name;
	std::cout << "city";
	std::cin >> student.city;
	std::cout << "school";
	std::cin >> student.school;
	std::string itog = student.name + ", " + student.city + ", " + (student.school); // соед с ",", чтобы легче работать с данными и записываем в конец файла 
	std::ofstream out;
	out.open("test.txt", std::ios::app);
	if (out.is_open()) {
		out << itog << std::endl;
	}
	out.close();

}
Data read_file() { // функция для загрузки из файла данных 
	Data data; // создаем структуру 
	std::string line; 
	std::ifstream in("test.txt"); // открываем файл 
	if (in.is_open()) {
		while (std::getline(in, line)) { // бесконечный цикл, который проходится по всем строчкам, пока они не законч 
			Student student; 

			int index = line.find(","); // определяем индекс первой ","
			int index_r = line.rfind(","); // определяем индекс второй ","
			line.erase(remove(line.begin(), line.end(), ' '), line.end()); // очищаем строчку от пробелов 
			student.name = line.substr(0, index); // вытаскиваем имя 
			student.city = line.substr(index + 1, index_r - index - 2); // вытаскиваем город
			student.school = line.substr(index_r);// вытаскиваем номер школы
			data.stundent.push_back(student);// добавляем в массив объект 
			if (line.substr(index + 1, index_r - index - 2) != city_institute) { // проверка на город
				data.city_num[line.substr(index + 1, index_r - index - 2)]++;
			}
			else {
				data.school_max[line.substr(index_r)]++;
			}
		}

	}
	in.close();
	return data;
}
void print(std::vector<Student>& student) { // вывод студентов
	for (const auto& entry : student) {
		std::cout << entry.name << std::endl;
		std::cout << entry.city << std::endl;
		std::cout << entry.school << std::endl;
	}
	
}
void print_city(Data data) { // вывод список городов
	for (const auto& entry : data.city_num) {
		std::cout << entry.first << ": " << entry.second << std::endl;

	}
	int current_max = 0;
	std::string arg_max ;
	for (auto it = data.school_max.cbegin(); it != data.school_max.cend(); ++it) {
		if (it->second > current_max) {
			arg_max = it->first;
			current_max = it->second;
		}
	}
	std::cout << "school " << arg_max << "value" << current_max << std::endl; 
}
 
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int variant; 
	std::cout << "Введите название города, где находится институт";
	std::cin >> city_institute;
	do {
		Data data = read_file();
		std::vector<int> num;
		std::vector<std::string>name;
		std::vector<std::string>city;
		print_menu();
		std::cin >> variant;
		switch (variant)
		{
		case 1:
			adding();
			break;
		case 2:
			print_city(data);
			break;
		case 3:
			print(data.stundent);
			break;
		case 4:
			for (auto i : data.stundent) {
				num.push_back(std::stoi(i.school));
			}
			merge(num, num.size());
			for (auto i : num) {
				std::cout << i;
			}
			break;
		case 5:
			for (auto i : data.stundent) {
				name.push_back(i.name);
			}
			qsortRecursive(name, name.size());
			for (auto i : name) {
				std::cout << i << std::endl;
			}

		case 6:
			for (auto i : data.stundent) {
				city.push_back(i.city);
			}
			qsortRecursive(city, city.size());
			for (auto i : city) {
				std::cout << i << std::endl;
			}
		}
		if (variant != 7) {
			system("pause");
		}

	} while (variant != 7);
	
	return 0;
}
 
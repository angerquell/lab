#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string city_institute; 
struct Student{
	std::string name; 
	std::string city;
	std::string school; 
};


struct Data {
	std::vector<Student> stundent; 
	std::map<std::string, unsigned> city_num;
	std::map<std::string, unsigned> school_max;
};
void qsortRecursive(std::vector<std::string>& a, int n) {
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

void merge(std::vector<int>& a, int n)
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
void print_menu() {
	system("cls");  
	printf("What do you want to do?\n");
	printf("1. Add good to list\n");
	printf("2. Print all goods in list\n");
	printf("3. Print the highest price\n");
	printf("4. Print the lowest price\n");
	printf("5. Exit\n");
	printf(">");
}


void adding() {
	Student student; 
	std::cout << "name"; 
	std::cin >> student.name;
	std::cout << "city";
	std::cin >> student.city;
	std::cout << "school";
	std::cin >> student.school;
	std::string itog = student.name + ", " + student.city + ", " + (student.school);
	std::ofstream out;
	out.open("test.txt", std::ios::app);
	if (out.is_open()) {
		out << itog << std::endl;
	}
	out.close();

}
Data read_file() {
	Data data; 
	std::string line; 
	std::ifstream in("test.txt");
	if (in.is_open()) {
		while (std::getline(in, line)) {
			Student student; 

			int index = line.find(",");
			int index_r = line.rfind(",");
			line.erase(remove(line.begin(), line.end(), ' '), line.end());
			student.name = line.substr(0, index);
			student.city = line.substr(index + 1, index_r - index - 2);
			student.school = line.substr(index_r);
			data.stundent.push_back(student);
			if (line.substr(index + 1, index_r - index - 2) != city_institute) {
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
void print(std::vector<Student>& student) {
	for (const auto& entry : student) {
		std::cout << entry.name << std::endl;
		std::cout << entry.city << std::endl;
		std::cout << entry.school << std::endl;
	}
	
}
void print_city(Data data) {
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
 
#include "file_operations.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstring>
#include <cctype>

void FileOperations::generateBinaryNumbers(const std::string& filename, int count) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for (int i = 0; i < count; ++i) {
        int num = dis(gen);
        file.write(reinterpret_cast<char*>(&num), sizeof(int));
    }
}

void FileOperations::copyMultiplesToFile(const std::string& inputFile, const std::string& outputFile, int k) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    if (!in || !out) return;
    
    int num;
    while (in.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        if (num % k == 0) {
            out.write(reinterpret_cast<char*>(&num), sizeof(int));
        }
    }
}

void FileOperations::generateMatrixFile(const std::string& filename, int n) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    int total = n * n;
    for (int i = 0; i < total; ++i) {
        int num = dis(gen);
        file.write(reinterpret_cast<char*>(&num), sizeof(int));
    }
}

void FileOperations::processMatrixFile(const std::string& inputFile, const std::string& outputFile, int n) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) return;
    
    std::vector<int> matrix(n * n, 0);
    int i = 0;
    int num;
    
    while (i < n * n && in.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        matrix[i] = num;
        i++;
    }
    
    int minSum = INT_MAX;
    int minCol = 0;
    
    for (int col = 0; col < n; ++col) {
        int sum = 0;
        for (int row = 0; row < n; ++row) {
            sum += matrix[row * n + col];
        }
        if (sum < minSum) {
            minSum = sum;
            minCol = col;
        }
    }
    
    std::vector<int> newMatrix(n * n);
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            newMatrix[row * n + col] = matrix[row * n + minCol];
        }
    }
    
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) return;
    
    for (int val : newMatrix) {
        out.write(reinterpret_cast<char*>(&val), sizeof(int));
    }
}

void FileOperations::generateToysFile(const std::string& filename, int count) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> priceDis(100.0, 5000.0);
    std::uniform_int_distribution<> ageDis(0, 12);
    
    const char* toyNames[] = {
        "Конструктор Lego", "Мяч", "Кукла", "Машинка", "Пазл",
        "Мягкая игрушка", "Настольная игра", "Конструктор металлический",
        "Радиоуправляемая машина", "Конструктор деревянный"
    };
    
    for (int i = 0; i < count; ++i) {
        Toy toy;
        int nameIndex = std::uniform_int_distribution<>(0, 9)(gen);
        strncpy(toy.name, toyNames[nameIndex], 49);
        toy.name[49] = '\0';
        toy.price = priceDis(gen);
        toy.minAge = ageDis(gen);
        toy.maxAge = toy.minAge + std::uniform_int_distribution<>(1, 5)(gen);
        
        file.write(reinterpret_cast<char*>(&toy), sizeof(Toy));
    }
}

double FileOperations::findMostExpensiveConstructor(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return 0.0;
    
    double maxPrice = 0.0;
    Toy toy;
    
    while (file.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        std::string name(toy.name);
        if (name.find("Конструктор") != std::string::npos) {
            if (toy.price > maxPrice) {
                maxPrice = toy.price;
            }
        }
    }
    
    return maxPrice;
}

void FileOperations::generateTextNumbers1(const std::string& filename, int count) {
    std::ofstream file(filename);
    if (!file) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    
    for (int i = 0; i < count; ++i) {
        file << dis(gen) << "\n";
    }
}

int FileOperations::sumElementsEqualToIndex(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return 0;
    
    int sum = 0;
    int index = 0;
    int num;
    
    while (file >> num) {
        if (num == index) {
            sum += num;
        }
        index++;
    }
    
    return sum;
}

void FileOperations::generateTextNumbers2(const std::string& filename, int count, int numbersPerLine) {
    std::ofstream file(filename);
    if (!file) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 50);
    
    for (int i = 0; i < count; ++i) {
        file << dis(gen);
        if ((i + 1) % numbersPerLine == 0 && i != count - 1) {
            file << "\n";
        } else if (i != count - 1) {
            file << " ";
        }
    }
}

long long FileOperations::multiplyMultiples(const std::string& filename, int k) {
    std::ifstream file(filename);
    if (!file) return 0;
    
    long long product = 1;
    bool found = false;
    int num;
    
    while (file >> num) {
        if (num % k == 0) {
            product *= num;
            found = true;
        }
    }
    
    return found ? product : 0;
}

bool isRussianChar(char c) {
    return (c >= 'А' && c <= 'я') || c == 'ё' || c == 'Ё';
}

bool hasRussianLetters(const std::string& str) {
    for (char c : str) {
        if (isRussianChar(c)) {
            return true;
        }
    }
    return false;
}

void FileOperations::generateTextFile(const std::string& filename, int lineCount) {
    std::ofstream file(filename);
    if (!file) return;
    
    const char* lines[] = {
        "Hello world",
        "Привет мир",
        "Test line without Russian",
        "Строка с русскими буквами",
        "Another test",
        "Ещё одна строка",
        "No russian here",
        "Здесь есть русские",
        "Only english",
        "Только русский"
    };
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    
    for (int i = 0; i < lineCount; ++i) {
        file << lines[dis(gen)] << "\n";
    }
}

void FileOperations::copyLinesWithoutRussian(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);
    if (!in || !out) return;
    
    std::string line;
    while (std::getline(in, line)) {
        if (!hasRussianLetters(line)) {
            out << line << "\n";
        }
    }
}

void FileOperations::showMenu() {
    int choice;
    
    do {
        std::cout << "\n=== ЛАБОРАТОРНАЯ РАБОТА: РАБОТА С ФАЙЛАМИ ===\n";
        std::cout << "1. Задание 1: Копировать кратные числа в бинарный файл\n";
        std::cout << "2. Задание 2: Обработка матрицы из бинарного файла\n";
        std::cout << "3. Задание 3: Найти самый дорогой конструктор\n";
        std::cout << "4. Задание 4: Сумма элементов равных индексу\n";
        std::cout << "5. Задание 5: Произведение кратных чисел\n";
        std::cout << "6. Задание 6: Копировать строки без русских букв\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите задание: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::string inputFile = "numbers1.bin";
                std::string outputFile = "multiples.bin";
                int count, k;
                
                std::cout << "Сколько чисел сгенерировать? ";
                std::cin >> count;
                std::cout << "Введите k: ";
                std::cin >> k;
                
                generateBinaryNumbers(inputFile, count);
                copyMultiplesToFile(inputFile, outputFile, k);
                
                std::cout << "Файл " << inputFile << " создан с " << count << " числами\n";
                std::cout << "Кратные " << k << " скопированы в " << outputFile << "\n";
                break;
            }
            
            case 2: {
                std::string inputFile = "matrix.bin";
                std::string outputFile = "processed_matrix.bin";
                int n;
                
                std::cout << "Введите размер матрицы n: ";
                std::cin >> n;
                
                generateMatrixFile(inputFile, n);
                processMatrixFile(inputFile, outputFile, n);
                
                std::cout << "Матрица " << n << "x" << n << " записана в " << inputFile << "\n";
                std::cout << "Обработанная матрица записана в " << outputFile << "\n";
                break;
            }
            
            case 3: {
                std::string filename = "toys.bin";
                int count;
                
                std::cout << "Сколько игрушек сгенерировать? ";
                std::cin >> count;
                
                generateToysFile(filename, count);
                double maxPrice = findMostExpensiveConstructor(filename);
                
                std::cout << "Файл с игрушками создан: " << filename << "\n";
                std::cout << "Стоимость самого дорогого конструктора: " << maxPrice << " руб.\n";
                break;
            }
            
            case 4: {
                std::string filename = "numbers2.txt";
                int count;
                
                std::cout << "Сколько чисел сгенерировать? ";
                std::cin >> count;
                
                generateTextNumbers1(filename, count);
                int sum = sumElementsEqualToIndex(filename);
                
                std::cout << "Файл создан: " << filename << "\n";
                std::cout << "Сумма элементов равных индексу: " << sum << "\n";
                break;
            }
            
            case 5: {
                std::string filename = "numbers3.txt";
                int count, numbersPerLine, k;
                
                std::cout << "Сколько чисел сгенерировать? ";
                std::cin >> count;
                std::cout << "Сколько чисел в строке? ";
                std::cin >> numbersPerLine;
                std::cout << "Введите k: ";
                std::cin >> k;
                
                generateTextNumbers2(filename, count, numbersPerLine);
                long long product = multiplyMultiples(filename, k);
                
                std::cout << "Файл создан: " << filename << "\n";
                std::cout << "Произведение элементов кратных " << k << ": " << product << "\n";
                break;
            }
            
            case 6: {
                std::string inputFile = "text.txt";
                std::string outputFile = "no_russian.txt";
                int lineCount;
                
                std::cout << "Сколько строк сгенерировать? ";
                std::cin >> lineCount;
                
                generateTextFile(inputFile, lineCount);
                copyLinesWithoutRussian(inputFile, outputFile);
                
                std::cout << "Исходный файл создан: " << inputFile << "\n";
                std::cout << "Строки без русских букв скопированы в: " << outputFile << "\n";
                break;
            }
            
            case 0:
                std::cout << "Выход из программы.\n";
                break;
                
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
        
        if (choice != 0) {
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 0);
}

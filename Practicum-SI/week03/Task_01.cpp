#include <iostream>
#include <fstream>
#pragma warning(disable : 4996);

struct Example
{
    int data;
    char buff[8];
};

Example *examples(int n)
{
    Example *examples = new Example[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> examples[i].data;
        std::cin.ignore();
        std::cin >> examples[i].buff;
    }
    return examples;
}

void addExamplesToFile(std::ofstream &ofs, const Example *examples, int n)
{
    ofs.write((const char *)examples, n * sizeof(Example));
}

size_t getFileSize(std::ifstream &ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    ifs.seekg(currentPos);
    return fileSize;
}

size_t examplesInFile(const char *filePath)
{
    std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cout << "Error while opening file";
        return 0;
    }
    size_t fileSize = getFileSize(ifs);
    // брои колко структури има във файла
    size_t countArraysInFile = fileSize / sizeof(Example);
    ifs.close();
    return countArraysInFile;
}

Example searchedExample(std::ifstream &ifs, const char *pattern, size_t count)
{
    Example *examples = new Example[count];
    ifs.read((char *)examples, count);
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(examples[i].buff, pattern) == 0)
        {
            return examples[i];
        }
    }
    return {-1, "err"};
}

int main()
{
    int n;
    std::cin >> n;
    Example *examples = new Example[n];
    char fileName[1024];
    std::cin.getline(fileName, 1024);
    std::ofstream ofs(fileName, std::ios::out | std::ios::binary | std::ios::app);
    if (!ofs.is_open())
    {
        std::cout << "Error while opening file";
        return 0;
    }
    addExamplesToFile(ofs, examples, n);
    ofs.close();
    delete[] examples;
    return 0;
}

// която казва колко структури от тип Example
// имаме записани във файл с име filePath.
// която проверява дали във файл
// filePath има структура с buff
// стойност равна на pattern. Ако
// има такава я връща. Ако няма такава
// връща нова структура Example със стойности -1 и "err".
// Ако има няколко структури отговарящи на това условие да се върне първата.
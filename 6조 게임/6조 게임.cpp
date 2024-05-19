#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

// salePrice�� ���� ������ �����Ͽ� �ش� ���������� ����� �� �ֵ��� ��
int salePrice;

// ���� ���� �ð��� ����ϴ� ����
std::chrono::system_clock::time_point gameStartTime;

void ShowTitleScreen() {
    const int width = 30; // �׸��� �ʺ�
    const int height = 7; // �׸��� ����

    // ���� �׵θ�
    std::cout << std::string(width, '=') << std::endl;

    // �߰� �κ�
    for (int i = 0; i < height - 4; ++i) {
        if (i == (height - 4) / 2) {
            // �ؽ�Ʈ ��� ����
            std::cout << std::string((width - 20) / 2, ' ') << "X������ ���Ĵ�" << std::endl;
        }
        else {
            // �߰� �� �����ϰ� �� ĭ ���
            std::cout << std::string(width, ' ') << std::endl;
        }
    }

    // �޴� �׸�
    std::cout << "1. �� ����" << std::endl;
    std::cout << "2. �ҷ�����" << std::endl;
    std::cout << "3. ����" << std::endl;

    // �Ʒ��� �׵θ�
    std::cout << std::string(width, '=') << std::endl;
}

void ShowGameScreen(const std::string& id, int level, int money) {
    std::map<int, std::string> levelToStage = {
        {1, "\033[36m�׸���Ʈ �� �ð� �ִ� ��� �����ִ� ���۰���\033[0m"},
        {2, "\033[36m�׸���Ʈ�� ��� �ð� �ִ� ��鰡��\033[0m"},
        {3, "\033[36m�ð� ������ �Լ��� ��鰡��\033[0m"},
        {4, "\033[36m������ ��� ���� ���ÿ� �Լ��� ��鰡��\033[0m"},
        {5, "\033[36m������ ū ��ȭ���� �Լ��� ��鰡��\033[0m"},
        {6, "\033[36m��⵵�� �Լ��� ��鰡��\033[0m"},
        {7, "\033[36m���� ���θ� ��⵵�� �Լ��� ��鰡��\033[0m"},
        {8, "\033[36m���� ��Ʈ�Ӹ��� �Լ��� ��鰡��\033[0m"},
        {9, "\033[36mȫ�� ���⿡ ������ ��鰡��\033[0m"},
        {10, "\033[36m2ȣ���� Ÿ�鼭 �������� ���� ��鰡��\033[0m"},
        {11, "\033[36m���� ���⿡ ������ ��鰡��\033[0m"},
        {12, "\033[36m�ܱ��� �������鵵 ã�ƿ��� ��鰡��\033[0m"},
        {13, "\033[36m�Ϻ� ���⿡ ������ ��鰡��\033[0m"},
        {14, "\033[36m�߱��� �����ϰ� ���ƽþ��� �б��� ���� ��鰡��\033[0m"},
        {15, "\033[36m�ƽþ� ������ ������ ��鰡��\033[0m"},
        {16, "\033[36m�������� �����Ų ��鰡��\033[0m"},
        {17, "\033[36m����þ��� ������ �� ��鰡��\033[0m"},
        {18, "\033[36m�̱� ���� �� ��Ƹ��� ��鰡��\033[0m"},
        {19, "\033[36m���������� ������ ��鰡��\033[0m"},
        {20, "\033[36m�޳��� ���⿡ ������ ��鰡��\033[0m"},
        {21, "\033[36mȭ�� 1ȣ���� ������ ��鰡��\033[0m"},
        {22, "\033[36m�ؿռ� �׶����ֿ� ������ ��鰡��\033[0m"},
        {23, "\033[36m�¾�踦 ������ ��鰡��\033[0m"},
        {24, "\033[36m���ϰ踦 �ѳ���� ��鰡��\033[0m"},
        {25, "\033[36m���ָ� �����ϴ� ��鰡��\033[0m"}
    };

    std::cout << "����: " << id << std::endl;
    std::cout << "���� �ܰ�: " << level << "�ܰ�" << std::endl;
    std::cout << "���� ����: " << levelToStage[level] << std::endl;
    std::cout << "������: " << money << std::endl;

    // UI �޴� �߰�
    std::cout << "=== UI ===" << std::endl;
    std::cout << "1. ���Ը� Ű���" << std::endl;
    std::cout << "2. ���Ը� �Ǹ��Ѵ�" << std::endl;
    std::cout << "3. �����ϱ�" << std::endl;
    std::cout << "4. ����" << std::endl;
}

void SaveGame(const std::map<std::string, std::pair<int, int>>& idData) {
    std::ofstream file("save_game.txt");
    if (file.is_open()) {
        for (const auto& entry : idData) {
            file << entry.first << " " << entry.second.first << " " << entry.second.second << std::endl;
        }
        std::cout << "������ ����Ǿ����ϴ�." << std::endl;
        file.close();
    }
    else {
        std::cout << "���� ���� ����: ������ �� �� �����ϴ�." << std::endl;
    }
}

void SaveGameToCSV(const std::map<std::string, std::pair<int, int>>& idData, const std::string& id, const std::chrono::system_clock::time_point& startTime) {
    std::ifstream checkFile("game_data.csv");
    bool fileExists = checkFile.good();
    checkFile.close();

    std::ofstream csvFile;
    if (fileExists) {
        csvFile.open("game_data.csv", std::ios::app);
    }
    else {
        csvFile.open("game_data.csv");
        // CSV ������ ó�� ������ ���� ��� �ۼ�
        csvFile << "ID,�ܰ�,������,���� ��¥,���� �ð�,���� �ð�" << std::endl;
    }

    if (csvFile.is_open()) {
        // ���� �ð� ��������
        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        auto startDateTime = std::chrono::system_clock::to_time_t(startTime);

        // CSV ���Ͽ� ������ �߰�
        const auto& entry = idData.at(id);
        csvFile << id << "," << entry.first << "," << entry.second << ","
            << std::put_time(std::localtime(&startDateTime), "%Y-%m-%d") << ","
            << std::put_time(std::localtime(&startDateTime), "%H:%M:%S") << ","
            << std::put_time(std::localtime(&currentTime), "%H:%M:%S") << std::endl;

        std::cout << "���� �����Ͱ� CSV ���Ͽ� ����Ǿ����ϴ�." << std::endl;
        csvFile.close();
    }
    else {
        std::cout << "CSV ���� ���� ����: ������ �� �� �����ϴ�." << std::endl;
    }
}

bool LoadGame(std::map<std::string, std::pair<int, int>>& idData, const std::string& id) {
    std::ifstream file("save_game.txt");
    if (file.is_open()) {
        std::string savedId;
        int level, money;
        bool found = false;
        while (file >> savedId >> level >> money) {
            idData[savedId] = std::make_pair(level, money);
            if (savedId == id) {
                found = true;
            }
        }
        file.close();
        if (!found) {
            std::cout << "����� ���̵� �����ϴ�. �� ������ �����մϴ�." << std::endl;
            idData[id] = std::make_pair(1, 10000); // �� ���� �ʱ�ȭ
        }
        return true;
    }
    else {
        std::cout << "����� ���� �����Ͱ� �����ϴ�. �� ������ �����մϴ�." << std::endl;
        idData[id] = std::make_pair(1, 10000); // �� ���� �ʱ�ȭ
        return true;
    }
}

int main() {
    srand(time(0)); // ���� ������ �ʱ�ȭ

    std::map<std::string, std::pair<int, int>> idData;
    std::string id;
    int level = 1;
    int money = 10000; // �������� 10000������ �ʱ�ȭ

    // �� �ܰ躰 ���� Ȯ�� ����
    std::map<int, int> successRates = {
        {1, 100}, {2, 99}, {3, 98}, {4, 97}, {5, 96}, {6, 95}, {7, 94}, {8, 92}, {9, 90},
        {10, 88}, {11, 86}, {12, 84}, {13, 82}, {14, 80}, {15, 77}, {16, 74}, {17, 71},
        {18, 65}, {19, 60}, {20, 55}, {21, 50}, {22, 40}, {23, 30}, {24, 20}, {25, 10}
    };

    // �� �ܰ躰 ���� ����
    std::map<int, int> upgradeCosts = {
        {1, 100}, {2, 200}, {3, 400}, {4, 600}, {5, 800}, {6, 1200}, {7, 1500}, {8, 2000}, {9, 2300},
        {10, 2500}, {11, 2800}, {12, 3000}, {13, 3300}, {14, 3800}, {15, 4000}, {16, 4500}, {17, 6000},
        {18, 7000}, {19, 9000}, {20, 10000}, {21, 30000}, {22, 40000}, {23, 50000}, {24, 100000}, {25, 200000}
    };

    // �Ǹ� ���� ����
    std::map<int, int> salePrices = {
        {1, 0}, {2, 100}, {3, 150}, {4, 300}, {5, 400}, {6, 600}, {7, 800}, {8, 1000}, {9, 2000},
        {10, 2200}, {11, 2500}, {12, 3000}, {13, 4000}, {14, 4500}, {15, 6000}, {16, 8000}, {17, 9000},
        {18, 10000}, {19, 12000}, {20, 15000}, {21, 35000}, {22, 50000}, {23, 70000}, {24, 150000}, {25, 300000}
    };

    while (true) {
        ShowTitleScreen(); // ���� ȭ�� ǥ��

        int menuChoice; // ���� ȭ�鿡���� ������ ����
        std::cin >> menuChoice; // ����� ���� �Է�

        if (menuChoice == 1) {
            std::cout << "���̵� �Է��Ͻʽÿ�: ";
            std::cin >> id; // ����� ���̵� �Է�
            idData[id] = std::make_pair(1, 10000); // �� ���� �ʱ�ȭ
            gameStartTime = std::chrono::system_clock::now(); // ���� ���� �ð� ���
        }
        else if (menuChoice == 2) {
            std::cout << "�ҷ��� ���̵� �Է��Ͻʽÿ�: ";
            std::cin >> id; // �ҷ��� ���̵� �Է�
            if (!LoadGame(idData, id)) {
                std::cout << "�ҷ����� ����. �� ������ �����մϴ�." << std::endl;
                idData[id] = std::make_pair(1, 10000); // �� ���� �ʱ�ȭ
            }
            gameStartTime = std::chrono::system_clock::now(); // ���� ���� �ð� ���
        }
        else if (menuChoice == 3) {
            std::cout << "������ �����մϴ�." << std::endl;
            break;
        }
        else {
            std::cout << "�߸��� �����Դϴ�." << std::endl;
            continue;
        }

        // ���� ȭ�� ǥ��
        while (true) {
            ShowGameScreen(id, idData[id].first, idData[id].second);

            char gameChoice; // ���� ȭ�鿡���� ������ ����
            std::cin >> gameChoice;

            // UI �޴� ó��
            switch (gameChoice) {
            case '1':
                // ���Ը� Ű���
                if (idData[id].first < 25) { // 25�ܰ� ������ ��쿡�� ����
                    // ���� �ܰ�� �Ѿ��
                    if (rand() % 100 < successRates[idData[id].first]) { // ���� ���� ����
                        ++idData[id].first;
                        idData[id].second -= upgradeCosts[idData[id].first]; // ��ȭ ��� ����
                        std::cout << "\033[1;32m�ź���, ���� �� �ɰŶ� �׷���.\033[0m" << idData[id].first - 1 << "\033[33m�ܰ迡��\033[0m " << idData[id].first << "\033[33m�ܰ�� ���׷��̵�Ǿ����ϴ�.\033[0m" << std::endl;
                        SaveGame(idData);
                        SaveGameToCSV(idData, id, gameStartTime);
                    }
                    else {
                        std::cout << "\033[1;31m�� �� �ȵ����� �̷��� ���ݾ���.�ű�� �� ��������?\033[0m " << std::endl;
                        // ���� �� �ܰ踦 1�� �ʱ�ȭ
                        idData[id].first = 1;
                        SaveGame(idData);
                        SaveGameToCSV(idData, id, gameStartTime);
                    }
                }
                else {
                    std::cout << "�ִ� ���׷��̵� �ܰ迡 �����߽��ϴ�." << std::endl;
                    SaveGame(idData);
                    SaveGameToCSV(idData, id, gameStartTime);
                }
                break;

            case '2':
                // ���Ը� �Ǹ��Ѵ�
                salePrice = salePrices[idData[id].first]; // ���� �ܰ迡 �ش��ϴ� �Ǹ� �ݾ�
                idData[id].second += salePrice; // �Ǹŷ� ���� �ݾ� �߰�
                idData[id].first = 1; // ������ 1�� �ʱ�ȭ
                std::cout << "���Ը� �Ǹ��߽��ϴ�. �����ݿ� " << salePrice << "���� �߰��Ǿ����ϴ�." << std::endl;
                SaveGame(idData);
                SaveGameToCSV(idData, id, gameStartTime);
                break;

            case '3':
                // �����ϱ�
                SaveGame(idData);
                SaveGameToCSV(idData, id, gameStartTime);
                break;

            case '4':
                // ����
                SaveGame(idData);
                SaveGameToCSV(idData, id, gameStartTime);
                std::cout << "������ �����մϴ�." << std::endl;
                return 0;

            default:
                std::cout << "�߸��� �����Դϴ�." << std::endl;
            }
        }
    }

    return 0;
}

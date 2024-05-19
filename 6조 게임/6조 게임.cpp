#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

// salePrice를 전역 변수로 정의하여 해당 스코프에서 사용할 수 있도록 함
int salePrice;

// 게임 시작 시간을 기록하는 변수
std::chrono::system_clock::time_point gameStartTime;

void ShowTitleScreen() {
    const int width = 30; // 네모의 너비
    const int height = 7; // 네모의 높이

    // 위쪽 테두리
    std::cout << std::string(width, '=') << std::endl;

    // 중간 부분
    for (int i = 0; i < height - 4; ++i) {
        if (i == (height - 4) / 2) {
            // 텍스트 가운데 정렬
            std::cout << std::string((width - 20) / 2, ' ') << "X종원의 골목식당" << std::endl;
        }
        else {
            // 중간 줄 제외하고 빈 칸 출력
            std::cout << std::string(width, ' ') << std::endl;
        }
    }

    // 메뉴 항목
    std::cout << "1. 새 게임" << std::endl;
    std::cout << "2. 불러오기" << std::endl;
    std::cout << "3. 종료" << std::endl;

    // 아래쪽 테두리
    std::cout << std::string(width, '=') << std::endl;
}

void ShowGameScreen(const std::string& id, int level, int money) {
    std::map<int, std::string> levelToStage = {
        {1, "\033[36m그린벨트 옆 시골에 있는 라면 끓여주는 구멍가게\033[0m"},
        {2, "\033[36m그린벨트를 벗어난 시골에 있는 라면가게\033[0m"},
        {3, "\033[36m시골 읍내로 입성한 라면가게\033[0m"},
        {4, "\033[36m읍내를 벗어나 작은 도시에 입성한 라면가게\033[0m"},
        {5, "\033[36m지방의 큰 번화가에 입성한 라면가게\033[0m"},
        {6, "\033[36m경기도로 입성한 라면가게\033[0m"},
        {7, "\033[36m서울 변두리 경기도로 입성한 라면가게\033[0m"},
        {8, "\033[36m서울 끄트머리에 입성한 라면가게\033[0m"},
        {9, "\033[36m홍대 진출에 성공한 라면가게\033[0m"},
        {10, "\033[36m2호선을 타면서 강남으로 가는 라면가게\033[0m"},
        {11, "\033[36m강남 진출에 성공한 라면가게\033[0m"},
        {12, "\033[36m외국인 관광객들도 찾아오는 라면가게\033[0m"},
        {13, "\033[36m일본 진출에 성공한 라면가게\033[0m"},
        {14, "\033[36m중국을 재패하고 동아시아의 패권을 잡은 라면가게\033[0m"},
        {15, "\033[36m아시아 전역을 지배한 라면가게\033[0m"},
        {16, "\033[36m동유럽을 집어삼킨 라면가게\033[0m"},
        {17, "\033[36m유라시아의 제왕이 된 라면가게\033[0m"},
        {18, "\033[36m미국 빼고 다 잡아먹은 라면가게\033[0m"},
        {19, "\033[36m지구정복에 성공한 라면가게\033[0m"},
        {20, "\033[36m달나라 진출에 성공한 라면가게\033[0m"},
        {21, "\033[36m화성 1호점을 개업한 라면가게\033[0m"},
        {22, "\033[36m해왕성 테라포밍에 성공한 라면가게\033[0m"},
        {23, "\033[36m태양계를 정복한 라면가게\033[0m"},
        {24, "\033[36m은하계를 넘나드는 라면가게\033[0m"},
        {25, "\033[36m우주를 지배하는 라면가게\033[0m"}
    };

    std::cout << "사장: " << id << std::endl;
    std::cout << "현재 단계: " << level << "단계" << std::endl;
    std::cout << "가게 상태: " << levelToStage[level] << std::endl;
    std::cout << "소지금: " << money << std::endl;

    // UI 메뉴 추가
    std::cout << "=== UI ===" << std::endl;
    std::cout << "1. 가게를 키운다" << std::endl;
    std::cout << "2. 가게를 판매한다" << std::endl;
    std::cout << "3. 저장하기" << std::endl;
    std::cout << "4. 종료" << std::endl;
}

void SaveGame(const std::map<std::string, std::pair<int, int>>& idData) {
    std::ofstream file("save_game.txt");
    if (file.is_open()) {
        for (const auto& entry : idData) {
            file << entry.first << " " << entry.second.first << " " << entry.second.second << std::endl;
        }
        std::cout << "게임이 저장되었습니다." << std::endl;
        file.close();
    }
    else {
        std::cout << "게임 저장 실패: 파일을 열 수 없습니다." << std::endl;
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
        // CSV 파일이 처음 생성될 때만 헤더 작성
        csvFile << "ID,단계,소지금,시작 날짜,시작 시간,종료 시간" << std::endl;
    }

    if (csvFile.is_open()) {
        // 현재 시간 가져오기
        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        auto startDateTime = std::chrono::system_clock::to_time_t(startTime);

        // CSV 파일에 데이터 추가
        const auto& entry = idData.at(id);
        csvFile << id << "," << entry.first << "," << entry.second << ","
            << std::put_time(std::localtime(&startDateTime), "%Y-%m-%d") << ","
            << std::put_time(std::localtime(&startDateTime), "%H:%M:%S") << ","
            << std::put_time(std::localtime(&currentTime), "%H:%M:%S") << std::endl;

        std::cout << "게임 데이터가 CSV 파일에 저장되었습니다." << std::endl;
        csvFile.close();
    }
    else {
        std::cout << "CSV 파일 저장 실패: 파일을 열 수 없습니다." << std::endl;
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
            std::cout << "저장된 아이디가 없습니다. 새 게임을 시작합니다." << std::endl;
            idData[id] = std::make_pair(1, 10000); // 새 게임 초기화
        }
        return true;
    }
    else {
        std::cout << "저장된 게임 데이터가 없습니다. 새 게임을 시작합니다." << std::endl;
        idData[id] = std::make_pair(1, 10000); // 새 게임 초기화
        return true;
    }
}

int main() {
    srand(time(0)); // 난수 생성기 초기화

    std::map<std::string, std::pair<int, int>> idData;
    std::string id;
    int level = 1;
    int money = 10000; // 소지금을 10000원으로 초기화

    // 각 단계별 성공 확률 설정
    std::map<int, int> successRates = {
        {1, 100}, {2, 99}, {3, 98}, {4, 97}, {5, 96}, {6, 95}, {7, 94}, {8, 92}, {9, 90},
        {10, 88}, {11, 86}, {12, 84}, {13, 82}, {14, 80}, {15, 77}, {16, 74}, {17, 71},
        {18, 65}, {19, 60}, {20, 55}, {21, 50}, {22, 40}, {23, 30}, {24, 20}, {25, 10}
    };

    // 각 단계별 가격 설정
    std::map<int, int> upgradeCosts = {
        {1, 100}, {2, 200}, {3, 400}, {4, 600}, {5, 800}, {6, 1200}, {7, 1500}, {8, 2000}, {9, 2300},
        {10, 2500}, {11, 2800}, {12, 3000}, {13, 3300}, {14, 3800}, {15, 4000}, {16, 4500}, {17, 6000},
        {18, 7000}, {19, 9000}, {20, 10000}, {21, 30000}, {22, 40000}, {23, 50000}, {24, 100000}, {25, 200000}
    };

    // 판매 가격 설정
    std::map<int, int> salePrices = {
        {1, 0}, {2, 100}, {3, 150}, {4, 300}, {5, 400}, {6, 600}, {7, 800}, {8, 1000}, {9, 2000},
        {10, 2200}, {11, 2500}, {12, 3000}, {13, 4000}, {14, 4500}, {15, 6000}, {16, 8000}, {17, 9000},
        {18, 10000}, {19, 12000}, {20, 15000}, {21, 35000}, {22, 50000}, {23, 70000}, {24, 150000}, {25, 300000}
    };

    while (true) {
        ShowTitleScreen(); // 시작 화면 표시

        int menuChoice; // 시작 화면에서의 선택지 변수
        std::cin >> menuChoice; // 사용자 선택 입력

        if (menuChoice == 1) {
            std::cout << "아이디를 입력하십시오: ";
            std::cin >> id; // 사용자 아이디 입력
            idData[id] = std::make_pair(1, 10000); // 새 게임 초기화
            gameStartTime = std::chrono::system_clock::now(); // 게임 시작 시간 기록
        }
        else if (menuChoice == 2) {
            std::cout << "불러올 아이디를 입력하십시오: ";
            std::cin >> id; // 불러올 아이디 입력
            if (!LoadGame(idData, id)) {
                std::cout << "불러오기 실패. 새 게임을 시작합니다." << std::endl;
                idData[id] = std::make_pair(1, 10000); // 새 게임 초기화
            }
            gameStartTime = std::chrono::system_clock::now(); // 게임 시작 시간 기록
        }
        else if (menuChoice == 3) {
            std::cout << "게임을 종료합니다." << std::endl;
            break;
        }
        else {
            std::cout << "잘못된 선택입니다." << std::endl;
            continue;
        }

        // 게임 화면 표시
        while (true) {
            ShowGameScreen(id, idData[id].first, idData[id].second);

            char gameChoice; // 게임 화면에서의 선택지 변수
            std::cin >> gameChoice;

            // UI 메뉴 처리
            switch (gameChoice) {
            case '1':
                // 가게를 키운다
                if (idData[id].first < 25) { // 25단계 이하인 경우에만 진행
                    // 다음 단계로 넘어가기
                    if (rand() % 100 < successRates[idData[id].first]) { // 성공 여부 판정
                        ++idData[id].first;
                        idData[id].second -= upgradeCosts[idData[id].first]; // 강화 비용 차감
                        std::cout << "\033[1;32m거봐유, 제가 잘 될거라 그랬쥬.\033[0m" << idData[id].first - 1 << "\033[33m단계에서\033[0m " << idData[id].first << "\033[33m단계로 업그레이드되었습니다.\033[0m" << std::endl;
                        SaveGame(idData);
                        SaveGameToCSV(idData, id, gameStartTime);
                    }
                    else {
                        std::cout << "\033[1;31m제 말 안들으니 이렇게 됐잖아유.거기는 좀 따뜻해유?\033[0m " << std::endl;
                        // 실패 시 단계를 1로 초기화
                        idData[id].first = 1;
                        SaveGame(idData);
                        SaveGameToCSV(idData, id, gameStartTime);
                    }
                }
                else {
                    std::cout << "최대 업그레이드 단계에 도달했습니다." << std::endl;
                    SaveGame(idData);
                    SaveGameToCSV(idData, id, gameStartTime);
                }
                break;

            case '2':
                // 가게를 판매한다
                salePrice = salePrices[idData[id].first]; // 현재 단계에 해당하는 판매 금액
                idData[id].second += salePrice; // 판매로 얻은 금액 추가
                idData[id].first = 1; // 레벨을 1로 초기화
                std::cout << "가게를 판매했습니다. 소지금에 " << salePrice << "원이 추가되었습니다." << std::endl;
                SaveGame(idData);
                SaveGameToCSV(idData, id, gameStartTime);
                break;

            case '3':
                // 저장하기
                SaveGame(idData);
                SaveGameToCSV(idData, id, gameStartTime);
                break;

            case '4':
                // 종료
                SaveGame(idData);
                SaveGameToCSV(idData, id, gameStartTime);
                std::cout << "게임을 종료합니다." << std::endl;
                return 0;

            default:
                std::cout << "잘못된 선택입니다." << std::endl;
            }
        }
    }

    return 0;
}

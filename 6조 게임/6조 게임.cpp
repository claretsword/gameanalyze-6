#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

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
        {1, "그린벨트 옆 시골에 있는 라면 끓여주는 구멍가게"},
        {2, "그린벨트를 벗어난 시골에 있는 라면가게"},
        {3, "시골 읍내로 입성한 라면가게"},
        {4, "읍내를 벗어나 작은 도시에 입성한 라면가게"},
        {5, "지방의 큰 번화가에 입성한 라면가게"},
        {6, "경기도로 입성한 라면가게"},
        {7, "서울 변두리 경기도로 입성한 라면가게"},
        {8, "서울 끄트머리에 입성한 라면가게"},
        {9, "홍대 진출에 성공한 라면가게"},
        {10, "2호선을 타면서 강남으로 가는 라면가게"},
        {11, "강남 진출에 성공한 라면가게"},
        {12, "외국인 관광객들도 찾아오는 라면가게"},
        {13, "일본 진출에 성공한 라면가게"},
        {14, "중국을 재패하고 동아시아의 패권을 잡은 라면가게"},
        {15, "아시아 전역을 지배한 라면가게"},
        {16, "동유럽을 집어삼킨 라면가게"},
        {17, "유라시아의 제왕이 된 라면가게"},
        {18, "미국 빼고 다 잡아먹은 라면가게"},
        {19, "지구정복에 성공한 라면가게"},
        {20, "달나라 진출에 성공한 라면가게"},
        {21, "화성 1호점을 개업한 라면가게"},
        {22, "해왕성 테라포밍에 성공한 라면가게"},
        {23, "태양계를 정복한 라면가게"},
        {24, "은하계를 넘나드는 라면가게"},
        {25, "우주를 지배하는 라면가게"}
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

bool LoadGame(std::map<std::string, std::pair<int, int>>& idData, std::string& id) {
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
            std::cout << "저장된 아이디가 없습니다." << std::endl;
        }
        return found;
    }
    else {
        std::cout << "저장된 게임 데이터가 없습니다." << std::endl;
        return false;
    }
}

int main() {
    srand(time(0)); // 난수 생성기 초기화

    std::map<std::string, std::pair<int, int>> idData;
    std::string id;
    int level = 1;
    int money = 10000000; // 소지금을 10000원으로 초기화

    // 각 단계별 성공 확률 설정
    std::map<int, int> successRates = {
        {1, 100}, {2, 99}, {3, 98}, {4, 97}, {5, 96}, {6, 95}, {7, 94}, {8, 92}, {9, 90},
        {10, 88}, {11, 86}, {12, 84}, {13, 82}, {14, 80}, {15, 77}, {16, 74}, {17, 71},
        {18, 65}, {19, 60}, {20, 55}, {21, 50}, {22, 40}, {23, 30}, {24, 20}, {25, 10}
    };

    // 각 단계별 가격 설정
    std::map<int, int> upgradeCosts = {
        {1, 100}, {2, 200}, {3, 300}, {4, 400}, {5, 500}, {6, 600}, {7, 700}, {8, 800}, {9, 900},
        {10, 1000}, {11, 1100}, {12, 1200}, {13, 1300}, {14, 1400}, {15, 1500}, {16, 1600}, {17, 1700},
        {18, 1800}, {19, 1900}, {20, 2000}, {21, 2100}, {22, 2200}, {23, 2300}, {24, 2400}, {25, 2500}
    };

    while (true) {
        ShowTitleScreen(); // 시작 화면 표시

        int menuChoice; // 시작 화면에서의 선택지 변수
        std::cin >> menuChoice; // 사용자 선택 입력

        if (menuChoice == 1) {
            std::cout << "아이디를 입력하십시오: ";
            std::cin >> id; // 사용자 아이디 입력
        }
        else if (menuChoice == 2) {
            std::cout << "불러올 아이디를 입력하십시오: ";
            std::cin >> id; // 불러올 아이디 입력
            while (!LoadGame(idData, id)) {
                std::cout << "불러올 아이디를 입력하십시오: ";
                std::cin >> id; // 불러올 아이디 입력
            }
        }
        else if (menuChoice == 3) {
            std::cout << "게임을 종료합니다." << std::endl;
            break;
        }
        else {
            std::cout << "잘못된 선택입니다." << std::endl;
            continue;
        }

        // 새 게임일 경우 소지금과 레벨 초기화
        if (menuChoice == 1) {
            idData[id] = std::make_pair(1, 10000000);
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
                        std::cout << "가게를 키웠습니다! " << idData[id].first - 1 << "단계에서 " << idData[id].first << "단계로 업그레이드되었습니다." << std::endl;
                        SaveGame(idData);
                    }
                    else {
                        std::cout << "가게를 키우는데 실패했습니다." << std::endl;
                        // 실패 시 단계를 1로 초기화
                        idData[id].first = 1;
                        SaveGame(idData);
                    }
                }
                else {
                    std::cout << "최대 업그레이드 단계에 도달했습니다." << std::endl;
                }
                break;

            case '2':
                // 가게를 판매한다
                std::cout << "가게를 판매하는 기능을 구현해주세요." << std::endl;
                SaveGame(idData);
                break;
            case '3':
                // 저장하기
                SaveGame(idData);
                break;
            case '4':
                std::cout << "게임을 종료합니다." << std::endl;
                SaveGame(idData);
                return 0; // 프로그램 종료
            default:
                std::cout << "잘못된 선택입니다." << std::endl;
            }

            // 게임 종료 조건 확인
            if (idData[id].first >= 25 || idData[id].second <= 0) {
                std::cout << "게임이 종료되었습니다." << std::endl;
                break;
            }
        }
    }

    return 0;
}

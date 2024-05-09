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
        // 중략
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
    int money = 10000; // 소지금을 10000원으로 초기화

    // 각 단계별 성공 확률 설정
    std::map<int, int> successRates = {
        {1, 100}, {2, 99}, {3, 98}, {4, 97}, {5, 96}, {6, 95}, {7, 94}, {8, 92}, {9, 90},
        {10, 88}, {11, 86}, {12, 84}, {13, 82}, {14, 80}, {15, 77}, {16, 74}, {17, 71},
        {18, 65}, {19, 60}, {20, 55}, {21, 50}, {22, 40}, {23, 30}, {24, 20}, {25, 10}
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
            idData[id] = std::make_pair(1, 10000);
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
                        idData[id].second -= 100; // 소지금 차감
                        std::cout << "가게를 키웠습니다! " << idData[id].first - 1 << "단계에서 " << idData[id].first << "단계로 업그레이드되었습니다." << std::endl;
                    }
                    else {
                        std::cout << "가게를 키우는데 실패했습니다." << std::endl;
                    }
                }
                else {
                    std::cout << "최대 업그레이드 단계에 도달했습니다." << std::endl;
                }
                break;
            case '2':
                // 가게를 판매한다
                std::cout << "가게를 판매하는 기능을 구현해주세요." << std::endl;
                break;
            case '3':
                // 저장하기
                SaveGame(idData);
                break;
            case '4':
                // 종료
                std::cout << "게임을 종료합니다." << std::endl;
                return 0;
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

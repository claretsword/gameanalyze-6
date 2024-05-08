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

    // 아래쪽 테두리
    std::cout << std::string(width, '=') << std::endl;
}

void ShowGameScreen(const std::string& id, int level, int money) {
    std::cout << "사장: " << id << std::endl;
    std::cout << "현재 레벨: " << level << std::endl;
    std::cout << "소지금: " << money << std::endl;
    // 나머지 게임 화면 출력
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
        std::string loadedId;
        int level, money;
        while (file >> loadedId >> level >> money) {
            idData[loadedId] = { level, money };
        }
        file.close();
        if (idData.find(id) != idData.end()) {
            std::cout << "게임이 불러와졌습니다." << std::endl;
            return true;
        }
        else {
            std::cout << "저장된 게임 데이터가 없습니다. 다시 입력해주세요." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "저장된 게임 데이터가 없습니다. 다시 입력해주세요." << std::endl;
        return false;
    }
}

int main() {
    srand(time(0)); // 난수 생성기 초기화

    std::map<std::string, std::pair<int, int>> idData;
    std::string id;
    int level = 1;
    int money = 1000;

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
    else {
        std::cout << "잘못된 선택입니다." << std::endl;
        return 0;
    }

    ShowGameScreen(id, idData[id].first, idData[id].second); // 게임 화면 표시

    char gameChoice; // 게임 화면에서의 선택지 변수
    std::cin >> gameChoice;

    if (gameChoice == '3') {
        SaveGame(idData); // 게임 저장
    }

    return 0;
}

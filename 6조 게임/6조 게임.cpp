#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

void ShowTitleScreen() {
    const int width = 30; // 네모의 너비
    const int height = 5; // 네모의 높이

    // 위쪽 테두리
    std::cout << std::string(width, '=') << std::endl;

    // 중간 부분
    for (int i = 0; i < height - 3; ++i) {
        if (i == (height - 3) / 2) {
            // 텍스트 가운데 정렬
            std::cout << std::string((width - 20) / 2, ' ') << "X종원의 골목식당" << std::endl;
        }
        else {
            // 중간 줄 제외하고 빈 칸 출력
            std::cout << std::string(width, ' ') << std::endl;
        }
    }

    // 아래쪽 테두리
    std::cout << std::string(width, '=') << std::endl;

    std::cout << "아이디를 입력하십시오: ";
}

void ShowGameScreen(const std::string& id) {
    std::cout << "사장: " << id << std::endl;
    std::cout << "현재 레벨: " << 1 << std::endl; // 임시로 1로 설정
    std::cout << "소지금: " << 1000 << std::endl; // 임시로 1000으로 설정
    // 나머지 게임 화면 출력
}

int main() {
    srand(time(0)); // 난수 생성기 초기화

    ShowTitleScreen(); // 시작 화면 표시
    std::string id;
    std::getline(std::cin, id); // 사용자 아이디 입력

    ShowGameScreen(id); // 게임 화면 표시

    return 0;
}

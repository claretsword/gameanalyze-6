#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// 세이브 함수
void saveGame(const string& playerName) {
    ofstream saveFile("save_game.txt");
    if (saveFile.is_open()) {
        saveFile << playerName << endl;
        // 추가적으로 세이브해야 할 게임 상태가 있다면 이곳에 저장합니다.
        saveFile.close();
        cout << "게임이 성공적으로 저장되었습니다." << endl;
    }
    else {
        cout << "세이브 파일을 열 수 없습니다." << endl;
    }
}

// 로드 함수
void loadGame(string& playerName) {
    ifstream loadFile("save_game.txt");
    if (loadFile.is_open()) {
        getline(loadFile, playerName);
        // 추가적으로 로드해야 할 게임 상태가 있다면 이곳에 로드합니다.
        loadFile.close();
        cout << "게임이 성공적으로 로드되었습니다." << endl;
    }
    else {
        cout << "로드할 세이브 파일이 없습니다." << endl;
    }
}

int main() {
    string playerName;
    bool isNewGame = true;

    // 세이브 파일이 존재하는지 확인하여 로드 또는 새로운 게임 시작
    ifstream saveFile("save_game.txt");
    if (saveFile.is_open()) {
        saveFile.close();
        char choice;
        cout << "이전 세이브 파일이 있습니다. 로드하시겠습니까? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            loadGame(playerName);
            isNewGame = false;
        }
        cin.ignore(); // 버퍼 비우기
    }

    if (isNewGame) {
        // 새로운 게임 시작
        cout << "안녕하세요! 게임을 시작합니다." << endl;
        cout << "플레이어의 이름을 입력하세요: ";
        getline(cin, playerName);
    }

    cout << "환영합니다, " << playerName << "님!" << endl;

    // 게임 진행 루프
    bool playing = true;
    while (playing) {
        // 게임 로직을 이곳에 작성하세요.

        // 세이브 및 종료 옵션 출력
        cout << "게임을 저장하려면 's'를 입력하세요. 종료하려면 'q'를 입력하세요: ";
        string input;
        getline(cin, input);
        if (input == "s" || input == "save") {
            saveGame(playerName);
        }
        else if (input == "q" || input == "quit") {
            playing = false;
        }
    }

    cout << "게임을 종료합니다. 다음에 또 만나요!" << endl;

    return 0;
}
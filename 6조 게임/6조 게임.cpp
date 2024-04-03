#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Player {
    string name;
    int HP;
    int MP;
    int attack;
};

// 세이브 함수
void saveGame(const Player& player) {
    ofstream saveFile("save_game.txt");
    if (saveFile.is_open()) {
        saveFile << player.name << endl;
        saveFile << player.HP << endl;
        saveFile << player.MP << endl;
        saveFile << player.attack << endl;
        saveFile.close();
        cout << "게임이 성공적으로 저장되었습니다." << endl;
    }
    else {
        cout << "세이브 파일을 열 수 없습니다." << endl;
    }
}

// 로드 함수
void loadGame(Player& player) {
    ifstream loadFile("save_game.txt");
    if (loadFile.is_open()) {
        getline(loadFile, player.name);
        loadFile >> player.HP;
        loadFile >> player.MP;
        loadFile >> player.attack;
        loadFile.close();
        cout << "게임이 성공적으로 로드되었습니다." << endl;
    }
    else {
        cout << "로드할 세이브 파일이 없습니다." << endl;
    }
}

// 플레이어의 스탯을 초기화하는 함수
void initializePlayer(Player& player, const string& playerName, int initialHP, int initialMP, int initialAttack) {
    player.name = playerName;
    player.HP = initialHP;
    player.MP = initialMP;
    player.attack = initialAttack;
}

int main() {
    Player player;
    string playerName;
    int initialHP = 100;
    int initialMP = 80;
    int initialAttack = 5;

    // 세이브 파일이 존재하는지 확인하여 로드 또는 새로운 게임 시작
    ifstream saveFile("save_game.txt");
    if (saveFile.is_open()) {
        saveFile.close();
        char choice;
        cout << "이전 세이브 파일이 있습니다. 로드하시겠습니까? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            loadGame(player);
        }
        else {
            // 새로운 게임 시작
            cout << "플레이어의 이름을 입력하세요: ";
            cin.ignore(); // 이전에 남아있는 '\n' 문자를 지움
            getline(cin, playerName);
            initializePlayer(player, playerName, initialHP, initialMP, initialAttack);
        }
    }
    else {
        // 새로운 게임 시작
        cout << "플레이어의 이름을 입력하세요: ";
        getline(cin, playerName);
        initializePlayer(player, playerName, initialHP, initialMP, initialAttack);
    }

    cout << "\n환영합니다, " << player.name << "님!" << endl;
    cout << "HP: " << player.HP << endl;
    cout << "MP: " << player.MP << endl;
    cout << "공격력: " << player.attack << endl;

    // 게임 진행 루프
    bool playing = true;
    while (playing) {
        // 게임 로직을 이곳에 작성하세요.

        // 메뉴 출력
        cout << "\n===== 메뉴 =====" << endl;
        cout << "m. 메뉴 보기" << endl;

        // 'm' 버튼을 누르면 메뉴가 나오도록 설정
        char menuButton;
        cin >> menuButton;
        if (menuButton == 'M') {
            cout << "1. 게임 저장하기" << endl;
            cout << "2. 게임 로드하기" << endl;
            cout << "3. 게임 종료하기" << endl;
            cout << "메뉴를 선택하세요: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                saveGame(player);
                break;
            case 2:
                loadGame(player);
                break;
            case 3:
                playing = false;
                break;
            default:
                cout << "올바른 메뉴 번호를 선택하세요." << endl;
                break;
            }

            cin.ignore(); // 버퍼 비우기
        }
        else {
            // 게임 로직을 이곳에 작성하세요.
        }
    }

    cout << "게임을 종료합니다. 다음에 또 만나요!" << endl;

    return 0;
}
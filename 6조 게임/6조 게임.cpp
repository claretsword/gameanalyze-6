#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Player {
    string name;
    int HP;
    int MP;
    int attack;
    int trainingPoints;
};

// 세이브 함수
void saveGame(const Player& player) {
    ofstream saveFile("save_game.txt");
    if (saveFile.is_open()) {
        saveFile << player.name << endl;
        saveFile << player.HP << endl;
        saveFile << player.MP << endl;
        saveFile << player.attack << endl;
        saveFile << player.trainingPoints << endl;
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
        loadFile >> player.trainingPoints;
        loadFile.close();
        cout << "게임이 성공적으로 로드되었습니다." << endl;
    }
    else {
        cout << "로드할 세이브 파일이 없습니다." << endl;
    }
}

// 플레이어의 스탯과 훈련 포인트를 초기화하는 함수
void initializePlayer(Player& player, const string& playerName, int initialHP, int initialMP, int initialAttack, int initialTrainingPoints) {
    player.name = playerName;
    player.HP = initialHP;
    player.MP = initialMP;
    player.attack = initialAttack;
    player.trainingPoints = initialTrainingPoints;
}

int main() {
    Player player;
    string playerName;
    int initialHP = 100;
    int initialMP = 80;
    int initialAttack = 5;
    int initialTrainingPoints = 3; // 초기 훈련 포인트

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
            initializePlayer(player, playerName, initialHP, initialMP, initialAttack, initialTrainingPoints);
        }
    }
    else {
        // 새로운 게임 시작
        cout << "플레이어의 이름을 입력하세요: ";
        getline(cin, playerName);
        initializePlayer(player, playerName, initialHP, initialMP, initialAttack, initialTrainingPoints);
    }

    cout << "\n환영합니다, " << player.name << "님!" << endl;
    cout << "HP: " << player.HP << endl;
    cout << "MP: " << player.MP << endl;
    cout << "공격력: " << player.attack << endl;
    cout << "훈련 포인트: " << player.trainingPoints << " 포인트" << endl; // 훈련 포인트 출력

    // 게임 진행 루프
    bool playing = true;
    bool showMenu = false; // 메뉴 표시 여부
    bool inTraining = false; // 훈련소에 입장한 상태인지 여부
    while (playing) {
        // 게임 로직을 이곳에 작성하세요.

        if (showMenu) {
            // 메뉴 표시
            cout << "\n===== 메뉴 =====" << endl;
            cout << "1. 게임 저장하기" << endl;
            cout << "2. 게임 로드하기" << endl;
            cout << "3. 게임 종료하기" << endl;
            if (!inTraining) {
                cout << "4. 훈련소" << endl;
            }
            else {
                cout << "4. 훈련소 나가기" << endl;
            }
            cout << "5. 본 게임 시작" << endl;
            cout << "메뉴를 선택하세요: ";
            showMenu = false; // 메뉴를 표시한 후 다시 숨김
        }
        else {
            cout << "\nM. 메뉴 표시" << endl;
        }

        char choice;
        cin >> choice;

        switch (choice) {
        case 'M':
        case 'm':
            showMenu = !showMenu; // M 버튼을 누를 때마다 메뉴 표시 여부 변경
            break;
        case '1':
            saveGame(player);
            break;
        case '2':
            loadGame(player);
            break;
        case '3':
            playing = false;
            break;
        case '4':
            if (!inTraining) {
                cout << "훈련소에 입장합니다." << endl;
                inTraining = true;
            }
            else {
                cout << "훈련소에서 나갑니다." << endl;
                inTraining = false;
            }
            break;
        case '5':
            cout << "본 게임을 시작합니다." << endl;
            // 본 게임 시작 코드 작성
            break;
        default:
            cout << "올바른 메뉴 번호를 선택하세요." << endl;
            break;
        }

        if (inTraining) {
            // 훈련소에서 스탯을 증가시키는 로직
            cout << "1. 체력 증가 (+5)" << endl;
            cout << "2. 공격력 증가 (+1)" << endl;
            cout << "훈련할 스탯을 선택하세요: ";
            int trainingChoice;
            cin >> trainingChoice;
            if (trainingChoice == 1) {
                if (player.trainingPoints >= 1) {
                    player.HP += 5;
                    player.trainingPoints -= 1;
                    cout << "체력이 5 증가했습니다. 현재 체력: " << player.HP << endl;
                }
                else {
                    cout << "훈련 포인트가 부족합니다." << endl;
                }
            }
            else if (trainingChoice == 2) {
                if (player.trainingPoints >= 1) {
                    player.attack += 1;
                    player.trainingPoints -= 1;
                    cout << "공격력이 1 증가했습니다. 현재 공격력: " << player.attack << endl;
                }
                else {
                    cout << "훈련 포인트가 부족합니다." << endl;
                }
            }
            else {
                cout << "올바른 번호를 선택하세요." << endl;
            }
        }

        cin.ignore(); // 버퍼 비우기
    }

    cout << "게임을 종료합니다. 다음에 또 만나요!" << endl;

    return 0;
}

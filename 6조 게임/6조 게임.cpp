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

// 변경된 스텟을 표시하는 함수
void showStats(const Player& player) {
    cout << "\n===== 스테이터스 =====" << endl;
    cout << "플레이어: " << player.name << endl;
    cout << "HP: " << player.HP << endl;
    cout << "MP: " << player.MP << endl;
    cout << "공격력: " << player.attack << endl;
    cout << "훈련 포인트: " << player.trainingPoints << " 포인트" << endl; // 훈련 포인트 출력
}

// 스텟 변경 함수
void changeStats(Player& player, int hpChange, int attackChange) {
    player.HP += hpChange;
    player.attack += attackChange;
    // 변경된 스텟을 표시
    showStats(player);
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

    // 게임 진행 루프
    bool playing = true;
    bool inTraining = false; // 훈련소에 입장한 상태인지 여부
    while (playing) {
        if (inTraining) {
            showStats(player);
            cout << "\n===== 훈련소 메뉴 =====" << endl;
            cout << "1. 체력 증가 (+5)" << endl;
            cout << "2. 공격력 증가 (+1)" << endl;
            cout << "3. 훈련소 나가기" << endl;
            cout << "메뉴를 선택하세요: ";
            int choice;
            cin >> choice;
            switch (choice) {
            case 1:
                if (player.trainingPoints >= 1) {
                    changeStats(player, 5, 0); // 체력 증가
                    player.trainingPoints -= 1; // 훈련 포인트 감소
                }
                else {
                    cout << "훈련 포인트가 부족합니다." << endl;
                }
                break;
            case 2:
                if (player.trainingPoints >= 1) {
                    changeStats(player, 0, 1); // 공격력 증가
                    player.trainingPoints -= 1; // 훈련 포인트 감소
                }
                else {
                    cout << "훈련 포인트가 부족합니다." << endl;
                }
                break;
            case 3:
                inTraining = false; // 훈련소 나가기
                break;
            default:
                cout << "올바른 메뉴 번호를 선택하세요." << endl;
                break;
            }
        }
        else {
            showStats(player);
            cout << "\n===== 기본 메뉴 =====" << endl;
            cout << "1. 게임 저장하기" << endl;
            cout << "2. 게임 로드하기" << endl;
            cout << "3. 게임 종료하기" << endl;
            cout << "4. 훈련소" << endl;
            cout << "메뉴를 선택하세요: ";
            int choice;
            cin >> choice;
            switch (choice) {
            case 1:
                saveGame(player); // 게임 저장
                break;
            case 2:
                loadGame(player); // 게임 로드
                break;
            case 3:
                playing = false; // 게임 종료
                break;
            case 4:
                inTraining = true; // 훈련소 입장
                break;
            default:
                cout << "올바른 메뉴 번호를 선택하세요." << endl;
                break;
            }
        }
    }

    cout << "게임을 종료합니다. 다음에 또 만나요!" << endl;

    return 0;
}

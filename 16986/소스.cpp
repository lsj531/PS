#include <iostream>
#include <cstdlib>
using namespace std;

// N:손동작 가지의 수
// K:이기기 위한 최소 승의 수
int N, K;
int a[11][11]; // 가위바위보 상성 정보
int p[2][25]; // 손동작의 순서 p[0]:경희 p[1]:민호

bool issued[11]; // 지우가 각 손동작을 사용했는가

// ch(choice):지우가 선택한 손동작
// op(opponent):지우가 붙을 상대가 누구인지(0 or 1)
// ww : 지우/경희/민호의 승리 횟수 2:지우 1:민호 0:경희
// idxx : 경희/민호가 몇 번 경기를 진행했는가
void solve(int ch, int op, int* ww, int *idxx) {
	int idx[2] = { idxx[0], idxx[1] };
	int w[3] = { ww[0],ww[1], ww[2] };
	int op_ch = p[op][idx[op]++]; // 상대가 선택한 손동작
	int new_op = -1; // 다음 상대 초기화
	if (a[ch][op_ch] == 2) { // 지우가 승리한 경우
		w[2]++;	// 승리 횟수 추가
		if (w[2] == K) { // 승리 횟수가 K이면 1 출력 후 종료
			cout << 1;
			exit(0);
		}
		new_op = 1 - op;
	}
	else {	// 상대가 승리한 경우
		w[op]++; // 승리 횟수 추가
		if (w[op] == K) return; // 승수 필터링

		int ch0 = p[0][idx[0]++];
		int ch1 = p[1][idx[1]++];

		if (a[ch0][ch1] == 2) {
			w[0]++;
			if (w[0] >= K) return;
			new_op = 0;
		}
		else {
			w[1]++;
			if (w[1] >= K) return;
			new_op = 1;
		}
	}


	for (int i = 1; i <= N; i++) {
		if (issued[i]) continue;
		issued[i] = true;
		solve(i, new_op, w, idx);
		issued[i] = false;
	}
}

int main(void) {
	cin >> N >> K;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> a[i][j];

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 20; j++)
			cin >> p[i][j];

	for (int i = 1; i <= N; i++) {
		issued[i] = true;
		int w[3] = { 0,0,0 }; // 이긴 횟수 초기화
		int idx[2] = { 0,0 }; //
		solve(i, 0, w, idx);
		issued[i] = false;
	}

	cout << 0;

	return 0;
}

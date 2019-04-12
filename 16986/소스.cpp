#include <iostream>
#include <cstdlib>
using namespace std;

// N:�յ��� ������ ��
// K:�̱�� ���� �ּ� ���� ��
int N, K;
int a[11][11]; // ���������� �� ����
int p[2][25]; // �յ����� ���� p[0]:���� p[1]:��ȣ

bool issued[11]; // ���찡 �� �յ����� ����ߴ°�

// ch(choice):���찡 ������ �յ���
// op(opponent):���찡 ���� ��밡 ��������(0 or 1)
// ww : ����/����/��ȣ�� �¸� Ƚ�� 2:���� 1:��ȣ 0:����
// idxx : ����/��ȣ�� �� �� ��⸦ �����ߴ°�
void solve(int ch, int op, int* ww, int *idxx) {
	int idx[2] = { idxx[0], idxx[1] };
	int w[3] = { ww[0],ww[1], ww[2] };
	int op_ch = p[op][idx[op]++]; // ��밡 ������ �յ���
	int new_op = -1; // ���� ��� �ʱ�ȭ
	if (a[ch][op_ch] == 2) { // ���찡 �¸��� ���
		w[2]++;	// �¸� Ƚ�� �߰�
		if (w[2] == K) { // �¸� Ƚ���� K�̸� 1 ��� �� ����
			cout << 1;
			exit(0);
		}
		new_op = 1 - op;
	}
	else {	// ��밡 �¸��� ���
		w[op]++; // �¸� Ƚ�� �߰�
		if (w[op] == K) return; // �¼� ���͸�

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
		int w[3] = { 0,0,0 }; // �̱� Ƚ�� �ʱ�ȭ
		int idx[2] = { 0,0 }; //
		solve(i, 0, w, idx);
		issued[i] = false;
	}

	cout << 0;

	return 0;
}

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class coor {
public:
	int x, y, z;
	coor(int _x, int _y, int _z) :x(_x), y(_y), z(_z) {};
};

int dx[6] = { 1,0,0,0,0,-1 };
int dy[6] = { 0,1,-1,0,0,0 };
int dz[6] = { 0,0,0,1,-1,0 };
int mat[4][5][5][5];
int maz[5][5][5];
int dist[5][5][5];

bool OOB(int a, int b, int c) {
	return a < 0 || a >= 5 || b < 0 || b >= 5 || c < 0 || c >= 5;
}

int solve() {
	// 시작점과 끝점이 이동 불가능한 경우
	if (maz[0][0][0] == 0 || maz[4][4][4] == 0)
		return 9999;
	// 거리 배열 초기화
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				dist[i][j][k] = -1;
	queue<coor> q;
	q.push(coor(0, 0, 0));
	dist[0][0][0] = 0;

	while (!q.empty()) {
		coor cur = q.front();
		q.pop();
		// 방향 이동
		for (int dir = 0; dir < 6; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			int nz = cur.z + dz[dir];
			if (OOB(nx,ny,nz)) continue;
			if (maz[nx][ny][nz] == 0 || dist[nx][ny][nz] != -1) continue;
			if (nx == 4 && ny == 4 && nz == 4)
				return dist[cur.x][cur.y][cur.z] + 1;
			dist[nx][ny][nz] = dist[cur.x][cur.y][cur.z] + 1;
			q.push(coor(nx, ny, nz));
		}
	}
	return 9999;
}

int main(void) {
	// 초기 데이터 배열 셋팅
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				cin >> mat[0][i][j][k];

		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				mat[1][i][j][k] = mat[0][i][4 - k][j];

		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				mat[2][i][j][k] = mat[1][i][4 - k][j];

		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				mat[3][i][j][k] = mat[2][i][4 - k][j];
	}
	int ans = 9999;

	// 판 쌓기
	int order[5] = { 0,1,2,3,4 };
	do {
		for (int temp = 0; temp < 1024; temp++) {
			int brute = temp;
			// 케이스별 큐브 셋팅
			for (int i = 0; i < 5; i++) {
				int dir = brute % 4;
				brute /= 4;

				for (int j = 0; j < 5; j++)
					for (int k = 0; k < 5; k++)
						maz[i][j][k] = mat[dir][order[i]][j][k];
			}
			ans = min(ans, solve());
		}
	} while (next_permutation(order, order + 5));

	if (ans == 9999)
		ans = -1;
	cout << ans;

	return 0;
}
/*
Bài tập Robot tìm đường: http://ntucoder.net/Problem/Details/3361
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define N 20
#define M 20

struct Robot
{
	int dong, cot; // vị trí tọa độ dòng cột mà Robot đang đứng
	char huongmat; // A: Trái, D: Phải, W: Lên, S: Xuống
};
typedef struct Robot ROBOT;

struct Node
{
	ROBOT Data;
	struct Node *Left, *Right, *Cha;
};
typedef struct Node NODE;

void INit(NODE *&Root)
{
	Root = NULL;
}

NODE* GetNode(ROBOT x)
{
	NODE *p = new NODE;

	if(p == NULL)
		return NULL;

	p->Data = x;
	p->Left = p->Right = p->Cha = NULL;
	return p;
}

// hợp lệ là khi không bị rơi vào trường hợp nào trong 3 trường hợp sau: 
// 1/ không đi ra ngoài map
// 2/ không có vật cản tại vị trí đó
// 3/ vị trí đó chưa từng được đi (bao gồm cả hướng mặt)
bool KiemTraRobotDiHopLe(ROBOT x, vector<vector<int>> map, bool truyvet[N][M][4]) // n: dòng - m: cột
{
	int n = map.size();
	int m = map[0].size();

	// 1/ không đi ra ngoài map
	if(x.dong < 0 || x.dong > n - 1 || x.cot < 0 || x.cot > m - 1)
		return false;

	// 2/ không có vật cản tại vị trí đó
	if(map[x.dong][x.cot] == 1)
		return false;

	// 3/ vị trí đó chưa từng được đi (bao gồm cả hướng mặt)
	int index_huongmat;
	if(x.huongmat == 'A')
		index_huongmat = 0;
	else if(x.huongmat == 'D')
		index_huongmat = 1;
	else if(x.huongmat == 'W')
		index_huongmat = 2;
	else if(x.huongmat == 'S')
		index_huongmat = 3;

	if(truyvet[x.dong][x.cot][index_huongmat] == true)
		return false;

	truyvet[x.dong][x.cot][index_huongmat] = true; // nhớ đánh dấu là đã đi

	return true; // nước đi hợp lệ
}

int main()
{
	ifstream FileIn;
	FileIn.open("input3.txt", ios_base::in);

	int n, m; // n: số dòng - m: số cột
	int dong_dich, cot_dich;

	FileIn >> n >> m;

	vector<vector<int>> map;
	map.resize(n);

	for(int i = 0; i < n; ++i)
		map[i].resize(m);

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			FileIn >> map[i][j]; 
		}
	}

	FileIn >> dong_dich >> cot_dich;

	// Tại vì chương trình của chúng ta tính theo gốc tọa độ 0,0 nên phải trừ đi 1 cho dòng đích, cột đích
	dong_dich--;
	cot_dich--;

	FileIn.close();

	// Xử lý ở dưới này

	// 0: A, 1: D, 2: W, 3: S
	bool truyvet[N][M][4] = {false};

	NODE *Root;
	INit(Root);

	ROBOT x;
	x.dong = 0;
	x.cot = 0;
	x.huongmat = 'S';

	truyvet[0][0][3] = true;

	Root = GetNode(x);

	queue<NODE *> q;
	q.push(Root);

	NODE *con_timthay = NULL;

	// vòng lặp sẽ lặp khi hàng đợi còn phần tử
	while(!q.empty())
	{
		NODE *p = q.front(); // Lấy phần tử đầu hàng đợi ra để xét
		q.pop(); // Bỏ phần tử đó đi

		// Trường hợp rẽ trái, đi thẳng
		ROBOT contrai, conphai;

		if(p->Data.huongmat == 'A')
		{
			contrai.huongmat = 'S';
			conphai.huongmat = 'A';

			contrai.dong = p->Data.dong + 1;
			contrai.cot = p->Data.cot;

			conphai.dong = p->Data.dong;
			conphai.cot = p->Data.cot - 1;
		}
		else if(p->Data.huongmat == 'D')
		{
			contrai.huongmat = 'W';
			conphai.huongmat = 'D';

			contrai.dong = p->Data.dong - 1;
			contrai.cot = p->Data.cot;

			conphai.dong = p->Data.dong;
			conphai.cot = p->Data.cot + 1;
		}
		else if(p->Data.huongmat == 'W')
		{
			contrai.huongmat = 'A';
			conphai.huongmat = 'W';

			contrai.dong = p->Data.dong;
			contrai.cot = p->Data.cot - 1;

			conphai.cot = p->Data.cot;
			conphai.dong = p->Data.dong - 1;
		}
		else if(p->Data.huongmat == 'S')
		{
			contrai.huongmat = 'D';
			conphai.huongmat = 'S';

			contrai.dong = p->Data.dong;
			contrai.cot = p->Data.cot + 1;

			conphai.cot = p->Data.cot;
			conphai.dong = p->Data.dong + 1;
		}

		if(KiemTraRobotDiHopLe(contrai, map, truyvet) == true)
		{
			NODE *con = GetNode(contrai);
			p->Left = con;
			con->Cha = p;

			// Xét điều kiện dừng
			if(con->Data.dong == dong_dich && con->Data.cot == cot_dich)
			{
				con_timthay = con;
				break;
			}
			q.push(con);
		}

		if(KiemTraRobotDiHopLe(conphai, map, truyvet) == true)
		{
			NODE *con = GetNode(conphai);
			p->Right = con;
			con->Cha = p;

			// Xét điều kiện dừng
			if(con->Data.dong == dong_dich && con->Data.cot == cot_dich)
			{
				con_timthay = con;
				break;
			}
			q.push(con);
		}
	}

	vector<int> ketqua;
	while(con_timthay != NULL)
	{
		ketqua.push_back(con_timthay->Data.cot + 1);
		ketqua.push_back(con_timthay->Data.dong + 1);
		con_timthay = con_timthay->Cha;
	}

	if(ketqua.size() == 0)
		cout << "0";
	else
	{
		int size = ketqua.size();
		cout << size / 2;

		for(int i = size - 1; i >= 1; i -= 2)
		{
			cout << endl << ketqua[i] << " " << ketqua[i - 1];
		}
	}

	system("pause");
	return 0;
}
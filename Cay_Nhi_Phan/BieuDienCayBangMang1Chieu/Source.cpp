#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

// Trả về vị trí con trái của Node có index là idx
int Left(int idx)
{
	int kq = 2 * idx + 1;

	if(kq < 0 || kq > 14)
		return -1; // không hợp lệ

	return kq;
}

// Trả về vị trí con phải của Node có index là idx
int Right(int idx)
{
	int kq = 2 * idx + 2;

	if(kq < 0 || kq > 14)
		return -1; // không hợp lệ

	return kq;
}

int TimCha(int idx)
{
	int kq;
	if(idx % 2 == 0)
		kq = idx/2 - 1;
	else
		kq = idx/2;

	if(kq < 0 || kq > 14)
		return -1; // không hợp lệ

	return kq;
}

void TaoCay(char *&a)
{
	int k;
	printf("\nNhap vao do cao cua cay k = ");
	scanf("%d", &k);

	int SoNode = pow(2.0, k);
	a = (char *)malloc(SoNode * sizeof(char));

	for(int i = 0; i < SoNode - 1; ++i)
		a[i] = '?'; // Khởi tạo ban đầu tất cả là ?. Sau đó nếu Node nào có tồn tại thì cập nhật lại index ở vị trí tương ứng trong mảng 1 chiều

	a[SoNode - 1] = '\0'; // Kết thúc chuỗi

	queue<int> q; // Chứa index của các Node con
	char x;
	fflush(stdin);
	printf("\nNhap vao node goc: ");
	scanf("%c", &x);
	q.push(0);
	a[0] = x;

	while(!q.empty())
	{
		int idx = q.front();
		q.pop();

		int SoCon;
		do{
			printf("\nNhap vao so luong con cua Node %c (0 hay 1 hay 2): ", a[idx]);
			scanf("%d", &SoCon);

			if(SoCon < 0 || SoCon > 2)
				printf("\nSo luong con chi co the la 0 hay 1 hay 2. Xin kiem tra va nhap lai!");
		}while(SoCon < 0 || SoCon > 2);

		if(SoCon == 1)
		{
			char LoaiCon;

			do{
				fflush(stdin); // Xóa bộ nhớ đệm

				printf("\nBan muon con cua Node %c la con trai hay con phai? Neu la con trai nhap L - Neu la con phai nhap R: ", a[idx]);
				scanf("%c", &LoaiCon);

				if(LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r')
					printf("\nNeu la con trai thi nhap L - Neu la con phai thi nhap R. Khong duoc nhap khac ky tu quy dinh");
			}while(LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r');

			char x;
			if(LoaiCon == 'L' || LoaiCon == 'l') // là con trái
			{
				fflush(stdin);
				printf("\nNhap vao node con trai cua Node %c: ", a[idx]);
				scanf("%c", &x);
				a[2 * idx + 1] = x;
				q.push(2 * idx + 1);
			}
			else // Là con phải
			{
				fflush(stdin);
				printf("\nNhap vao node con phai cua Node %c: ", a[idx]);
				scanf("%c", &x);
				a[2 * idx + 2] = x;
				q.push(2 * idx + 2);
			}
		}
		else if(SoCon == 2)
		{
			char l, r;

			fflush(stdin);
			printf("\nNhap vao node con trai cua Node %c: ", a[idx]);
			scanf("%c", &l);
			a[2 * idx + 1] = l;
			q.push(2 * idx + 1);

			fflush(stdin);
			printf("\nNhap vao node con phai cua Node %c: ", a[idx]);
			scanf("%c", &r);
			a[2 * idx + 2] = r;
			q.push(2 * idx + 2);
		}
	}
}

// 1: left -> right, khác 1: right->left
void DuyetTheoChieuRong(char a[], int thutu = 1) 
{
	queue<int> q; // chứa index của các Node theo thứ tự duyệt

	// Phải có tồn tại Node gốc thì mới đưa Node gốc đó vào hàng đợi
	if(strlen(a) >= 1)
		q.push(0); // 0 chính là index của Node gốc

	while(!q.empty()) // lặ[ liên tục khi hàng đợi còn phần tử
	{
		int i = q.front(); // Lấy ra index của Node đầu hàng đợi
		
		if(a[i] != '?') // không xét những Node giả
			printf("%c ", a[i]); 
		
		q.pop(); // bỏ Node ra khỏi hàng đợi

		if(thutu == 1)
		{
			if(2 * i + 1 >= 0 && 2 * i + 1 < strlen(a)) // có tồn tại Node con trái của p
				q.push(2 * i + 1); // Đưa con trái vào hàng đợi

			if(2 * i + 2 >= 0 && 2 * i + 2 < strlen(a)) // có tồn tại Node con phải của p
				q.push(2 * i + 2); // Đưa con phải vào hàng đợi
		}
		else
		{
			if(2 * i + 1 >= 0 && 2 * i + 1 < strlen(a)) // có tồn tại Node con phải của p
				q.push(2 * i + 2); // Đưa con phải vào hàng đợi

			if(2 * i + 2 >= 0 && 2 * i + 2 < strlen(a)) // có tồn tại Node con trái của p
				q.push(2 * i + 1); // Đưa con trái vào hàng đợi
		}
	}
}

// Phép duyệt trước
// 1: left -> right, khác 1: right->left
void PreOrder(char *a, int idx, int thutu = 1)
{
	if(idx >= 0 && idx < strlen(a)) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if(a[idx] != '?')
			printf("%c ", a[idx]); // duyệt in ra N
		
		if(thutu == 1)
		{
			PreOrder(a, 2 * idx + 1, thutu); // LEFT
			PreOrder(a, 2 * idx + 2, thutu); // RIGHT
		}
		else
		{
			PreOrder(a, 2 * idx + 2, thutu); // RIGHT
			PreOrder(a, 2 * idx + 1, thutu); // LEFT 
		}
	}
}

// Phép duyệt giữa
// 1: left -> right, khác 1: right->left
void InOrder(char *a, int idx, int thutu = 1)
{
	if(idx >= 0 && idx < strlen(a)) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if(thutu == 1)
		{
			InOrder(a, 2 * idx + 1, thutu); // LEFT
			
			if(a[idx] != '?')
				printf("%c ", a[idx]); // duyệt in ra N
			
			InOrder(a, 2 * idx + 2, thutu); // RIGHT
		}
		else
		{
			InOrder(a, 2 * idx + 2, thutu); // RIGHT 

			if(a[idx] != '?')
				printf("%c ", a[idx]); // duyệt in ra N

			InOrder(a, 2 * idx + 1, thutu); // LEFT
		}
	}
}

// Phép duyệt sau
// 1: left -> right, khác 1: right->left
void PostOrder(char *a, int idx, int thutu = 1)
{
	if(idx >= 0 && idx < strlen(a)) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if(thutu == 1)
		{
			PostOrder(a, 2 * idx + 1, thutu); // LEFT
			PostOrder(a, 2 * idx + 2, thutu); // RIGHT
			
			if(a[idx] != '?')
				printf("%c ", a[idx]); // duyệt in ra N
		}
		else
		{
			PostOrder(a, 2 * idx + 2, thutu); // RIGHT
			PostOrder(a, 2 * idx + 1, thutu); // LEFT

			if(a[idx] != '?')
				printf("%c ", a[idx]); // duyệt in ra N
		}
	}
}

void DemTongCacNodeTrenCay(char *a, int idx, int &dem)
{
	if(idx >= 0 && idx < strlen(a))
	{
		if(a[idx] != '?')
			dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		
		DemTongCacNodeTrenCay(a, 2 * idx + 1, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		DemTongCacNodeTrenCay(a, 2 * idx + 2, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

int main()
{
	/*char *a;
	TaoCay(a);

	printf("%s", a);*/

	//char a[15];
	//strcpy(a, "ABCDEFGHI?JK??L");

	char *a = (char *)malloc(16 * sizeof(char));
	strcpy(a, "ABCDEFGHI?JK??L");
	
	printf("\nDuyet theo chieu rong: ");
	DuyetTheoChieuRong(a, 2);

	printf("\nDuyet truoc: ");
	PreOrder(a, 0, 2);

	printf("\nDuyet giua: ");
	InOrder(a, 0, 2);

	printf("\nDuyet sau: ");
	PostOrder(a, 0, 2);

	int SoLuongCacNode = 0;
	DemTongCacNodeTrenCay(a, 0, SoLuongCacNode);
	printf("\nTong so luong cac Node tren cay la: %d", SoLuongCacNode);

	free(a); // giải phóng cây

	/*a[0] = 'A';
	a[1] = 'B';
	a[2] = 'C';
	a[3] = 'D';
	a[4] = 'E';
	a[5] = 'F';
	a[6] = 'G';
	a[7] = 'H';
	a[8] = 'I';
	a[9] = '?';
	a[10] = 'J';
	a[11] = 'K';
	a[12] = '?';
	a[13] = '?';
	a[14] = 'L';*/

	/*printf("\nRoot = %c", a[0]);
	printf("\nRoot->Left = %c", a[Left(0)]);
	printf("\nRoot->Right = %c", a[Right(0)]);

	printf("\nRoot->Left->Left = %c", a[Left(Left(0))]);
	printf("\nRoot->Left->Right = %c", a[Right(Left(0))]);

	printf("\nRoot->Left->Right->Right = %c", a[Right(Right(Left(0)))]);

	if(a[Left(Right(Left(0)))] != '?')
		printf("\nRoot->Left->Right->Left = %c", a[Left(Right(Left(0)))]);

	printf("\nRoot->Left->Left->Left = %c", a[Left(Left(Left(0)))]);

	printf("\nRoot->Left->Right->Right = ");
	if(Right(Right(Left(0))) == -1 || (Right(Right(Left(0))) != -1 && a[Right(Right(Left(0)))] == '?'))
		printf("Khong co con o vi tri nay");
	else
		printf("%c", a[Right(Right(Left(0)))]);*/

	/*int idx = 0;
	if(TimCha(idx) == -1)
		printf("\nNode %c khong co cha", a[idx]);
	else
		printf("\nCha cua Node %c la %c", a[idx], a[TimCha(idx)]);*/

	getch();
	return 0;
}
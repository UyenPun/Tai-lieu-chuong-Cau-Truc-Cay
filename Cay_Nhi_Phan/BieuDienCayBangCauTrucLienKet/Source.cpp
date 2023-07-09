#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <queue>
using namespace std;

/* Khai báo cấu trúc dữ liệu cây nhị phân */

struct Node
{
	char Data; // dữ liệu trong Node là ký tự
	struct Node *Left, *Right; // con trỏ trỏ đến liên kết Node trái và Node phải
};
typedef struct Node NODE;
//typedef NODE* Tree;

/* ===================================== */

/* Khởi tạo cây */

void INit(NODE *&Root) // Tree &Root
{
	Root = NULL;
}

/* ================= */

/* Tạo node */

// Hàm này sẽ khởi tạo ra 1 Node mới và đưa x vào Data của Node đó sau đó trả Node đó về
NODE* GetNode(char x) // x là dữ liệu đưa vào trong Node
{
	NODE *p = (NODE *)malloc(sizeof(NODE));
	
	// Trường hợp máy tính hết bộ nhớ để cấp phát
	if(p == NULL)
		return NULL;

	// Nếu còn chạy được xuống dưới này tức là Node không rỗng => khởi tạo thành công
	p->Data = x; // x được cập nhật vô Data của Node p
	p->Left = p->Right = NULL; // Khởi tạo liên kết con trái và con phải của Node p là NULL
	
	return p; // Trả về Node p sau khi được tạo ra và cập nhật dữ liệu
}

void NhapDuLieuMotNode(NODE *&k, char *s)
{
	fflush(stdin); // Xóa bộ nhớ đệm
	char x;
	do{
		printf("\nNhap vao du lieu Node %s: ", s);
		scanf("%c", &x);

		if(x < 'A' || x > 'Z' && x < 'a' || x > 'z') // Xử lý bắt phải có dữ liệu
			printf("\nDu lieu nhap cho Node phai la ky tu trong bang chu cai. Xin kiem tra nhap lai!");
	}while(x < 'A' || x > 'Z' && x < 'a' || x > 'z');

	k = GetNode(x);
}

void TaoCay(NODE *&Root)
{
	NhapDuLieuMotNode(Root, "goc");
	queue<NODE *> q;
	q.push(Root);

	while(!q.empty()) // Sẽ lặp liên tục khi nào hàng đợi còn khác rỗng
	{
		NODE *p = q.front(); // Lấy Node đầu tiên đang chờ được xử lý
		q.pop(); // Bỏ nó ra khỏi hàng đợi

		int SoCon;
		do{
			printf("\nNhap vao so luong con cua Node %c (0 hay 1 hay 2): ", p->Data);
			scanf("%d", &SoCon);

			if(SoCon < 0 || SoCon > 2)
				printf("\nSo luong con chi co the la 0 hay 1 hay 2. Xin kiem tra va nhap lai!");
		}while(SoCon < 0 || SoCon > 2);

		if(SoCon == 1)
		{
			char LoaiCon;

			do{
				fflush(stdin); // Xóa bộ nhớ đệm

				printf("\nBan muon con cua Node %c la con trai hay con phai? Neu la con trai nhap L - Neu la con phai nhap R: ", p->Data);
				scanf("%c", &LoaiCon);

				if(LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r')
					printf("\nNeu la con trai thi nhap L - Neu la con phai thi nhap R. Khong duoc nhap khac ky tu quy dinh");
			}while(LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r');

			NODE *k;
			if(LoaiCon == 'L' || LoaiCon == 'l') // là con trái
			{
				NhapDuLieuMotNode(k, "con trai");
				p->Left = k;
			}
			else // Là con phải
			{
				NhapDuLieuMotNode(k, "con phai");
				p->Right = k;
			}
			q.push(k);
		}
		else if(SoCon == 2)
		{
			NODE *l, *r;

			NhapDuLieuMotNode(l, "con trai");
			p->Left = l;
			q.push(l);

			NhapDuLieuMotNode(r, "con phai");
			p->Right = r;
			q.push(r);
		}
	}
}

/* =========== */

// 1: left -> right, khác 1: right->left
void DuyetTheoChieuRong(NODE *Root, int thutu = 1) 
{
	queue<NODE *> q;

	// Phải có tồn tại Node gốc thì mới đưa Node gốc đó vào hàng đợi
	if(Root != NULL)
		q.push(Root);

	while(!q.empty()) // lặ[ liên tục khi hàng đợi còn phần tử
	{
		NODE *p = q.front(); // Lấy ra Node đầu hàng đợi
		printf("%c ", p->Data); 
		q.pop(); // bỏ Node ra khỏi hàng đợi

		if(thutu == 1)
		{
			if(p->Left != NULL) // có tồn tại Node con trái của p
				q.push(p->Left); // Đưa con trái vào hàng đợi

			if(p->Right != NULL) // có tồn tại Node con phải của p
				q.push(p->Right); // Đưa con phải vào hàng đợi
		}
		else
		{
			if(p->Right != NULL) // có tồn tại Node con phải của p
				q.push(p->Right); // Đưa con phải vào hàng đợi

			if(p->Left != NULL) // có tồn tại Node con trái của p
				q.push(p->Left); // Đưa con trái vào hàng đợi
		}
	}
}

// Phép duyệt trước
// 1: left -> right, khác 1: right->left
void PreOrder(NODE *Root, int thutu = 1)
{
	if(Root != NULL) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		printf("%c ", Root->Data); // duyệt in ra N
		
		if(thutu == 1)
		{
			PreOrder(Root->Left, thutu);
			PreOrder(Root->Right, thutu);
		}
		else
		{
			PreOrder(Root->Right, thutu);
			PreOrder(Root->Left, thutu);
		}
	}
}

// Phép duyệt giữa
// 1: left -> right, khác 1: right->left
void InOrder(NODE *Root, int thutu = 1)
{
	if(Root != NULL) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if(thutu == 1)
		{
			InOrder(Root->Left, thutu);
			printf("%c ", Root->Data); // duyệt in ra N
			InOrder(Root->Right, thutu);
		}
		else
		{
			InOrder(Root->Right, thutu);
			printf("%c ", Root->Data); // duyệt in ra N
			InOrder(Root->Left, thutu);
		}
	}
}

// Phép duyệt sau
// 1: left -> right, khác 1: right->left
void PostOrder(NODE *Root, int thutu = 1)
{
	if(Root != NULL) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if(thutu == 1)
		{
			PostOrder(Root->Left, thutu);
			PostOrder(Root->Right, thutu);
			printf("%c ", Root->Data); // duyệt in ra N
		}
		else
		{
			PostOrder(Root->Right, thutu);
			PostOrder(Root->Left, thutu);
			printf("%c ", Root->Data); // duyệt in ra N
		}
	}
}

void DemTongCacNodeTrenCay(NODE *Root, int &dem)
{
	if(Root != NULL)
	{
		dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		DemTongCacNodeTrenCay(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		DemTongCacNodeTrenCay(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

void RemoveAll(NODE *&Root)
{
	if(Root != NULL)
	{
		RemoveAll(Root->Left); // Xét tiếp qua nhánh con trái của Node hiện tại
		RemoveAll(Root->Right); // Xét tiếp qua nhánh con phải của Node hiện tại
		free(Root); // Giải phóng Node đang xét đến. Lưu ý: Phải giải phóng nó sau cùng (duyệt sau) chứ nếu dùng duyệt trước hay duyệt giữa thì sau khi giải phóng lấy gì mà tiếp tục trỏ? => LỖI
		Root = NULL; // Sau khi giải phóng xong phải cập nhật cho Node đó giá trị NULL nếu không sẽ bị lỗi ngang nếu sau khi giải phóng xong người dùng có thao tác tiếp gì đó (vd: duyệt cây)
	}
}

int main()
{
	/* Nhập dữ liệu cho cây (Tạo cây) */

	// Bước 1: Tạo ra bấy nhiêu Node tương ứng với các Node có trong cây
	NODE *Root = GetNode('A'); // Đây chính là Node gốc
	NODE *B = GetNode('B');
	NODE *C = GetNode('C');
	NODE *D = GetNode('D');
	NODE *E = GetNode('E');
	NODE *F = GetNode('F');
	NODE *G = GetNode('G');
	NODE *H = GetNode('H');
	NODE *I = GetNode('I');
	NODE *J = GetNode('J');
	NODE *K = GetNode('K');
	NODE *L = GetNode('L');

	// Bước 2: Tạo ra các mối liên kết giữa các Node với nhau
	Root->Left = B;
	Root->Right = C;
	B->Left = D;
	B->Right = E;
	C->Left = F;
	C->Right = G;
	D->Left = H;
	D->Right = I;
	E->Right = J;
	F->Left = K;
	G->Right = L;


	/* ========================================= */

	printf("\nDuyet theo chieu rong: ");
	DuyetTheoChieuRong(Root);
	
	printf("\nDuyet truoc: ");
	PreOrder(Root, 2);

	printf("\nDuyet giua: ");
	InOrder(Root, 2);

	printf("\nDuyet sau: ");
	PostOrder(Root, 2);

	int SoLuongCacNode = 0;
	DemTongCacNodeTrenCay(Root, SoLuongCacNode);
	printf("\nTong so luong cac Node tren cay la: %d", SoLuongCacNode);

	printf("\n\nGiai phong cay\n");
	RemoveAll(Root); // giải phóng bộ nhớ đã cấp phát cho cây

	/*NODE *Root;
	TaoCay(Root);
	printf("\nRoot: %c", Root->Data);
	printf("\nRoot->Right: %c", Root->Right->Data);
	printf("\nRoot->Right->Left: %c", Root->Right->Left->Data);
	printf("\nRoot->Right->Left->Right: %c", Root->Right->Left->Right->Data);
	printf("\nRoot->Right->Left->Right->Left: %c", Root->Right->Left->Right->Left->Data);*/

	
	getch();
	return 0;
}
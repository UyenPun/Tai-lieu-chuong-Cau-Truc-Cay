#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <queue>
#include <time.h>
#include <vector>
#include <stack>
using namespace std;

/* Khai báo cấu trúc dữ liệu cây nhị phân */

struct Node
{
	int Data; // dữ liệu trong Node là ký tự
	struct Node *Left, *Right; // con trỏ trỏ đến liên kết Node trái và Node phải
	bool TinhTrangDuyet;
	int ThuTuDuyet;
	int level; // tầng mà node này đang đứng
	int TongCay; // tính tổng của node đại diện cho cây
	struct Node *Cha;
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
NODE* GetNode(int x) // x là dữ liệu đưa vào trong Node
{
	NODE *p = (NODE *)malloc(sizeof(NODE));

	// Trường hợp máy tính hết bộ nhớ để cấp phát
	if(p == NULL)
		return NULL;

	// Nếu còn chạy được xuống dưới này tức là Node không rỗng => khởi tạo thành công
	p->Data = x; // x được cập nhật vô Data của Node p
	p->Left = p->Right = NULL; // Khởi tạo liên kết con trái và con phải của Node p là NULL
	p->TinhTrangDuyet = false; // chưa được duyệt
	p->Cha = NULL;
	p->ThuTuDuyet = 0;
	p->level = 1;
	p->TongCay = 0;
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
		printf("%d ", p->Data); 
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
			//printf("%c ", Root->Data); // duyệt in ra N
			InOrder(Root->Right, thutu);
		}
		else
		{
			InOrder(Root->Right, thutu);
			//printf("%c ", Root->Data); // duyệt in ra N
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
			//printf("%c ", Root->Data); // duyệt in ra N
		}
		else
		{
			PostOrder(Root->Right, thutu);
			PostOrder(Root->Left, thutu);
			//printf("%c ", Root->Data); // duyệt in ra N
		}
	}
}

void DemSoLuongCacNodeTrenCay_DeQuyDuoi(NODE *Root, int &dem)
{
	if(Root != NULL)
	{
		dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		DemSoLuongCacNodeTrenCay_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		DemSoLuongCacNodeTrenCay_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
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

int DemSoLuongCacNodeTrenCay_DeQuyThuong(NODE *Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if(Root == NULL)
		return 0;

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return 1 + DemSoLuongCacNodeTrenCay_DeQuyThuong(Root->Left) + DemSoLuongCacNodeTrenCay_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

int DemSoLuongCacNodeTrenCay_KhongDeQuy(NODE *Root) 
{
	queue<NODE *> q;

	// Phải có tồn tại Node gốc thì mới đưa Node gốc đó vào hàng đợi
	if(Root != NULL)
		q.push(Root);

	int dem = 0;
	while(!q.empty()) // lặ[ liên tục khi hàng đợi còn phần tử
	{
		NODE *p = q.front(); // Lấy ra Node đầu hàng đợi
		//printf("%d ", p->Data); 
		dem++;
		q.pop(); // bỏ Node ra khỏi hàng đợi

		if(p->Left != NULL) // có tồn tại Node con trái của p
			q.push(p->Left); // Đưa con trái vào hàng đợi

		if(p->Right != NULL) // có tồn tại Node con phải của p
			q.push(p->Right); // Đưa con phải vào hàng đợi
	}
	return dem;
}

// Node lá: Là node không có con
int DemSoLuongCacNodeLa_DeQuyThuong(NODE *Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if(Root == NULL)
		return 0;

	int dem = 0;
	if(Root->Left == NULL && Root->Right == NULL) // Root là node lá => cho dem = 1
	{
		printf("%c ", Root->Data);
		dem = 1;
	}

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return dem + DemSoLuongCacNodeLa_DeQuyThuong(Root->Left) + DemSoLuongCacNodeLa_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

// Node lá: Là node không có con
void DemSoLuongCacNodeLa_DeQuyDuoi(NODE *Root, int &dem)
{
	if(Root != NULL)
	{
		if(Root->Left == NULL && Root->Right == NULL) // Root là node lá => cho dem = 1
		{
			//printf("%c ", Root->Data);
			dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		}

		DemSoLuongCacNodeLa_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		DemSoLuongCacNodeLa_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

int DemSoLuongCacNodeCoDu2Con_DeQuyThuong(NODE *Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if(Root == NULL)
		return 0;

	int dem = 0;
	if(Root->Left != NULL && Root->Right != NULL)
	{
		printf("%c ", Root->Data);
		dem = 1;
	}

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return dem + DemSoLuongCacNodeCoDu2Con_DeQuyThuong(Root->Left) + DemSoLuongCacNodeCoDu2Con_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

void DemSoLuongCacNodeCoDu2Con_DeQuyDuoi(NODE *Root, int &dem)
{
	if(Root != NULL)
	{
		if(Root->Left != NULL && Root->Right != NULL)
		{
			//printf("%c ", Root->Data);
			dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		}

		DemSoLuongCacNodeCoDu2Con_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		DemSoLuongCacNodeCoDu2Con_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

int DemSoLuongCacNodeCoDuyNhat1Con_DeQuyThuong(NODE *Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if(Root == NULL)
		return 0;

	int dem = 0;
	if((Root->Left != NULL && Root->Right == NULL) || (Root->Right != NULL && Root->Left == NULL))
	{
		printf("%c ", Root->Data);
		dem = 1;
	}

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return dem + DemSoLuongCacNodeCoDuyNhat1Con_DeQuyThuong(Root->Left) + DemSoLuongCacNodeCoDuyNhat1Con_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

void DemSoLuongCacNodeCoDuyNhat1Con_DeQuyDuoi(NODE *Root, int &dem)
{
	if(Root != NULL)
	{
		if((Root->Left != NULL && Root->Right == NULL) || (Root->Right != NULL && Root->Left == NULL))
		{
			printf("%c ", Root->Data);
			dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		}

		DemSoLuongCacNodeCoDuyNhat1Con_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		DemSoLuongCacNodeCoDuyNhat1Con_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

int TinhBacCua1Node(NODE *X)
{
	int DemCon = 0;

	if(X->Left != NULL)
		DemCon++;

	if(X->Right != NULL)
		DemCon++;

	return DemCon;
}

void TinhBacCuaCay(NODE *Root, int &MaxBac)
{
	if(Root != NULL)
	{
		printf("%c ", Root->Data);

		// xử lý
		int bac = TinhBacCua1Node(Root);
		if(bac > MaxBac)
		{
			MaxBac = bac;

			if(MaxBac == 2) // nhận thấy cây luôn có bậc tối đa là 2 nên khi tìm được 1 node có bậc là 2 rồi thì chúng ta dừng lại không cần duyệt gọi đệ quy tiếp nữa
				return;
		}

		TinhBacCuaCay(Root->Left, MaxBac);
		TinhBacCuaCay(Root->Right, MaxBac);
	}
}

int TinhChieuCaoCuaCay_DeQuyThuong(NODE *Root)
{
	if(Root == NULL)
		return 0;

	int left = TinhChieuCaoCuaCay_DeQuyThuong(Root->Left);
	int right = TinhChieuCaoCuaCay_DeQuyThuong(Root->Right);

	return left > right ? left + 1 : right + 1;
}

void TinhChieuCaoCuaCay_DeQuyDuoi(NODE *Root, int &max, int level = 1)
{
	if(Root != NULL)
	{
		// xử lý Root
		//printf("\nNode %c nam o level: %d", Root->Data, level);
		if(level > max)
			max = level;

		level++;
		TinhChieuCaoCuaCay_DeQuyDuoi(Root->Left, max, level);
		TinhChieuCaoCuaCay_DeQuyDuoi(Root->Right, max, level);
	}
}

void TimNodeX(NODE *Root, bool &Check, char x, int &dosau, int level)
{
	if(Root != NULL && Check == false) // chỉ đệ quy khi Node có tồn tại và trạng thái tìm kiếm là chưa được tìm thấy
	{
		printf("%c ", Root->Data);
		if(Root->Data == x)
		{
			Check = true;
			dosau = level;

			// Nếu dùng exit(0) là tắt luôn toàn bộ chương trình => chỉ dùng khi đằng sau bài này mình không còn phải làm bài nào nữa, còn nếu còn yêu cầu thì không dùng cách này được
			/*printf("\nDa tim thay node co data la %c", x);
			system("pause");
			exit(0);*/
			return; // kết thúc tìm kiếm khi đã thấy
		}

		level++;
		TimNodeX(Root->Left, Check, x, dosau, level);
		TimNodeX(Root->Right, Check, x, dosau, level);
	}
}

void LietKeVaDemCacNodeTrenTangK(NODE *Root, int k, int &count, int level = 1)
{
	if(Root != NULL)
	{
		//printf("\nNode %c co level la: %d", Root->Data, level);
		if(level == k)
		{
			count++;
			printf("%c ", Root->Data);
		}

		level++;
		LietKeVaDemCacNodeTrenTangK(Root->Left, k, count, level);
		LietKeVaDemCacNodeTrenTangK(Root->Right, k, count, level);
	}
}

void DemCacNodeTrenTangK(NODE *Root, int k, int &count, int level = 1)
{
	if(Root != NULL)
	{
		//printf("\nNode %c co level la: %d", Root->Data, level);
		if(level == k)
			count++;

		level++;
		DemCacNodeTrenTangK(Root->Left, k, count, level);
		DemCacNodeTrenTangK(Root->Right, k, count, level);
	}
}

void LietKeCacNodeTrenMoiTang(NODE *Root)
{
	int ChieuCaoCay = 0;
	TinhChieuCaoCuaCay_DeQuyDuoi(Root, ChieuCaoCay);

	for(int i = 1; i <= ChieuCaoCay; ++i)
	{
		printf("\nTang thu %d: ", i);
		int count = 0;
		LietKeVaDemCacNodeTrenTangK(Root, i, count);
		printf(" => co %d node", count);
	}
}

// s là operator giữa tầng của node hiện tại với tầng k
// vd: Xuất tất cả các node nằm trên tầng k => s = "=="
// vd: Xuất tất cả các node có tầng lớn hơn tầng k => s = ">"
void LietKeVaDemCacNodeCoTangThoaDieuKienVoiTangK(NODE *Root, char *s, int k, int &count, int level = 1)
{
	if(Root != NULL)
	{
		bool Check;
		if(strcmp(s, "==") == 0)
			Check = (level == k);
		else if(strcmp(s, ">") == 0)
			Check = (level > k);
		else if(strcmp(s, "<") == 0)
			Check = (level < k);
		else if(strcmp(s, ">=") == 0)
			Check = (level >= k);
		else if(strcmp(s, "<=") == 0)
			Check = (level <= k);
		else if(strcmp(s, "!=") == 0)
			Check = (level != k);

		if(Check)
		{
			count++;
			printf("%c ", Root->Data);
		}

		level++;
		LietKeVaDemCacNodeCoTangThoaDieuKienVoiTangK(Root->Left, s, k, count, level);
		LietKeVaDemCacNodeCoTangThoaDieuKienVoiTangK(Root->Right, s, k, count, level);
	}
}

// Nếu trả về true => là cây nhị phân đầy đủ
// Nếu trả về false => không phải là cây nhị phân đầy đủ
bool KiemTraCayNhiPhanCoLaCayNhiPhanDayDu_Cach1(NODE *Root)
{
	int ChieuCaoCay = 0;
	TinhChieuCaoCuaCay_DeQuyDuoi(Root, ChieuCaoCay);

	for(int i = 1; i <= ChieuCaoCay; ++i)
	{
		//printf("\nTang thu %d: ", i);
		int count = 0;
		DemCacNodeTrenTangK(Root, i, count);
		//printf(" => co %d node", count);

		if(count != pow(2.0, i - 1))
			return false;
	}
	return true;
}

void ThongKeSoLuongNodeTrenMoiTangVaoVector(NODE *Root, vector<int> &a, int level = 1)
{
	if(Root != NULL)
	{
		//printf("\nNode %c co level la: %d", Root->Data, level);
		if(level > a.size()) // Nếu level đang xét mà vector chưa có thì tạo mới ra ô tương ứng trong vector với giá trị khởi tạo ban đầu là 0
			a.push_back(0);

		a[level - 1]++; // ô tương ứng level trong vector sẽ được cập nhật đếm lên 1 đơn vị

		level++;
		ThongKeSoLuongNodeTrenMoiTangVaoVector(Root->Left, a, level);
		ThongKeSoLuongNodeTrenMoiTangVaoVector(Root->Right, a, level);
	}
}

bool KiemTraCayNhiPhanCoLaCayNhiPhanDayDu_Cach2(NODE *Root)
{
	vector<int> a;

	ThongKeSoLuongNodeTrenMoiTangVaoVector(Root, a);

	int SoLuong = a.size();
	for(int i = 0; i < SoLuong; ++i)
	{
		if(a[i] != pow(2.0, i))
			return false;
	}
	return true;
}

// thống kê số lượng node và danh sách node ở tầng h và tầng h-1
void DuyetCayVaTaoDanhSachMang2ChieuChuaCacNode(NODE *Root, vector<vector<NODE *>> &Mang2ChieuNode, int level = 1)
{
	if(Root != NULL)
	{
		if(level > Mang2ChieuNode.size())
		{
			vector<NODE *> temp;
			temp.push_back(Root);
			Mang2ChieuNode.push_back(temp);
		}
		else
		{
			Mang2ChieuNode[level - 1].push_back(Root);
		}

		level++;
		DuyetCayVaTaoDanhSachMang2ChieuChuaCacNode(Root->Left, Mang2ChieuNode, level);
		DuyetCayVaTaoDanhSachMang2ChieuChuaCacNode(Root->Right, Mang2ChieuNode, level);
	}
}

// trả về true nếu thỏa là cây nhị phân hoàn chỉnh - trả về false nếu không thỏa là cây nhị phân hoàn chỉnh
bool KiemTraCayNhiPhanCoLaCayNhiPhanHoanChinh(NODE *Root)
{
	vector<vector<NODE *>> Mang2ChieuNode;
	DuyetCayVaTaoDanhSachMang2ChieuChuaCacNode(Root, Mang2ChieuNode);
	int ChieuCaoCay = Mang2ChieuNode.size();

	for(int i = 1; i < ChieuCaoCay; ++i)
	{
		if(Mang2ChieuNode[i - 1].size() != pow(2.0, i - 1))
			return false;
	}

	// Xét riêng số lượng node của tầng cuối cùng phải không đầy đủ thì mới xét xem có là hoàn chỉnh hay không (chứ nếu đầy đủ luôn thì đó là cây đầy đủ rồi)
	if(Mang2ChieuNode[ChieuCaoCay - 1].size() == pow(2.0, ChieuCaoCay - 1))
		return false;

	// Nếu chạy đến đây rồi thì tức là tiêu chí 1 đầu tiên đã thỏa
	for(int j = 0; j < Mang2ChieuNode[ChieuCaoCay - 1].size(); ++j)
	{
		NODE *Con = Mang2ChieuNode[ChieuCaoCay - 1][j];
		NODE *Cha = Mang2ChieuNode[ChieuCaoCay - 2][j / 2];

		if(j % 2 == 0) // chẵn => con trái
		{
			if(Cha->Left != Con)
				return false;
		}
		else // lẻ => con phải
		{
			if(Cha->Right != Con)
				return false;
		}
	}
	return true;
}

// 1: là cây đầy đủ - 2: là cây hoàn chỉnh - 0: không là cây gì
int KiemTraCayNhiPhanLaCayNhiPhanDayDuHayCayNhiPhanHoanChinh(NODE *Root)
{
	vector<vector<NODE *>> Mang2ChieuNode;
	DuyetCayVaTaoDanhSachMang2ChieuChuaCacNode(Root, Mang2ChieuNode);
	int ChieuCaoCay = Mang2ChieuNode.size();

	// kiểm tra các node từ tầng 1 đến h - 1 phải đầy đủ thì mới xét tiếp
	for(int i = 1; i < ChieuCaoCay; ++i)
	{
		if(Mang2ChieuNode[i - 1].size() != pow(2.0, i - 1))
			return 0;
	}

	// Nếu xuống đây được tức là cây này các node ở tầng 1 đến h-1 đều đầy đủ => xét tiếp số lượng các node ở tầng h
	if(Mang2ChieuNode[ChieuCaoCay - 1].size() == pow(2.0, ChieuCaoCay - 1))
		return 1;

	// Nếu xuống đây được tức là không đầy đủ các node (tức là không thể là cây đầy đủ chỉ có thể là cây hoàn chỉnh hoặc là không) thì sẽ xét tiếp tiêu chí 2 xem các node có được sắp đều từ trái qua phải không để kết luận có thể là cây hoàn chỉnh
	for(int j = 0; j < Mang2ChieuNode[ChieuCaoCay - 1].size(); ++j)
	{
		NODE *Con = Mang2ChieuNode[ChieuCaoCay - 1][j];
		NODE *Cha = Mang2ChieuNode[ChieuCaoCay - 2][j / 2];

		if(j % 2 == 0) // chẵn => con trái
		{
			if(Cha->Left != Con)
				return 0;
		}
		else // lẻ => con phải
		{
			if(Cha->Right != Con)
				return 0;
		}
	}
	return 2; // là cây hoàn chỉnh
}

/* =============================== KHÔNG ĐỆ QUY ================================== */

// thutu = 1 (left -> right), thutu = 2 (right -> left)
void PreOrder_KhuDeQuyDungStack(NODE *Root, int thutu = 1)
{
	stack<NODE *> s;
	s.push(Root);

	//thutu == 1 ? printf("\nNLR: ") : printf("\nNRL: ");

	while(!s.empty())
	{
		NODE *p = s.top();
		s.pop();
		//printf("%c ", p->Data);

		if(thutu == 1) // left -> right
		{
			if(p->Right != NULL)
				s.push(p->Right);

			if(p->Left != NULL)
				s.push(p->Left);
		}
		else // right -> left
		{
			if(p->Left != NULL)
				s.push(p->Left);

			if(p->Right != NULL)
				s.push(p->Right);
		}
	}
}

// thutu = 1 (left -> right), thutu = 2 (right -> left)
void InOrder_KhuDeQuyDungStack(NODE *Root, int thutu = 1)
{
	stack<NODE *> s;
	s.push(Root);
	Root->TinhTrangDuyet = true;

	//thutu == 1 ? printf("\nLNR: ") : printf("\nRNL: ");

	while(!s.empty())
	{
		NODE *p = s.top(); // p là Node ở đỉnh stack
		bool Check = false;

		if(thutu == 1)
		{
			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // có tồn tại con phải và con phải chưa được duyệt
			{
				s.pop(); // xóa phần tử đầu stack hiện tại
				s.push(p->Right); // đưa con phải vào stack
				p->Right->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				s.push(p); // trả lại phần tử đầu stack trước đó
				Check = true; // kiểm tra có con được thêm vào
			}

			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // có tồn tại con trái và con trái chưa được duyệt
			{
				s.push(p->Left); // đưa con trái vào stack
				p->Left->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				Check = true; // kiểm tra có con được thêm vào
			}
		}
		else
		{
			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // có tồn tại con phải và con phải chưa được duyệt
			{
				s.pop(); // xóa phần tử đầu stack hiện tại
				s.push(p->Left); // đưa con phải vào stack
				p->Left->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				s.push(p); // trả lại phần tử đầu stack trước đó
				Check = true; // kiểm tra có con được thêm vào
			}

			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // có tồn tại con trái và con trái chưa được duyệt
			{
				s.push(p->Right); // đưa con trái vào stack
				p->Right->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				Check = true; // kiểm tra có con được thêm vào
			}
		}

		// Nếu sau 1 quá trình xét mà không có con nào được thêm vào => in ra node đầu stack hiện tại và bỏ đi
		if(Check == false)
		{
			//printf("%c ", p->Data);
			s.pop();
		}
	}
}

// thutu = 1 (left -> right); thutu = 2 (right -> left)
void PostOrder_KhuDeQuyDungStack(NODE *Root, int thutu = 1)
{
	stack<NODE *> s;
	s.push(Root);

	while(!s.empty())
	{
		NODE *p = s.top();
		bool Check = false; // biến cờ hiệu mục đích để biết xem từ node hiện tại đầu stack có node con nào của nó hợp lệ để được thêm vào tiếp. Nếu trải qua 2 cái if mà Check vẫn là false tức là không có node con nào của node đang xét được thêm vào stack => lấy node đó ra khỏi stack và in ra

		if(thutu == 1)
		{
			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // xét có con phải và chưa được thêm vào stack
			{
				s.push(p->Right); // tiến hành thêm vào
				p->Right->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}

			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // xét có con trái và chưa được thêm vào stack
			{
				s.push(p->Left); // tiến hành thêm vào
				p->Left->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}
		}
		else
		{
			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // xét có con trái và chưa được thêm vào stack
			{
				s.push(p->Left); // tiến hành thêm vào
				p->Left->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}

			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // xét có con phải và chưa được thêm vào stack
			{
				s.push(p->Right); // tiến hành thêm vào
				p->Right->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}
		}

		if(Check == false)
		{
			//printf("%c ", p->Data);
			s.pop(); // bỏ ra khỏi stack
		}
	}
}

void DuyetCayKhongDeQuyKhongStack(NODE *Root, char *s) // s = "NLR" hoặc "LNR" hoặc "LRN" hoặc "NRL" hoặc "RNL" hoặc "RLN"
{
	//int length = strlen(s);
	//if(length != 3)
	//{
	//	printf("\nChuoi phep duyet khong hop le. Xin kiem tra lai!");
	//}
	//else
	//{
	//	int dem_N = 0;
	//	int dem_L = 0;
	//	int dem_R = 0;

	//	for(int i = 0; i < length; ++i)
	//	{
	//		if(s[i] == 'N' || s[i] == 'n')
	//			dem_N++;
	//		else if(s[i] == 'L' || s[i] == 'l')
	//			dem_L++;
	//		else if(s[i] == 'R' || s[i] == 'r')
	//			dem_R++;
	//	}

	//	if(dem_L != 1 || dem_N != 1 || dem_R != 1)
	//	{
	//		printf("\nChuoi phep duyet khong hop le. Xin kiem tra lai!");
	//	}
	//	else // hoàn toàn hợp lệ
	//	{
	//printf("\n%s: ", s);


	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					printf("%c ", Root->Data);
					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}

		}
	}
	//}
	//}
}

int DemSoLuongCacNodeTrenCay_KhongDeQuyKhongStack(NODE *Root)
{
	int dem = 0;
	char s[] = "NLR"; // quy ước thao tác duyệt

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//printf("%d ", Root->Data);
					dem++;
					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}
	return dem;
}

// node lá là node không có con
int DemSoLuongCacNodeLaTrenCay_KhongDeQuyKhongStack(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	int dem = 0;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//printf("%d ", Root->Data);
					if(Root->Left == NULL && Root->Right == NULL)
						dem++;

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	return dem;
}

int DemSoLuongCacNodeTrenCayCoDu2Con_KhongDeQuyKhongStack(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	int dem = 0;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//printf("%d ", Root->Data);
					if(Root->Left != NULL && Root->Right != NULL)
						dem++;

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	return dem;
}

int DemSoLuongCacNodeTrenCayChiCoDuyNhat1Con_KhongDeQuyKhongStack(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	int dem = 0;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//printf("%d ", Root->Data);
					if((Root->Left == NULL && Root->Right != NULL) || (Root->Left != NULL && Root->Right == NULL))
					{
						//printf("%c ", Root->Data);
						dem++;
					}
					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	return dem;
}

int TinhBacCuaCay_KhongDeQuyKhongStack(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	int MaxBac = 0;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//printf("%d ", Root->Data);

					int Bac = TinhBacCua1Node(Root);
					if(Bac > MaxBac)
					{
						MaxBac = Bac;

						if(MaxBac == 2)
							return MaxBac;
					}

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	return MaxBac;
}

// Tính tầng mà node đó đang đứng
int TinhDoSauCuaNodeBatKy_KhongDeQuyKhongStack(NODE *X)
{
	int dem = 0;

	while(true)
	{
		X = X->Cha;

		if(X == NULL)
			break;

		dem++;
	}
	return dem + 1;
}

// Trả về 1 Node khác NULL: nếu tìm thấy - NULL: nếu không tìm thấy
NODE* TimKiemNodeCoDataXTrongCay_KhongDeQuyKhongStack(NODE *Root, char Data) // Data đang là kiểu X
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					char x1 = Root->Data;
					char x2 = Data;

					if(x1 >= 'A' && x1 <= 'Z')
						x1 += 32;

					if(x2 >= 'A' && x2 <= 'Z')
						x2 += 32;

					if(x1 == x2)
						return Root; // khác NULL

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	return NULL;
}

int TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	int DoSauMax = 1;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					int DoSauNode = TinhDoSauCuaNodeBatKy_KhongDeQuyKhongStack(Root);
					if(DoSauNode > DoSauMax)
						DoSauMax = DoSauNode;

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
					{
						int level_cha = Root->level;
						Root = Root->Left;
						Root->level = level_cha + 1;
					}
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
					{
						int level_cha = Root->level;
						Root = Root->Right;
						Root->level = level_cha + 1;
					}
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	return DoSauMax; // CHIỀU CAO Cây
}

vector<vector<NODE *>> CapNhatLevelChoCacNodeVaTraVeMang2ChieuChuaDanhSachCacNode_KhongDeQuyKhongStack(NODE *&Root)
{
	vector<vector<NODE *>> arr;

	char s[] = "NLR"; // quy ước thao tác duyệt

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					if(Root->level > arr.size())
					{
						vector<NODE *> temp;
						temp.push_back(Root);
						arr.push_back(temp);
					}
					else
					{
						arr[Root->level - 1].push_back(Root);
					}

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
					{
						int level_Cha = Root->level;
						Root = Root->Left;
						Root->level = level_Cha + 1;
					}
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
					{
						int level_Cha = Root->level;
						Root = Root->Right;
						Root->level = level_Cha + 1;
					}
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}


	return arr;
}

void TimDoLechLonNhatTrenCay_DeQuy(NODE *Root, int &DoLechMax, NODE *&p)
{
	if(Root != NULL)
	{
		int docaocontrai = 0;
		TinhChieuCaoCuaCay_DeQuyDuoi(Root->Left, docaocontrai);

		int docaoconphai = 0;
		TinhChieuCaoCuaCay_DeQuyDuoi(Root->Right, docaoconphai);

		int dolech = abs(docaocontrai - docaoconphai);

		if(dolech > DoLechMax)
		{
			DoLechMax = dolech;
			p = Root;
		}

		TimDoLechLonNhatTrenCay_DeQuy(Root->Left, DoLechMax, p);
		TimDoLechLonNhatTrenCay_DeQuy(Root->Right, DoLechMax, p);
	}
}

int TimDoLechLonNhatTrenCay_KhuDeQuy(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt
	NODE *lech;
	int DoLechMax = 0;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//printf("\nDang xet node %c", Root->Data);

					int docaocontrai = 0;

					if(Root->Left != NULL)
						docaocontrai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(Root->Left);

					int docaoconphai = 0;

					if(Root->Right != NULL)
						docaoconphai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(Root->Right);

					int dolech = abs(docaocontrai - docaoconphai);

					if(dolech > DoLechMax)
					{
						DoLechMax = dolech;
						lech = Root;
					}

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}

	//printf("\nLech tai node %c", lech->Data);
	return DoLechMax;
}

void RemoveAll_KhuDeQuy(NODE *&Root)
{
	char s[] = "NLR";

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					free(Root);
					Root = NULL;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
				{
					NODE *q = Root;
					Root = Root->Cha;
					free(q);
					q = NULL;
				}
			}
		}
	}

}

void TinhTongCay(NODE *Root, int &Tong)
{
	if(Root != NULL)
	{
		Tong += Root->Data;

		TinhTongCay(Root->Left, Tong);
		TinhTongCay(Root->Right, Tong);
	}
}

void TimCayConCoTongLonNhat(NODE *Root, int &TongMax, NODE *&p_Max)
{
	if(Root != NULL)
	{
		//printf("\n\nXet node %d ", Root->Data);
		
		int Tong = 0;
		TinhTongCay(Root, Tong);
		//printf("=> Tong = %d", Tong);
		
		if(Tong > TongMax)
		{
			TongMax = Tong;
			p_Max = Root;
		}

		TimCayConCoTongLonNhat(Root->Left, TongMax, p_Max);
		TimCayConCoTongLonNhat(Root->Right, TongMax, p_Max);
	}
}

int TinhTongCay_KhuDeQuy(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt
	int Tong = 0;

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					Tong += Root->Data;

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}
	return Tong;
}

NODE* TimCayConCoTongLonNhat_KhuDeQuy(NODE *Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt
	int TongMax = INT_MIN; // Chỗ này nếu để TongMax = Root->Data sẽ bị sai vì chúng ta đang xét tất cả cây con của 1 Node nên trừ khi TongMax = tổng các cây con của 1 Node bất kỳ trong cây thì được, còn không để đơn giản chúng ta cho nó bằng giá trị nhỏ nhất của kiểu int (INT_MIN) để đảm bảo mọi giá trị đều lớn hơn nó mà cập nhật lại TongMax
	NODE *p_Max = Root; // Chỗ này nếu gán con trỏ p = Root thì không sao vì chắc chắn Node có cây con có tổng lớn nhất cũng luôn chỉ nằm trong phạm vi các node của cây đang có => cho nó khởi tạo bằng Root hay bằng 1 node bất kỳ có trong cây đều được

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					int Tong = TinhTongCay_KhuDeQuy(Root);
					if(Tong > TongMax)
					{
						TongMax = Tong;
						p_Max = Root;
					}

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}
	//printf("\nTong lon nhat (Khu de quy) la: %d", TongMax);
	return p_Max;
}

// Duyệt sau: Left - Right - Node
void TimCayConCoTongLonNhat_Cach2(NODE *Root, int &TongMax, NODE *&p_Max)
{
	if(Root != NULL)
	{
		TimCayConCoTongLonNhat_Cach2(Root->Left, TongMax, p_Max);
		TimCayConCoTongLonNhat_Cach2(Root->Right, TongMax, p_Max);

		int Tong = Root->Data;
		
		if(Root->Left != NULL)
			Tong += Root->Left->TongCay;
		
		if(Root->Right != NULL)
			Tong += Root->Right->TongCay;
		
		Root->TongCay = Tong; // cập nhật lại tổng cây của Node hiện tại

		if(Root->TongCay > TongMax)
		{
			TongMax = Root->TongCay;
			p_Max = Root;
		}
	}
}

NODE* TimCayConCoTongLonNhat_KhuDeQuy_Cach2(NODE *Root)
{
	char s[] = "LRN"; // quy ước thao tác duyệt
	int TongMax = INT_MIN; // Chỗ này nếu để TongMax = Root->Data sẽ bị sai vì chúng ta đang xét tất cả cây con của 1 Node nên trừ khi TongMax = tổng các cây con của 1 Node bất kỳ trong cây thì được, còn không để đơn giản chúng ta cho nó bằng giá trị nhỏ nhất của kiểu int (INT_MIN) để đảm bảo mọi giá trị đều lớn hơn nó mà cập nhật lại TongMax
	NODE *p_Max = Root; // Chỗ này nếu gán con trỏ p = Root thì không sao vì chắc chắn Node có cây con có tổng lớn nhất cũng luôn chỉ nằm trong phạm vi các node của cây đang có => cho nó khởi tạo bằng Root hay bằng 1 node bất kỳ có trong cây đều được

	if(Root != NULL)
	{
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while(true)
		{
			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					int Tong = Root->Data;

					if(Root->Left != NULL)
						Tong += Root->Left->TongCay;

					if(Root->Right != NULL)
						Tong += Root->Right->TongCay;

					Root->TongCay = Tong; // cập nhật lại tổng cây của Node hiện tại

					if(Root->TongCay > TongMax)
					{
						TongMax = Root->TongCay;
						p_Max = Root;
					}

					Root->ThuTuDuyet++;
				}
				else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if(Root->Left != NULL)
						Root = Root->Left;
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if(Root->Cha == NULL)
				{
					Root->Cha = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->Cha;
			}
		}
	}
	//printf("\nTong lon nhat (Khu de quy - Cach 2) la: %d", TongMax);
	return p_Max;
}

int main()
{
	/* Nhập dữ liệu cho cây (Tạo cây) */

	// Bước 1: Tạo ra bấy nhiêu Node tương ứng với các Node có trong cây
	//NODE *Root = GetNode('A'); // Đây chính là Node gốc
	//NODE *B = GetNode('B');
	//NODE *C = GetNode('C');
	//NODE *D = GetNode('D');
	//NODE *E = GetNode('E');
	//NODE *F = GetNode('F');
	//NODE *G = GetNode('G');
	//NODE *H = GetNode('H');
	//NODE *I = GetNode('I');
	//NODE *J = GetNode('J');
	//NODE *K = GetNode('K');
	//NODE *L = GetNode('L');

	NODE *Root = GetNode(-9); // Đây chính là Node gốc
	NODE *B = GetNode(2);
	NODE *C = GetNode(-50);
	NODE *D = GetNode(-1);
	NODE *E = GetNode(0);
	NODE *F = GetNode(-16);
	NODE *G = GetNode(-7);
	NODE *H = GetNode(6);
	NODE *I = GetNode(3);
	NODE *J = GetNode(-4);
	NODE *K = GetNode(-10);
	NODE *L = GetNode(-9);

	// Bước 2: Tạo ra các mối liên kết giữa các Node với nhau

	Root->Left = B;
	B->Cha = Root;

	Root->Right = C;
	C->Cha = Root;

	B->Left = D;
	D->Cha = B;

	B->Right = E;
	E->Cha = B;

	C->Left = F;
	F->Cha = C;

	C->Right = G;
	G->Cha = C;

	D->Left = H;
	H->Cha = D;

	D->Right = I;
	I->Cha = D;

	E->Right = J;
	J->Cha = E;

	F->Left = K;
	K->Cha = F;

	G->Right = L;
	L->Cha = G;


	/*NODE *M = GetNode('M');
	E->Left = M;

	NODE *N = GetNode('N');
	F->Right = N;

	NODE *O = GetNode('O');
	G->Left = O;*/

	/* ========================================= */

	//printf("\nDo sau cua Node %c la: %d", B->Data, TinhDoSauCuaNodeBatKy_KhongDeQuyKhongStack(B));

	//DuyetCayKhongDeQuyKhongStack(C, "NLR");

	//printf("\nChieu cao cua cay la: %d", TinhChieuCaoCuaCay_KhongDeQuyKhongStack(Root));

	/*vector<vector<NODE *>> arr = CapNhatLevelChoCacNodeVaTraVeMang2ChieuChuaDanhSachCacNode_KhongDeQuyKhongStack(D);

	for(int i = 0; i < arr.size(); ++i)
	{
	printf("\nTang %d: ", i + 1);
	for(int j = 0; j < arr[i].size(); ++j)
	{
	printf("%c ", arr[i][j]->Data);
	}
	}*/

	clock_t start1 = clock();
	for(int i = 1; i <= 100000; ++i)
	{
		int TongMax = INT_MIN; // Chỗ này nếu để TongMax = Root->Data sẽ bị sai vì chúng ta đang xét tất cả cây con của 1 Node nên trừ khi TongMax = tổng các cây con của 1 Node bất kỳ trong cây thì được, còn không để đơn giản chúng ta cho nó bằng giá trị nhỏ nhất của kiểu int (INT_MIN) để đảm bảo mọi giá trị đều lớn hơn nó mà cập nhật lại TongMax
		NODE *p_Max = Root; // Chỗ này nếu gán con trỏ p = Root thì không sao vì chắc chắn Node có cây con có tổng lớn nhất cũng luôn chỉ nằm trong phạm vi các node của cây đang có => cho nó khởi tạo bằng Root hay bằng 1 node bất kỳ có trong cây đều được
		TimCayConCoTongLonNhat(Root, TongMax, p_Max);
		//printf("\nCay con co tong lon nhat la: %d va do la cay %d", TongMax, p_Max->Data);
	}
	clock_t end1 = clock();

	clock_t start2 = clock();
	for(int i = 1; i <= 100000; ++i)
	{
		NODE *p_Max_Khudequy = TimCayConCoTongLonNhat_KhuDeQuy(Root);
		//printf("\nCay con co tong lon nhat (khu de quy) la: %d", p_Max_Khudequy->Data);
	}
	clock_t end2 = clock();

	clock_t start3 = clock();
	for(int i = 1; i <= 100000; ++i)
	{
		int TongMax_Cach2 = INT_MIN; // Chỗ này nếu để TongMax = Root->Data sẽ bị sai vì chúng ta đang xét tất cả cây con của 1 Node nên trừ khi TongMax = tổng các cây con của 1 Node bất kỳ trong cây thì được, còn không để đơn giản chúng ta cho nó bằng giá trị nhỏ nhất của kiểu int (INT_MIN) để đảm bảo mọi giá trị đều lớn hơn nó mà cập nhật lại TongMax
		NODE *p_Max_Cach2 = Root; // Chỗ này nếu gán con trỏ p = Root thì không sao vì chắc chắn Node có cây con có tổng lớn nhất cũng luôn chỉ nằm trong phạm vi các node của cây đang có => cho nó khởi tạo bằng Root hay bằng 1 node bất kỳ có trong cây đều được
		TimCayConCoTongLonNhat_Cach2(Root, TongMax_Cach2, p_Max_Cach2);
		//printf("\nCay con co tong lon nhat (cach 2) la: %d va do la cay %d", TongMax_Cach2, p_Max_Cach2->Data);
	}
	clock_t end3 = clock();

	clock_t start4 = clock();
	for(int i = 1; i <= 100000; ++i)
	{
		NODE *p_Max_Khudequy_Cach2 = TimCayConCoTongLonNhat_KhuDeQuy_Cach2(Root);
		//printf("\nCay con co tong lon nhat (khu de quy - Cach 2) la: %d", p_Max_Khudequy_Cach2->Data);
	}
	clock_t end4 = clock();
	

	printf("\nTimCayConCoTongLonNhat chay mat %lf giay", (double)(end1 - start1) / CLOCKS_PER_SEC);
	printf("\nTimCayConCoTongLonNhat_KhuDeQuy chay mat %lf giay", (double)(end2 - start2) / CLOCKS_PER_SEC);
	printf("\nTimCayConCoTongLonNhat_Cach2 chay mat %lf giay", (double)(end3 - start3) / CLOCKS_PER_SEC);
	printf("\nTimCayConCoTongLonNhat_KhuDeQuy_Cach2 chay mat %lf giay", (double)(end4 - start4) / CLOCKS_PER_SEC);

	/*int DoLechMax = 0;
	NODE *p = NULL;
	TimDoLechLonNhatTrenCay_DeQuy(Root, DoLechMax, p);
	printf("\nDo lech lon nhat tren cay (de quy) la: %d va lech tai Node %c", DoLechMax, p->Data);
	

	printf("\nDo lech lon nhat tren cay (khu de quy) la: %d", TimDoLechLonNhatTrenCay_KhuDeQuy(Root));*/


	/*DuyetCayKhongDeQuyKhongStack(B, "NLR");
	printf("\nDuyet cay lon: ");
	DuyetCayKhongDeQuyKhongStack(Root, "NLR");*/

	/*char data = 'l';
	NODE *p = TimKiemNodeCoDataXTrongCay_KhongDeQuyKhongStack(Root, data);
	if(p == NULL)
	printf("\nKhong tim thay bat ky node nao co data la %c trong cay", data);
	else
	{
	int DoSau = TinhDoSauCuaNodeBatKy_KhongDeQuyKhongStack(p);
	printf("\nTim thay Node co data la %c va do sau cua no la: %d", p->Data, DoSau);
	}*/

	//printf("\nBac cua cay la: %d", TinhBacCuaCay_KhongDeQuyKhongStack(Root));

	//printf("\nSo luong cac node la: %d", DemSoLuongCacNodeLa_DeQuyThuong(Root));
	/*int SoLuongCacNodeLa = 0;
	DemSoLuongCacNodeLa_DeQuyDuoi(Root, SoLuongCacNodeLa);
	printf("\nSo luong cac node la: %d", SoLuongCacNodeLa);*/

	//printf("\nSo luong cac node co du 2 con la: %d", DemSoLuongCacNodeCoDu2Con_DeQuyThuong(Root));
	/*int SoLuongCacNodeCoDu2Con = 0;
	DemSoLuongCacNodeCoDu2Con_DeQuyDuoi(Root, SoLuongCacNodeCoDu2Con);
	printf("\nSo luong cac node co du 2 con la: %d", SoLuongCacNodeCoDu2Con);*/

	//printf("\nSo luong cac node co duy nhat 1 con la: %d", DemSoLuongCacNodeCoDuyNhat1Con_DeQuyThuong(Root));
	/*int SoLuongCacNodeCoDuyNhat1Con = 0;
	DemSoLuongCacNodeCoDuyNhat1Con_DeQuyDuoi(Root, SoLuongCacNodeCoDuyNhat1Con);
	printf("\nSo luong cac node co duy nhat 1 con la: %d", SoLuongCacNodeCoDuyNhat1Con);*/

	//printf("\nBac cua Node %c la %d", J->Data, TinhBacCua1Node(J));
	/*int BacCuaCay = 0;
	TinhBacCuaCay(Root, BacCuaCay);
	printf("\nCay co bac la: %d", BacCuaCay);*/

	/*int ChieuCaoCay = TinhChieuCaoCuaCay_DeQuyThuong(Root);
	printf("\nTinhChieuCaoCuaCay_DeQuyThuong: Cay co chieu cao la: %d", ChieuCaoCay);*/

	/*int ChieuCao = 0;
	TinhChieuCaoCuaCay_DeQuyDuoi(Root, ChieuCao, 1);
	printf("\nTinhChieuCaoCuaCay_DeQuyDuoi: Cay co chieu cao la: %d", ChieuCao);*/

	/*bool TimThayX = false;
	char x = 'M';
	int dosaucuaNode;
	TimNodeX(Root, TimThayX, x, dosaucuaNode, 1);
	if(TimThayX == true)
	printf("\nDa tim thay node co data la %c => do sau cua node la: %d", x, dosaucuaNode);
	else
	printf("\nKhong co node nao trong cay co data la %c", x);*/

	/*int k = 5;
	int count = 0;
	printf("\nCac node nam tren tang %d la: ", k);
	LietKeVaDemCacNodeTrenTangK(Root, k, count, 1);

	if(count == 0)
	printf("\nKhong co node nao nam tren tang %d", k);
	else
	printf("\n=> Co %d node", count);*/

	//LietKeCacNodeTrenMoiTang(Root);

	/*int k = 3;
	int demSoLuongNode = 0;
	char *s = ">=";
	LietKeVaDemCacNodeCoTangThoaDieuKienVoiTangK(Root, s, k, demSoLuongNode);
	printf("\n=> Co %d node thoa dieu kien co tang %s tang %d", demSoLuongNode, s, k);*/

	/*bool KiemTraCayNhiPhanDayDu_Cach1 = KiemTraCayNhiPhanCoLaCayNhiPhanDayDu_Cach1(Root);
	if(KiemTraCayNhiPhanDayDu_Cach1 == true)
	printf("\nKiemTraCayNhiPhanDayDu_Cach1 => Day la cay nhi phan day du");
	else
	printf("\nKiemTraCayNhiPhanDayDu_Cach1 => Day khong phai la cay nhi phan day du");

	bool KiemTraCayNhiPhanDayDu_Cach2 = KiemTraCayNhiPhanCoLaCayNhiPhanDayDu_Cach2(Root);
	if(KiemTraCayNhiPhanDayDu_Cach2 == true)
	printf("\nKiemTraCayNhiPhanDayDu_Cach2 => Day la cay nhi phan day du");
	else
	printf("\nKiemTraCayNhiPhanDayDu_Cach2 => Day khong phai la cay nhi phan day du");*/

	//vector<vector<NODE *>> Mang2Chieu;
	//DuyetCayVaTaoDanhSachMang2ChieuChuaCacNode(Root, Mang2Chieu);

	/*for(int i = 0; i < Mang2Chieu.size(); ++i)
	{
	for(int j = 0; j < Mang2Chieu[i].size(); ++j)
	{
	printf("%c ", Mang2Chieu[i][j]->Data);
	}
	printf("\n");
	}*/

	/*int k = 4;
	for(int j = 0; j < Mang2Chieu[k - 1].size(); ++j)
	{
	printf("%c ", Mang2Chieu[k - 1][j]->Data);
	}
	printf("\n=> Co %d node", Mang2Chieu[k - 1].size());*/

	/*bool KiemTraCayNhiPhanHoanChinh = KiemTraCayNhiPhanCoLaCayNhiPhanHoanChinh(Root);
	if(KiemTraCayNhiPhanHoanChinh == true)
	printf("\n=> Day la cay nhi phan hoan chinh");
	else
	printf("\n=> Day khong phai la cay nhi phan hoan chinh");*/

	/*int KiemTraCayDayDuHayHoanChinh = KiemTraCayNhiPhanLaCayNhiPhanDayDuHayCayNhiPhanHoanChinh(Root);
	if(KiemTraCayDayDuHayHoanChinh == 1)
	printf("\n=> Day la cay nhi phan day du");
	else if(KiemTraCayDayDuHayHoanChinh == 2)
	printf("\n=> Day la cay nhi phan hoan chinh");
	else
	printf("\n=> Day la cay nhi phan");*/

	/* Tạo ra 1 cây nhị phân đầy đủ có độ cao là k */
	//int k = 15;
	//NODE *Root = GetNode(1);
	//queue<NODE *> q;
	//q.push(Root);

	//while(true)
	//{
	//NODE *p = q.front();
	//q.pop();

	//if(p->Data == pow(2.0, k - 1))
	//break;

	//NODE *p_Left = GetNode(2 * p->Data);
	//p->Left = p_Left;
	//p_Left->Cha = p;

	//NODE *p_Right = GetNode(2 * p->Data + 1);
	//p->Right = p_Right;
	//p_Right->Cha = p;

	//q.push(p_Left);
	//q.push(p_Right);
	//}

	//
	//clock_t start1 = clock();
	////for(int i = 1; i <= 10000; ++i)
	//int dem = 0;
	//DemSoLuongCacNodeCoDu2Con_DeQuyDuoi(Root, dem);
	//clock_t end1 = clock();

	//printf("\nDemSoLuongCacNodeCoDu2Con_DeQuyDuoi chay mat %lf giay", (double)(end1 - start1)/ CLOCKS_PER_SEC);

	//clock_t start2 = clock();
	////for(int i = 1; i <= 10000; ++i)
	//DemSoLuongCacNodeTrenCayCoDu2Con_KhongDeQuyKhongStack(Root);
	//clock_t end2 = clock();

	//printf("\nDemSoLuongCacNodeTrenCayCoDu2Con_KhongDeQuyKhongStack chay mat %lf giay", (double)(end2 - start2)/ CLOCKS_PER_SEC);

	/*
	clock_t start1 = clock();
	bool KiemTraCayNhiPhanDayDu_Cach1 = KiemTraCayNhiPhanCoLaCayNhiPhanDayDu_Cach1(Root);
	clock_t end1 = clock();

	printf("\nKiemTraCayNhiPhanDayDu_Cach1 chay mat %lf giay", (double)(end1 - start1) / CLOCKS_PER_SEC);

	clock_t start2 = clock();
	bool KiemTraCayNhiPhanDayDu_Cach2 = KiemTraCayNhiPhanCoLaCayNhiPhanDayDu_Cach2(Root);
	clock_t end2 = clock();

	printf("\nKiemTraCayNhiPhanDayDu_Cach2 chay mat %lf giay", (double)(end2 - start2) / CLOCKS_PER_SEC);*/

	//DuyetTheoChieuRong(Root);

	//printf("\nDuyet theo chieu rong: ");
	//DuyetTheoChieuRong(Root);
	//
	//printf("\nDuyet truoc: ");
	//PreOrder(Root, 2);

	//printf("\nDuyet giua: ");
	//InOrder(Root, 2);

	//printf("\nDuyet sau: ");
	//PostOrder(Root, 2);

	//clock_t start1 = clock();
	//int SoLuongCacNode = 0;
	//for(int i = 1; i <= 1000; ++i)
	//	DemSoLuongCacNodeTrenCay_DeQuyDuoi(Root, SoLuongCacNode);
	////printf("\nDemSoLuongCacNodeTrenCay_DeQuyDuoi: %d", SoLuongCacNode);
	//clock_t end1 = clock();

	//printf("\nDemSoLuongCacNodeTrenCay_DeQuyDuoi chay mat %lf giay", (double)(end1 - start1) / CLOCKS_PER_SEC);

	//clock_t start2 = clock();
	//for(int i = 1; i <= 1000; ++i)
	//	DemSoLuongCacNodeTrenCay_DeQuyThuong(Root);
	//clock_t end2 = clock();
	////printf("\nDemSoLuongCacNodeTrenCay_DeQuyThuong: %d", DemSoLuongCacNodeTrenCay_DeQuyThuong(Root));

	//printf("\nDemSoLuongCacNodeTrenCay_DeQuyThuong chay mat %lf giay", (double)(end2 - start2) / CLOCKS_PER_SEC);

	//clock_t start3 = clock();
	//
	//for(int i = 1; i <= 1000; ++i)
	//	DemSoLuongCacNodeTrenCay_KhongDeQuy(Root);
	////printf("\nDemSoLuongCacNodeTrenCay_DeQuyDuoi: %d", SoLuongCacNode);
	//clock_t end3 = clock();

	//// Cách làm tuy không dùng đệ quy nhưng nó lại phải dùng queue và với mỗi thao tác push, pop đã phải mất quá nhiều thời gian xử lý => bị chậm hơn so với 2 cách kia. Nếu đếm số lượng các node thì chỉ đơn giản là duyệt qua và không cần phải làm gì phức tạp thêm nhưng không dùng đệ quy
	//printf("\nDemSoLuongCacNodeTrenCay_KhongDeQuy chay mat %lf giay", (double)(end3 - start3) / CLOCKS_PER_SEC);

	//printf("\nDemSoLuongCacNodeTrenCay_KhongDeQuy: %d", DemSoLuongCacNodeTrenCay_KhongDeQuy(Root));

	/* ================ TỪ CHỖ NÀY TRỞ ĐI LÀM KHỬ ĐỆ QUY =============== */



	//PreOrder_KhuDeQuyDungStack(Root);
	//InOrder_KhuDeQuyDungStack(Root);
	//PostOrder_KhuDeQuyDungStack(Root, 2);
	//DuyetCayKhongDeQuyKhongStack(Root, "nLr");
	//DuyetCayKhongDeQuyKhongStack(Root, "LNR");
	//DuyetCayKhongDeQuyKhongStack(Root, "lrn");

	printf("\n\nGiai phong cay\n");
	//RemoveAll(Root); // giải phóng bộ nhớ đã cấp phát cho cây
	RemoveAll_KhuDeQuy(Root);

	getch();
	return 0;
}
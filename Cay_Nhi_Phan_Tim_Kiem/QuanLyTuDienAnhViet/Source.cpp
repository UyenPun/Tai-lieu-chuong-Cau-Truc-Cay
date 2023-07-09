#include <iostream>
#include <string>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
using namespace std;

// TỪ
struct Tu
{
	string TiengAnh;
	string TiengViet;
};
typedef struct Tu TU;

// Xây dựng các phép toán operator để so sánh 2 cấu trúc WORD với nhau để từ đó có thể tìm kiếm/thêm/xóa node trong cây
bool operator >(TU a, TU b)
{
	/*if(a.TiengAnh > b.TiengAnh)
		return true;

	return false;*/
	

	// 2 dòng trên gom lại viết thành 1 dòng thế này
	//return strcmp(strlwr((char *)a.TiengAnh.c_str()), strlwr((char *)b.TiengAnh.c_str())) > 0 ? true : false;

	return a.TiengAnh > b.TiengAnh;
}

bool operator <(TU a, TU b)
{
	//return strcmp(strlwr((char *)a.TiengAnh.c_str()), strlwr((char *)b.TiengAnh.c_str())) < 0 ? true : false;

	return a.TiengAnh < b.TiengAnh;
}

bool operator ==(TU a, TU b)
{
	//return strcmp(strlwr((char *)a.TiengAnh.c_str()), strlwr((char *)b.TiengAnh.c_str())) == 0 ? true : false;

	return a.TiengAnh == b.TiengAnh;
}

bool operator !=(TU a, TU b)
{
	//return strcmp(strlwr((char *)a.TiengAnh.c_str()), strlwr((char *)b.TiengAnh.c_str())) != 0 ? true : false;

	return a.TiengAnh != b.TiengAnh;
}

/* 1/ Khai báo cấu trúc dữ liệu cây nhị phân tìm kiếm */

struct Node
{
	TU Data; // cây nhị phân tìm kiếm chứa các WORD (từ điển)
	struct Node *Left, *Right; // Trỏ tới các Node cây con trái và cây con phải
	
	// 2 thành phần này là để tham gia vào quá trình duyệt cây không dùng đệ quy không dùng stack
	int ThuTuDuyet;
	struct Node *Cha;
};
typedef struct Node NODE;
// typedef NODE* Tree; // Tree t; => t là 1 Node (NODE *)

/* End 1 */

/* 2/ Khởi tạo cây */

void INit(NODE *&Root)
{
	Root = NULL;
}

/* End 2 */

/* 3/ Tạo node */

// Tạo 1 Node mới chứa dữ liệu x và trả về địa chỉ của Node đó sau khi tạo xong
NODE* GetNode(TU x) // x là dữ liệu mà sẽ đưa nó vào trong Node
{
	NODE *p = new NODE; // cấp phát con trỏ Node kiểu của bên C++
	//NODE *p = (NODE *)malloc(sizeof(NODE)); // cấp phát con trỏ Node kiểu của bên C
	if(p == NULL)
		return NULL; // Không tạo thành công do thiếu vùng nhớ để cấp phát tạo ra Node

	// Nếu vẫn còn chạy được xuống đây tức là không thỏa cái if => Node được tạo thành công
	p->Data = x; // đưa dữ liệu x vào trong Node p
	p->Left = p->Right = NULL; // cập nhật con trỏ Left, Right là NULL
	p->ThuTuDuyet = 0;
	p->Cha = NULL;

	return p; // trả về Node p đã được tạo
}

/* End 3 */

void BienThanhChuThuong(string &str)
{
	int length = str.length();
	for(int i = 0; i < length; ++i)
	{
		// Nếu phát hiện ký tự là ký tự hoa => đổi về ký tự thường
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
}



// tìm giá trị x xem có tồn tại ở node nào đó trong cây không? Nếu có thì trả về node đó, nếu không có thì trả về node đứng trước node đó để phục vụ cho mục đích thêm node vào cây
NODE* TimKiemNode_KhuDeQuy(NODE *Root, TU x) 
{
	NODE *p = Root;
	NODE *q = p; // q là Node cuối cùng trước khi đến NULL => mục đích: Để có thể từ đó tạo liên kết thêm node mới vào
	while(p != NULL)
	{
		q = p;

		if(x > p->Data)
			p = p->Right;
		else if(x < p->Data)
			p = p->Left;
		else // x == p->Data
			return p; // Điều kiện dừng đã tìm thấy
	}

	// Chạy xuống đây tức là Root đã = NULL => không tìm thấy
	return q; // Trả về Node cuối cùng trước khi đến NULL
}

// 40, 5, 35, 45, 15, 56, 35, 35, 35, 48, 13, 16, 49, 47
// return 1: Thành công
// return 0: Không thành công (bị trùng)
// return -1: Không thành công (không đủ bộ nhớ để cấp phát cho Node)
int ThemNodeVaoCay_KhuDeQuy(NODE *&Root, TU x) // thêm giá trị x vào cây
{
	// Từ ban đầu cây chưa có gì => tạo node gốc cho cây
	if(Root == NULL)
	{
		Root = GetNode(x);
	}
	else // cây đã có node gốc rồi thì tiến hành thêm lần lượt các node tiếp theo vào và so sánh để tìm vị trí thích hợp để thêm
	{
		NODE *p = TimKiemNode_KhuDeQuy(Root, x); 

		if(p->Data != x) // vì thế phải xét tiêu chí giá trị của p phải khác x => thêm mới vào chứ không bị trùng
		{
			// Thêm Node mới vào
			NODE *ConMoi = GetNode(x);

			if(ConMoi == NULL)
				return -1; // Không thành công (không đủ bộ nhớ để cấp phát cho Node)

			if(x > p->Data)
				p->Right = ConMoi;
			else if(x < p->Data)
				p->Left = ConMoi;

			ConMoi->Cha = p;
		}
		else
		{
			return 0; // Không thành công (bị trùng)
		}
	}
	return 1; // thành công
}

void GiaiPhongCay_KhuDeQuy(NODE *&Root)
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

					delete Root;
					Root = NULL;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
				{
					NODE *q = Root;
					Root = Root->Cha;
					delete q;
					q = NULL;
				}
			}
		}
	}
}

void NhapMotTu(TU &a)
{
	fflush(stdin);
	cout << "\nNhap vao tu Tieng Anh: ";
	getline(cin, a.TiengAnh);

	fflush(stdin);
	cout << "\nNhap vao nghia Tieng Viet tuong ung: ";
	getline(cin, a.TiengViet);

	// Ngay khi nhập xong thì nó chuẩn hóa từ tiếng Anh thành chữ thường luôn
	BienThanhChuThuong(a.TiengAnh);
	BienThanhChuThuong(a.TiengViet);
}

// ví dụ như gặp số âm là dừng lại
void TaoCayNhapTuBanPhimKhongBietTruocSoLuong(NODE *&Root)
{
	TU x;
	char c;
	do{

		NhapMotTu(x);

		int ketqua = ThemNodeVaoCay_KhuDeQuy(Root, x);

		if(ketqua == 0)
			printf("\nLoi: Gia tri Node nay da co ton tai trong cay roi cho nen khong them vao cay duoc nua");
		else if(ketqua == -1)
			printf("\nLoi: Khong du bo nho de cap phat cho Node");
		else if(ketqua == 0)
			cout << "\nThem thanh cong vao tu dien";

		printf("\nBan co muon nhap nua khong? Nhan phim c de nhap tiep. Nhan phim bat ky khac de ket thuc");
		c = getch(); // chờ kết quả tương tác của người dùng từ bàn phím

		if(c == 'c' || c == 'C')
			system("cls"); // Xóa hết màn hình

	}while(c == 'c' || c == 'C'); // Cho phép nhập tiếp
}

void LRN(NODE *Root)
{
	if(Root != NULL)
	{
		LRN(Root->Left);
		LRN(Root->Right);
		cout << Root->Data.TiengAnh << ": " << Root->Data.TiengViet << endl;
	}
}

// p là Node thế mạng sẽ xóa
void TimPhanTuTheMang_KhuDeQuy(NODE *&Root, NODE *&p) 
{
	// q là Node thế mạng cần xóa
	NODE *q = Root;
	NODE *k = p; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó. Khởi đầu thì k = p (Node cần xóa)
	
	while(q->Right != NULL)
	{
		k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
		q = q->Right;
	}

	// Sau vòng lặp thì q là Node phải nhất (Tức là nếu trỏ phải lần nữa thì sẽ là NULL => q là phải nhất)

	// Phải để đoạn lệnh này trước 2 đoạn lệnh sau để cập nhật liên kết cho xong rồi từ đó mới muốn cho trỏ đi đâu thì trỏ. Nếu không sẽ bị lỗi nếu để 2 đoạn lệnh dưới lên trên đoạn lệnh này
	if(q->Data > k->Data)
		k->Right = q->Left;
	else if(q->Data < k->Data)
		k->Left = q->Left;

	if(q->Left != NULL)
		q->Left->Cha = k;

	p->Data = q->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
	p = q; // Cho con trỏ p trỏ tới Node thế mạng (q) để kết thúc hàm thì sẽ free(p) chính là free(q)
}


// return 1: Xóa thành công
// return 0: Không xóa thành công (Node cần xóa không tồn tại trong cây)
int XoaNodeTrongCay_KhuDeQuy(NODE *&Root, TU x) // x là giá trị cần xóa ra khỏi cây
{
	NODE *q = Root;
	NODE *k = NULL; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó
	while(q != NULL)
	{
		if(x > q->Data)
		{
			k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
			q = q->Right;
		}
		else if(x < q->Data)
		{
			k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
			q = q->Left;
		}
		else // tìm thấy x trong cây tại Node q => tiến hành xóa
		{
			NODE *p = q; // p là Node sẽ bị xóa: Lý do dùng Node tạm p để xóa mà không xóa trực tiếp q bởi vì lỡ trong cùng 1 hàm sau khi xóa xong lại có nhu cầu duyệt cây tiếp thì lại duyệt dựa theo Node q nếu mà q bị xóa thì đâu còn duyệt được nữa

			// TH1: Node cần xóa là Node lá
			// TH2: Node cần xóa là Node có 1 con

			// Giữ liên kết với phần còn lại của Node bị xóa
			if(p->Left == NULL)
			{
				// k là Node cha của Node q cần xóa => k sẽ trỏ liên kết để giữ cháu của nó (giữ con của node cần xóa)
				// Làm sao biết k phải trỏ Left hay Right đến cháu của nó? => tùy thuộc q cần xóa đang là con trái hay con phải của k
				if(k != NULL) // k có tồn tại
				{
					if(p->Data > k->Data)
						k->Right = p->Right;
					else if(p->Data < k->Data)
						k->Left = p->Right;

					if(p->Right != NULL)
						p->Right->Cha = k;
				}
				else // Nếu ngay từ đầu k rỗng (tức là Node p cần xóa chính là Node gốc của cây
				{
					Root = Root->Right; // Cập nhật trực tiếp Node gốc của cây sẽ trỏ sang con của nó
					
					if(Root != NULL)
						Root->Cha = NULL;
				}
			}
			else if(p->Right == NULL)
			{
				if(k != NULL) // k có tồn tại
				{
					// k là Node cha của Node q cần xóa => k sẽ trỏ liên kết để giữ cháu của nó (giữ con của node cần xóa)
					// Làm sao biết k phải trỏ Left hay Right đến cháu của nó? => tùy thuộc q cần xóa đang là con trái hay con phải của k
					if(p->Data > k->Data)
						k->Right = p->Left;
					else if(p->Data < k->Data)
						k->Left = p->Left;

					if(p->Left != NULL)
						p->Left->Cha = k;
				}
				else // Nếu ngay từ đầu k rỗng (tức là Node p cần xóa chính là Node gốc của cây
				{
					Root = Root->Left; // Cập nhật trực tiếp Node gốc của cây sẽ trỏ sang con của nó
					
					if(Root != NULL)
						Root->Cha = NULL;
				}
			}
			else // p->Left != NULL && p->Right != NULL => TH3: Node cần xóa là Node có đủ 2 con
			{
				TimPhanTuTheMang_KhuDeQuy(q->Left, p); // Tìm phần tử thế mạng: Phải nhất của cây con trái
			}
			delete p; // giải phóng p
			return 1; // Xóa thành công - kết thúc hàm
		}
	}
	return 0; // Không xóa thành công (Node cần xóa không tồn tại trong cây)
}

void DuyetCayKhongDeQuyKhongStack(NODE *Root, char *s) // s = "NLR" hoặc "LNR" hoặc "LRN" hoặc "NRL" hoặc "RNL" hoặc "RLN"
{
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
					cout << Root->Data.TiengAnh << ": " << Root->Data.TiengViet << endl;

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
}

void DocFileTuDien(NODE *&Root)
{
	ifstream FileIn;
	FileIn.open("tudien.txt", ios_base::in);

	if(!FileIn)
	{
		cout << "\nKhong tim thay tap tin tudien.txt nen cay ban dau se khoi tao rong (khong co du lieu san trong cay)";
		FileIn.close();
		return;
	}

	// Nếu vẫn chạy được xuống dưới đây tức là có tồn tại tập tin => đọc dữ liệu vào cây
	cout << "\nDu lieu tu dien trong tap tin tudien.txt da duoc doc vao cay thanh cong";

	while(!FileIn.eof())
	{
		TU x;
		getline(FileIn, x.TiengAnh, ':');
		getline(FileIn, x.TiengViet);

		if(x.TiengAnh != "")
		{
			ThemNodeVaoCay_KhuDeQuy(Root, x);
		}
		
	}

	FileIn.close();
}

void GhiFileTuDien(NODE *Root)
{
	ofstream FileOut;
	FileOut.open("tudien.txt", ios_base::out);

	if(Root != NULL)
	{
		char *s = "NLR";
		NODE *cha = Root->Cha;
		Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		
		while(true)
		{

			if(Root->ThuTuDuyet <= 2)
			{
				if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					FileOut << Root->Data.TiengAnh << ":" << Root->Data.TiengViet << endl;

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

	FileOut.close();
}

void Menu()
{
	NODE *Root;
	INit(Root); // Phải nhớ khởi tạo cho cây để tránh bị lỗi
	
	DocFileTuDien(Root);
	
	int menu1;

menucha:

	do{
		printf("\n===============> Menu <===============\n");
		printf("\n1. Them tu moi vao tu dien");
		printf("\n2. Xoa 1 tu trong tu dien");
		printf("\n3. Cap nhat 1 tu trong tu dien");
		printf("\n4. Tra cuu nghia Tieng Viet cua 1 tu trong tu dien");
		printf("\n5. Xuat danh sach cac tu trong tu dien theo thu tu tang dan");
		printf("\n0. Thoat chuong trinh");
		printf("\n======================================\n");

		printf("\nNhap vao lua chon (0 -> 5): ");
		scanf("%d", &menu1);

		if(menu1 < 0 || menu1 > 5)
		{
			printf("\nLua chon chi duoc trong khoang 0 -> 5. Nhan enter nhap lai!");
			system("pause");
			system("cls");
		}
	}while(menu1 < 0 || menu1 > 5);

	
	if(menu1 == 1) // Them Node vao cay (du lieu nhap vao tu ban phim)
	{
		TaoCayNhapTuBanPhimKhongBietTruocSoLuong(Root);
	}
	else if(menu1 == 2)
	{
		TU s;
		fflush(stdin);
		cout << "\nNhap vao tu Tieng Anh can xoa khoi cay tu dien: ";
		getline(cin, s.TiengAnh);

		// Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
		BienThanhChuThuong(s.TiengAnh);

		int kq = XoaNodeTrongCay_KhuDeQuy(Root, s);

		if(kq == 1)
			cout << "\nDa xoa thanh cong tu: " << s.TiengAnh << " ra khoi cay";
		else if(kq == 0)
			cout << "\nKhong tim thay tu " << s.TiengAnh << " trong cay nen khong xoa duoc!";
	}
	else if(menu1 == 3)
	{
		TU s;
		fflush(stdin);
		cout << "\nNhap vao tu Tieng Anh can cap nhat: ";
		getline(cin, s.TiengAnh);

		// Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
		BienThanhChuThuong(s.TiengAnh);

		NODE *p = TimKiemNode_KhuDeQuy(Root, s);

		if(p->Data == s) // tìm thấy
		{
			int luachon;
			do{
				cout << "\nBan muon cap nhat tu Tieng Viet hay muon cap nhat ca Tieng Anh lan Tieng Viet?";
				cout << "\n1. Cap nhat tu Tieng Viet";
				cout << "\n2. Cap nhat ca Tieng Anh lan Tieng Viet";

				cout << "\nNhap vao lua chon cua Ban: ";
				cin >> luachon;

				if(luachon < 1 || luachon > 2)
					cout << "\nLua chon chi duoc la 1 hoac 2. Xin kiem tra lai!";

			}while(luachon < 1 || luachon > 2);

			if(luachon == 1)
			{
				fflush(stdin);
				cout << "\nNhap vao nghia Tieng Viet can cap nhat lai cho tu nay: ";
				getline(cin, s.TiengViet);

				BienThanhChuThuong(s.TiengViet);

				p->Data.TiengViet = s.TiengViet; // Cập nhật lại tiếng việt

				cout << "\nDa cap nhat thanh cong nghia Tieng Viet cua tu " << s.TiengAnh;
			}
			else
			{
				cout << "\nNhu vay chuong trinh se xoa di tu hien tai va them moi lai tu moi cho Ban nhap vao";
				XoaNodeTrongCay_KhuDeQuy(Root, p->Data);

				TU x;
				NhapMotTu(x);
				int kq = ThemNodeVaoCay_KhuDeQuy(Root, x);

				if(kq == 1)
					cout << "\nDa them thanh cong tu moi";
				else if(kq == 0)
					cout << "\nKhong them duoc do tu can them da bi trung voi 1 tu dang co trong cay tu dien";
				else if(kq == -1)
					cout << "\nKhong them duoc do khong du bo nho de cap phat";

			}

			
		}
		else // không tìm thấy
			cout << "\nKhong tim thay tu Tieng Anh: " << s.TiengAnh << " trong cay nen khong cap nhat duoc!";
	}
	else if(menu1 == 4)
	{
		TU s;
		fflush(stdin);
		cout << "\nNhap vao tu Tieng Anh can tra cuu nghia Tieng Viet: ";
		getline(cin, s.TiengAnh);

		// Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
		BienThanhChuThuong(s.TiengAnh);

		NODE *p = TimKiemNode_KhuDeQuy(Root, s);

		if(p->Data == s) // tìm thấy
			cout << "\nTu Tieng Anh: " << s.TiengAnh << " co nghia Tieng Viet la: " << p->Data.TiengViet; 
		else // không tìm thấy
			cout << "\nKhong tim thay tu Tieng Anh: " << s.TiengAnh << " trong cay nen khong tra cuu duoc!";
	}
	else if(menu1 == 5)
	{
		DuyetCayKhongDeQuyKhongStack(Root, "LNR"); // Duyệt cây LNR để xuất dữ liệu trong cây theo thứ tự tăng dần của các khóa trong Node
	}
	else if(menu1 == 0) // Thoat chuong trinh => phải giải phóng cây
	{
		GhiFileTuDien(Root);

		cout << "\nDu lieu tu dien da duoc ghi vao tap tin tudien.txt";

		GiaiPhongCay_KhuDeQuy(Root);

		if(Root == NULL)
			printf("\nCay duoc giai phong thanh cong truoc khi thoat chuong trinh");
		else
			printf("\nCay chua duoc giai phong truoc khi thoat chuong trinh vi ly do gi do");

		getch();
		exit(0); // tắt chương trình luôn
	}
	
	printf("\nNhan enter de quay tro lai Menu chinh");
	system("pause");
	system("cls"); // xóa hết màn hình đi
	goto menucha;
}

int main()
{
	Menu();

	system("pause");
	return 0;
}
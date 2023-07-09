#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

/* Khai báo cấu trúc dữ liệu cây nhị phân */

struct Ngay
{
	int Day, Month, Year;
};
typedef struct Ngay NGAY;

struct DocGia
{
	char MaDocGia[6]; // có thêm 1 ký tự ở cuối cùng cho việc kết thúc chuỗi
	char TenDocGia[31]; // có thêm 1 ký tự ở cuối cùng cho việc kết thúc chuỗi
	NGAY NgaySinh;
	char DiaChi[31]; // có thêm 1 ký tự ở cuối cùng cho việc kết thúc chuỗi
	NGAY NgayLapThe;
};
typedef struct DocGia DOCGIA;

struct Node
{
	DOCGIA Data; // dữ liệu trong Node là ký tự
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
NODE* GetNode(DOCGIA x) // x là dữ liệu đưa vào trong Node
{
	//NODE *p = (NODE *)malloc(sizeof(DOCGIA));
	//NODE *p = (NODE *)calloc(1, sizeof(DOCGIA));
	//NODE *p = (NODE *)realloc(0, sizeof(DOCGIA));
	
	NODE *p = new NODE;

	// Trường hợp máy tính hết bộ nhớ để cấp phát
	if(p == NULL)
		return NULL;

	// Nếu còn chạy được xuống dưới này tức là Node không rỗng => khởi tạo thành công
	p->Data = x; // x được cập nhật vô Data của Node p
	p->Left = p->Right = NULL; // Khởi tạo liên kết con trái và con phải của Node p là NULL
	
	return p; // Trả về Node p sau khi được tạo ra và cập nhật dữ liệu
}


void RemoveAll(NODE *&Root)
{
	if(Root != NULL)
	{
		RemoveAll(Root->Left); // Xét tiếp qua nhánh con trái của Node hiện tại
		RemoveAll(Root->Right); // Xét tiếp qua nhánh con phải của Node hiện tại
		//free(Root); // Giải phóng Node đang xét đến. Lưu ý: Phải giải phóng nó sau cùng (duyệt sau) chứ nếu dùng duyệt trước hay duyệt giữa thì sau khi giải phóng lấy gì mà tiếp tục trỏ? => LỖI
		
		delete Root; // trong trường hợp kiểu dữ liệu tự tạo thì chúng ta dùng delete sẽ giải phóng bình thường cho Node còn dùng cách cấp phát bên C thì sẽ bị lỗi
		
		Root = NULL; // Sau khi giải phóng xong phải cập nhật cho Node đó giá trị NULL nếu không sẽ bị lỗi ngang nếu sau khi giải phóng xong người dùng có thao tác tiếp gì đó (vd: duyệt cây)
	}
}

void XuatThongTinDocGia(DOCGIA x)
{
		printf("\nMa doc gia: %s", x.MaDocGia);
	printf("\nTen doc gia: %s", x.TenDocGia);
	printf("\nSinh ngay: %d/%d/%d", x.NgaySinh.Day, x.NgaySinh.Month, x.NgaySinh.Year);
	printf("\nDia chi: %s", x.DiaChi);
	printf("\nNgay lap the: %d/%d/%d", x.NgayLapThe.Day, x.NgayLapThe.Month, x.NgayLapThe.Year);
}

bool operator > (NGAY x, NGAY y)
{
	if(x.Year < y.Year)
		return true;
	else if(x.Year == y.Year)
	{
		if(x.Month < y.Month)
			return true;
		else if(x.Month == y.Month)
		{
			if(x.Day < y.Day)
				return true;
		}
	}
	return false;
}

void TimDocGiaLonTuoiNhat(NODE *Root, NODE *&p_TuoiMax, NGAY &TuoiMax)
{
	if(Root != NULL)
	{

		if(Root->Data.NgaySinh > TuoiMax)
		{
			TuoiMax = Root->Data.NgaySinh;
			p_TuoiMax = Root;
		}

		TimDocGiaLonTuoiNhat(Root->Left, p_TuoiMax, TuoiMax);
		TimDocGiaLonTuoiNhat(Root->Right, p_TuoiMax, TuoiMax);
	}
}

void LietKeCacDocGiaSinhSauNamX(NODE *Root, int year_X)
{
	if(Root != NULL)
	{
		if(Root->Data.NgaySinh.Year > year_X)
			XuatThongTinDocGia(Root->Data);

		LietKeCacDocGiaSinhSauNamX(Root->Left, year_X);
		LietKeCacDocGiaSinhSauNamX(Root->Right, year_X);
	}
}

bool operator == (NGAY x, NGAY y)
{
	if(x.Day != y.Day)
		return false;

	if(x.Month != y.Month)
		return false;

	if(x.Year != y.Year)
		return false;

	return true;
}

void DemSoLuongNodeCoDu2ConCoNgayTheTrungNgayX(NODE *Root, NGAY x, int &dem)
{
	if(Root != NULL)
	{
		if(Root->Left != NULL && Root->Right != NULL && Root->Data.NgayLapThe == x)
		{
			dem++;
		}

		DemSoLuongNodeCoDu2ConCoNgayTheTrungNgayX(Root->Left, x, dem);
		DemSoLuongNodeCoDu2ConCoNgayTheTrungNgayX(Root->Right, x, dem);
	}
}

void TimKiemDocGiaTrongCayTheoMaSo(NODE *Root, char *madocgia, NODE *&p, bool &TimThay)
{
	if(Root != NULL && TimThay == false) // chỉ xét khi Node có tồn tại và giá trị chưa được tìm thấy
	{
		printf("\nBat dau xet vo Node co ma so la: %s", Root->Data.MaDocGia);
		if(strcmp(Root->Data.MaDocGia, madocgia) == 0)
		{
			p = Root;
			printf("\nDa tim thay va return");
			TimThay = true; // đã tìm thấy
			return;
		}

		TimKiemDocGiaTrongCayTheoMaSo(Root->Left, madocgia, p, TimThay);
		TimKiemDocGiaTrongCayTheoMaSo(Root->Right, madocgia, p, TimThay);
	}
}

int main()
{
	DOCGIA dg_1;
	strcpy(dg_1.MaDocGia, "1");
	strcpy(dg_1.TenDocGia, "Nguyen Van A");
	dg_1.NgaySinh.Day = 18;
	dg_1.NgaySinh.Month = 12;
	dg_1.NgaySinh.Year = 1953;
	strcpy(dg_1.DiaChi, "Go Vap");
	dg_1.NgayLapThe.Day = 6;
	dg_1.NgayLapThe.Month = 5;
	dg_1.NgayLapThe.Year = 2004;

	DOCGIA dg_2;
	strcpy(dg_2.MaDocGia, "2");
	strcpy(dg_2.TenDocGia, "Tran Thi B");
	dg_2.NgaySinh.Day = 7;
	dg_2.NgaySinh.Month = 7;
	dg_2.NgaySinh.Year = 1954;
	strcpy(dg_2.DiaChi, "Tan Phu");
	dg_2.NgayLapThe.Day = 7;
	dg_2.NgayLapThe.Month = 5;
	dg_2.NgayLapThe.Year = 2004;

	DOCGIA dg_3;
	strcpy(dg_3.MaDocGia, "3");
	strcpy(dg_3.TenDocGia, "Ly Thi C");
	dg_3.NgaySinh.Day = 31;
	dg_3.NgaySinh.Month = 10;
	dg_3.NgaySinh.Year = 1994;
	strcpy(dg_3.DiaChi, "Binh Thanh");
	dg_3.NgayLapThe.Day = 7;
	dg_3.NgayLapThe.Month = 5;
	dg_3.NgayLapThe.Year = 2004;

	DOCGIA dg_4;
	strcpy(dg_4.MaDocGia, "4");
	strcpy(dg_4.TenDocGia, "Teo Van D");
	dg_4.NgaySinh.Day = 6;
	dg_4.NgaySinh.Month = 3;
	dg_4.NgaySinh.Year = 1996;
	strcpy(dg_4.DiaChi, "Kien Giang");
	dg_4.NgayLapThe.Day = 31;
	dg_4.NgayLapThe.Month = 3;
	dg_4.NgayLapThe.Year = 2012;

	DOCGIA dg_5;
	strcpy(dg_5.MaDocGia, "5");
	strcpy(dg_5.TenDocGia, "Khoai Thi E");
	dg_5.NgaySinh.Day = 2;
	dg_5.NgaySinh.Month = 10;
	dg_5.NgaySinh.Year = 1990;
	strcpy(dg_5.DiaChi, "Ho Chi Minh");
	dg_5.NgayLapThe.Day = 30;
	dg_5.NgayLapThe.Month = 4;
	dg_5.NgayLapThe.Year = 2008;


	NODE *docgia_1 = GetNode(dg_1);
	NODE *docgia_2 = GetNode(dg_2);
	NODE *docgia_3 = GetNode(dg_3);
	NODE *docgia_4 = GetNode(dg_4);
	NODE *docgia_5 = GetNode(dg_5);

	docgia_1->Left = docgia_2;
	docgia_1->Right = docgia_3;

	docgia_2->Left = docgia_4;
	docgia_3->Right = docgia_5;


	// Lấy ngày hiện tại đang đứng để đảm bảo mọi ngày sinh đều lớn hơn ngày hiện tại
	time_t t = time(0);
	struct tm *Now = localtime(&t);
	NGAY TuoiMax;
	TuoiMax.Day = Now->tm_mday;
	TuoiMax.Month = Now->tm_mon + 1;
	TuoiMax.Year = Now->tm_year + 1900;

	NODE *p_TuoiMax = docgia_1;

	TimDocGiaLonTuoiNhat(docgia_1, p_TuoiMax, TuoiMax);

	printf("\nDoc gia co tuoi lon nhat la: ");
	XuatThongTinDocGia(p_TuoiMax->Data);

	int year_X = 1975;
	printf("\nLiet ke cac doc gia sinh sau nam %d", year_X);
	LietKeCacDocGiaSinhSauNamX(docgia_1, year_X);

	NGAY ngaylapthe;
	ngaylapthe.Day = 7;
	ngaylapthe.Month = 5;
	ngaylapthe.Year = 2004;

	int dem = 0;

	DemSoLuongNodeCoDu2ConCoNgayTheTrungNgayX(docgia_1, ngaylapthe, dem);
	printf("\nSo luong node co du 2 con co ngay lap the trong ngay %d/%d/%d la: %d", ngaylapthe.Day, ngaylapthe.Month, ngaylapthe.Year, dem);

	char *madocgiacantim = "2";
	NODE *p_DocGiaTimThay = NULL;
	bool TimThay = false;
	TimKiemDocGiaTrongCayTheoMaSo(docgia_1, madocgiacantim, p_DocGiaTimThay, TimThay);

	if(p_DocGiaTimThay == NULL)
		printf("\nKhong tim thay doc gia co ma la: %s", madocgiacantim);
	else
	{
		printf("\nTim thay doc gia co ma la: %s tai node co dia chi la: %p", madocgiacantim, p_DocGiaTimThay);
		printf("\nThong tin cua doc gia: ");
		XuatThongTinDocGia(p_DocGiaTimThay->Data);

	}

	printf("\n\nGiai phong cay\n");
	RemoveAll(docgia_1); // giải phóng bộ nhớ đã cấp phát cho cây

	getch();
	return 0;
}
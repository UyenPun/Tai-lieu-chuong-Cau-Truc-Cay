#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stack>
#include <Windows.h>
using namespace std;

bool KiemTraLaHamMotNgoi(string s);

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

/* Khai báo cấu trúc dữ liệu cây nhị phân */
struct Node
{
	string Data; // dữ liệu trong Node là ký tự
	struct Node *Left, *Right; // con trỏ trỏ đến liên kết Node trái và Node phải
	float KetQua;
	bool ToMau;
};
typedef struct Node NODE;
//typedef NODE* Tree;

/* ===================================== */

/* Tạo node */

// Hàm này sẽ khởi tạo ra 1 Node mới và đưa x vào Data của Node đó sau đó trả Node đó về
NODE* GetNode(string x) // x là dữ liệu đưa vào trong Node
{
	NODE *p = new NODE;
	
	// Trường hợp máy tính hết bộ nhớ để cấp phát
	if(p == NULL)
		return NULL;

	// Nếu còn chạy được xuống dưới này tức là Node không rỗng => khởi tạo thành công
	p->Data = x; // x được cập nhật vô Data của Node p
	p->Left = p->Right = NULL; // Khởi tạo liên kết con trái và con phải của Node p là NULL
	p->ToMau = false; // không được tô
	return p; // Trả về Node p sau khi được tạo ra và cập nhật dữ liệu
}

// duyệt giữa
void LNR(NODE *Root)
{
	if(Root != NULL)
	{
		if(Root->Left != NULL || KiemTraLaHamMotNgoi(Root->Data) == true) // nếu nhắm có thể đi qua trái được => in ra dấu mở ngoặc
			cout << "( ";

	
		LNR(Root->Left);

		if(Root->ToMau == true)
			textcolor(14); // tô màu vàng

		cout << Root->Data << " ";

		textcolor(7); // trở lại màu như thường

		LNR(Root->Right);

		if(Root->Right != NULL) // sau khi đã đi qua phải rồi thì sẽ trả nợ dấu đóng ngoặc
			cout << ")"; 
	}
}

void LRN(NODE *Root)
{
	if(Root != NULL)
	{
		LRN(Root->Left);
		LRN(Root->Right);
		cout << " " << Root->Data;
	}
}

// true: là số, false: không phải là số
bool KiemTraLaSo(string s)
{
	return s[s.length() - 1] >= '0' && s[s.length() - 1] <= '9'; // nên xét ký tự cuối cùng chứ không nên xét ký tự đầu tiên vì nếu số âm thì ký tự đầu tiên là - chứ không phải là số
}

// true: là toán tử, false: không là toán tử
bool KiemTraLaToanTu(string s)
{
	return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

bool KiemTraLaMoNgoac(string s)
{
	return s == "(";
}

bool KiemTraLaDongNgoac(string s)
{
	return s == ")";
}

bool KiemTraLaHamMotNgoi(string s)
{
	return s == "abs" || s == "sqrt" || s == "sin" || s == "cos" || s == "tan" || s == "log" || s == "!";
}

bool KiemTraLaHamHaiNgoi(string s)
{
	return s == "sqrtn" || s == "logn";
}

int TinhGiaiThua(int x)
{
	int Tich = 1;
	for(int i = 1; i <= x; ++i)
		Tich *= i;

	return Tich;
}

float TinhCanBacXCuaY(float x, float y) // x là căn bậc, y là số cần tính căn
{
	return pow(y, 1.0 / x);
}

float TinhLogaritCoSoXCuaY(float x, float y) // x là cơ số, y là số cần tính logarit
{
	return log10(y) / log10(x);
}

int TinhDoUuTien(string s)
{
	//if(s == "abs" || s == "sqrt" || s == "sin" || s == "cos" || s == "tan" || s == "log" || s == "!" || s == "sqrtn" || s == "logn")
	if(KiemTraLaHamMotNgoi(s) == true || KiemTraLaHamHaiNgoi(s) == true)	
		return 4;

	if(s == "^")
		return 3;

	if(s == "*" || s == "/")
		return 2;

	if(s == "+" || s == "-")
		return 1;

	return 0; // mở ngoặc
}

// Hàm tách này hoạt động với chuỗi s ở dạng bất kỳ (viết liền nhau hay cách bao nhiêu khoảng trắng) đều được
vector<string> TachCacPhanTuTrongChuoiTrungToBanDau(string s)
{
	vector<string> a;

	int length = s.length();
	int idx;
	for(int i = 0; i < length; ++i)
	{
		if(s[i] != ' ')
		{
			string temp;
			temp.push_back(s[i]);

			a.push_back(temp);
			idx = i;
			break;
		}
	}

	for(int i = idx + 1; i < length; ++i)
	{
		if(s[i] != ' ') // Xét ký tự phải khác rỗng thì mới tiến hành kiểm tra xét duyệt
		{
			string phantucuoi = a[a.size() - 1]; // lấy phần tử cuối cùng hiện tại đang có trong mảng a
			char kytucuoi = phantucuoi[phantucuoi.length() - 1]; // lấy ký tự cuối cùng của phần tử cuối trong mảng a
			
			if(s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '!')
			{
				// trong trường hợp dấu , dùng để ngăn cách giữa 2 số => sau khi chuẩn bị tạo mới số thứ 2 thì xóa ký tự , của số thứ 1 đi
				if(kytucuoi == ',')
					a[a.size() - 1].erase(phantucuoi.length() - 1);

				string temp;
				temp.push_back(s[i]);

				a.push_back(temp);
			}
			else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			{
				//string phantucuoi = a[a.size() - 1]; // lấy phần tử cuối cùng hiện tại đang có trong mảng a
				//char kytucuoi = phantucuoi[phantucuoi.length() - 1]; // lấy ký tự cuối cùng của phần tử cuối trong mảng a

				if((kytucuoi >= 'a' && kytucuoi <= 'z') || (kytucuoi >= 'A' && kytucuoi <= 'Z'))
				{
					a[a.size() - 1].push_back(s[i]);
				}
				else
				{
					// trong trường hợp dấu , dùng để ngăn cách giữa 2 số => sau khi chuẩn bị tạo mới số thứ 2 thì xóa ký tự , của số thứ 1 đi
					if(kytucuoi == ',')
						a[a.size() - 1].erase(phantucuoi.length() - 1);

					string temp;
					temp.push_back(s[i]);

					a.push_back(temp);
				}
			}
			else if(s[i] >= '0' && s[i] <= '9')
			{
				//string phantucuoi = a[a.size() - 1]; // lấy phần tử cuối cùng hiện tại đang có trong mảng a
				//char kytucuoi = phantucuoi[phantucuoi.length() - 1]; // lấy ký tự cuối cùng của phần tử cuối trong mảng a

				if((kytucuoi >= '0' && kytucuoi <= '9') || kytucuoi == '.')
				{
					a[a.size() - 1].push_back(s[i]);
				}
				else if(kytucuoi == '-')
				{
					if(a.size() <= 1)
					{
						a[a.size() - 1].push_back(s[i]);
					}
					else // a.size() > 1 
					{
						string phantuapcuoi = a[a.size() - 2];

						if(KiemTraLaMoNgoac(phantuapcuoi) == true || KiemTraLaToanTu(phantuapcuoi) == true)
						{
							a[a.size() - 1].push_back(s[i]);
						}
						else if(KiemTraLaDongNgoac(phantuapcuoi) == true || KiemTraLaSo(phantuapcuoi) == true || phantuapcuoi == "!")
						{
							// trong trường hợp dấu , dùng để ngăn cách giữa 2 số => sau khi chuẩn bị tạo mới số thứ 2 thì xóa ký tự , của số thứ 1 đi
							if(kytucuoi == ',')
								a[a.size() - 1].erase(phantucuoi.length() - 1);

							string temp;
							temp.push_back(s[i]);

							a.push_back(temp);
						}
					}

				}
				else
				{
					// trong trường hợp dấu , dùng để ngăn cách giữa 2 số => sau khi chuẩn bị tạo mới số thứ 2 thì xóa ký tự , của số thứ 1 đi
					if(kytucuoi == ',')
						a[a.size() - 1].erase(phantucuoi.length() - 1);

					string temp;
					temp.push_back(s[i]);

					a.push_back(temp);
				}

			}
			else if(s[i] == '.' || s[i] == ',')
			{
				a[a.size() - 1].push_back(s[i]);
			}
		}
	}
	return a;
}

// Đầu vào: chuỗi s là chuỗi trung tố
// Đầu ra: Trả về vector hậu tố
vector<string> Buoc1_ChuyenBieuThucTrungToSangHauTo(string s)
{
	vector<string> a; // mảng 1 chiều chứa các phần tử trong chuỗi input đầu vào

	// substr(vị trí bắt đầu cắt, số lượng ký tự muốn lấy) => substr(2, 2)
	
	// Chỉ làm đúng khi mỗi phần tử trong chuỗi s cách nhau đúng 1 khoảng trắng
	// Tách ra các phần tử trong chuỗi input đầu vào lưu vào mảng a
	//char *p = strtok((char *)s.c_str(), " ");
	//while(p != NULL)
	//{
	//	a.push_back(p); // giả sử chỗ này nó báo lỗi là dữ liệu đưa vào phải là kiểu string chứ ko thể là kiểu char * => search google cách chuyển từ kiểu char * sang kiểu string. vd: How to convert char * to string in c++
	//	//printf("p = %s\n", p);
	//	p = strtok(NULL, " ");
	//}

	// Chuỗi s có ra sao đi nữa miễn các ký tự đúng theo thứ tự quan hệ của nó là sẽ tách ra được hết
	a = TachCacPhanTuTrongChuoiTrungToBanDau(s);

	// Lấy các phần tử đã lưu trong mảng a đem đi xử lý
	//string hauto = "";
	vector<string> hauto;
	stack<string> nganxep;

	// Duyệt mảng a để xét lần lượt các phần tử và có xử lý tương ứng
	int size = a.size();
	for(int i = 0; i < size; ++i)
	{
		cout << a[i] << " ";

		if(KiemTraLaSo(a[i]) == true) // + Số => đưa luôn vào biểu thức hậu tố
		{
			//hauto += a[i] + " ";
			hauto.push_back(a[i]);
		}
		else if(KiemTraLaMoNgoac(a[i]) == true) // + Dấu mở ngoặc => đưa luôn vào Stack
		{
			nganxep.push(a[i]);
		}
		else if(KiemTraLaToanTu(a[i]) == true || KiemTraLaHamMotNgoi(a[i]) == true || KiemTraLaHamHaiNgoi(a[i]) == true) // + Toán tử (+, -, *, /, ^) => xét độ ưu tiên trong Stack để từ đó điều phối
		{
			bool Check = false;
			while(!nganxep.empty())
			{
				string daustack = nganxep.top();
				if(TinhDoUuTien(a[i]) > TinhDoUuTien(daustack))
				{
					Check = true;
					nganxep.push(a[i]);
					break; // nếu thỏa thì dừng quá trình lặp luôn
				}
				else // a[i] độ ưu tiên thấp hơn => lấy phần tử đầu stack bỏ qua bên hậu tố và xét lại độ ưu tiên với phần tử đầu stack mới
				{
					nganxep.pop(); // bỏ phần tử đầu stack hiện tại
					//hauto += daustack + " "; // đem đầu stack trước đó bỏ qua hậu tố
					hauto.push_back(daustack);
				}
			}

			if(Check == false) // khi if này xảy ra tức là a[i] luôn có độ ưu tiên thấp hơn các phần tử trong stack (hoặc stack ngay từ đầu đã rỗng) => đưa a[i] vào stack luôn
			{
				nganxep.push(a[i]);
			}
		}
		else if(KiemTraLaDongNgoac(a[i]) == true) // + Dấu đóng ngoặc => lấy các phần tử trong Stack bỏ vào hậu tố đến khi nào gặp mở ngoặc thì dừng lại
		{
			while(!nganxep.empty())
			{
				string daustack = nganxep.top();
				nganxep.pop();

				if(daustack != "(")
				{
					//hauto += daustack + " ";
					hauto.push_back(daustack);
				}
				else
				{
					break;
				}
			}
		}
	}

	// Khi đã xét hết các phần tử rồi thì sẽ lấy giá trị còn lại trong stack bỏ qua hậu tố
	while(!nganxep.empty())
	{
		string daustack = nganxep.top();
		nganxep.pop();

		//hauto += daustack + " ";
		hauto.push_back(daustack);
	}
	return hauto;
}

NODE *Buoc2_TuBieuThucHauToDungThanhCayNhiPhan(vector<string> hauto)
{
	// Bước 2:
	stack<NODE *> nganxep;

	int size = hauto.size();

	// Duyệt vòng lặp xét các phần tử hậu tố để xử lý tương ứng
	for(int i = 0; i < size; ++i)
	{
		NODE *n = GetNode(hauto[i]);

		if(KiemTraLaToanTu(hauto[i]) == true || KiemTraLaHamHaiNgoi(hauto[i]) == true)
		{
			NODE *y = nganxep.top();
			nganxep.pop();

			NODE *x = nganxep.top();
			nganxep.pop();

			n->Left = x;
			n->Right = y;
		}
		else if(KiemTraLaHamMotNgoi(hauto[i]) == true)
		{
			NODE *x = nganxep.top();
			nganxep.pop();

			if(hauto[i] == "!") // đối với trường hợp ! thì giá trị tính giai thừa nằm trước giai thừa => Left
				n->Left = x;
			else // đối với những hàm 1 ngôi như sqrt, abs, sin, cos, tan, log thì giá trị tính nằm đằng sau => Right
				n->Right = x; // Cho trỏ Left hay Right tới x đều được nhưng nếu trỏ tới Right thì khi duyệt theo thứ tự Left - Node - Right nó sẽ ra trình tự đúng còn nếu trỏ tới Left thì khi duyệt LNR nó sẽ in ra số trước rồi mới gọi abs sau
		}

		nganxep.push(n);
	}

	//NODE *Root = nganxep.top();
	return nganxep.top();
}

void Buoc3_TinhGiaTriBieuThuc(NODE *Root, NODE *goc, int &dem)
{
	if(Root != NULL)
	{
		Buoc3_TinhGiaTriBieuThuc(Root->Left, goc, dem);
		Buoc3_TinhGiaTriBieuThuc(Root->Right, goc, dem);

		if(KiemTraLaSo(Root->Data) == true)
		{
			// "10" -> 10 => string to float // vd: how to convert string to float in c++
			//Root->KetQua = stof(Root->Data); // từ C++ 11 trở lên là có hàm này hỗ trợ chuyển từ kiểu string sang kiểu float
			Root->KetQua = atof((char *)Root->Data.c_str()); // Hàm hỗ trợ chuỗi bên C => chuyển chuỗi string bên C++ sang kiểu C rồi áp dụng như bình thường
		}
		else if(KiemTraLaToanTu(Root->Data) == true || KiemTraLaHamHaiNgoi(Root->Data) == true)
		{
			float x = Root->Left->KetQua;
			float y = Root->Right->KetQua;
			float ketqua;

			if(Root->Data == "+")
				ketqua = x + y;
			else if(Root->Data == "-")
				ketqua = x - y;
			else if(Root->Data == "*")
				ketqua = x * y;
			else if(Root->Data == "/")
				ketqua = x / y;
			else if(Root->Data == "^")
				ketqua = pow(x, y);
			else if(Root->Data == "sqrtn")
				ketqua = TinhCanBacXCuaY(x, y);
			else if(Root->Data == "logn")
				ketqua = TinhLogaritCoSoXCuaY(x, y);
			
			system("pause"); // nhờ vào system("pause") để có thể xuất kết quả của từng bước
			cout << "\n\nBuoc " << dem << ":";
			cout << "\nChon phep toan xu ly: ";

			// bật tô màu cho các node tương ứng
			Root->ToMau = true; // toán tử
			Root->Left->ToMau = true; // số hạng trái
			Root->Right->ToMau = true; // số hạng phải

			LNR(goc);

			Root->KetQua = ketqua;
			Root->Data = to_string(Root->KetQua); // how to convert float to string in c++

			Root->Left = Root->Right = NULL;
			cout << "\nXu ly phep toan: ";
			LNR(goc);

			// Reset lại ban đầu
			Root->ToMau = false;

			dem++;
		}
		else if(KiemTraLaHamMotNgoi(Root->Data) == true)
		{
			float y, ketqua;

			if(Root->Data == "!")
			{
				y = Root->Left->KetQua;
				Root->Left->ToMau = true;
			}
			else
			{
				y = Root->Right->KetQua;
				Root->Right->ToMau = true;
			}
			

			if(Root->Data == "abs")
				ketqua = abs(y);
			else if(Root->Data == "sqrt")
				ketqua = sqrt(y);
			else if(Root->Data == "sin")
				ketqua = sin(y);
			else if(Root->Data == "cos")
				ketqua = cos(y);
			else if(Root->Data == "tan")
				ketqua = tan(y);
			else if(Root->Data == "log")
				ketqua = log10(y);
			else if(Root->Data == "!")
				ketqua = TinhGiaiThua(y);

			system("pause"); // nhờ vào system("pause") để có thể xuất kết quả của từng bước
			cout << "\n\nBuoc " << dem << ":";
			cout << "\nChon phep toan xu ly: ";
			Root->ToMau = true; // hàm
			LNR(goc);

			Root->KetQua = ketqua;
			Root->Data = to_string(Root->KetQua); // how to convert float to string in c++

			if(Root->Left != NULL)
				Root->Left = NULL;
			else if(Root->Right != NULL)
				Root->Right = NULL;

			cout << "\nXu ly phep toan: ";
			LNR(goc);

			// Reset lại ban đầu
			Root->ToMau = false;

			dem++;
		}
	}
}

float TinhGiaTriBieuThuc(string s)
{
	vector<string> hauto = Buoc1_ChuyenBieuThucTrungToSangHauTo(s);

	/*for(int i = 0; i < hauto.size(); ++i)
		cout << hauto[i] << endl;*/

	NODE *Root = Buoc2_TuBieuThucHauToDungThanhCayNhiPhan(hauto);
	NODE *goc = Root;
	/*cout << "\nDuyet giua: ";
	LNR(Root);

	cout << "\nDuyet sau: ";
	LRN(Root);*/

	int dem = 1;
	Buoc3_TinhGiaTriBieuThuc(Root, goc, dem);

	//cout << "\nBieu thuc ban dau: " << s;
	//cout << "\nGia tri cua bieu thuc la: " << Root->KetQua;
	return Root->KetQua;
}

int main()
{
	//string s = "sqrtn(2, sqrtn(2, 2 * 8))";
	string s = "log(abs(logn(10, (sqrtn(4, 16) * 5) ^ 2)! * -5))"; // 2 2 16 sqrtn sqrtn
	//string s = "(2*(3       +4)           -4)/         5+2";
	//string s = "   -203   *(-3.5    + -4   )-4       /   5-2    ";
	//string s = "( 10 / 2 + 3 ) * ( 7 - 4 )";
	//string s = "4 * ( 3 - 5 ) + ( 1 - 2 * 3 )";
	//string s = "5 - 8 * 2 + 9 / 2 - 6";
	//string s = "1 - 2 + 3 / 4 * ( 5 - 6 * 7 ) / 2 + ( 9 - 1 * 8 ) + 5";
	//string s = "-90.54-(5*8/(4+6)--3/(2+1)*-2.3)/-100";

	cout << "\nTinh gia tri cua bieu thuc: ";

	cout << "\n\nKet luan: Ket qua cuoi cung cua bieu thuc la: " << TinhGiaTriBieuThuc(s);

	system("pause");
	return 0;
}
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>

// Khai báo cấu trúc cây AVL
struct Node
{
	char Data;
	struct Node *Left, *Right;
	struct Node *Cha;
	int ThuTuDuyet;
};
typedef struct Node NODE;

int TinhChieuCaoCay_DeQuy(NODE *Root);
int XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(NODE *&Root);
int XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(NODE *&Root, NODE *&ConMoi);

// Khởi tạo cây
void INit(NODE *&Root)
{
	Root = NULL;
}

// Tạo ra 1 Node mới chứa giá trị x (Data) và trả về Node đó (địa chỉ)
NODE* GetNode(char x) 
{
	NODE *p = (NODE *)malloc(sizeof(NODE));

	if(p == NULL)
		return NULL; // Không đủ bộ nhớ để cấp phát

	// Nếu chạy được xuống đây tức là đã có bộ nhớ để cấp phát => cài đặt cho Node p
	p->Data = x; // Đưa giá trị x vào Data của Node
	p->Left = p->Right = NULL; // Cho 2 liên kết con trái, con phải của Node mới tạo là NULL
	p->Cha = NULL;
	p->ThuTuDuyet = 0;

	return p; // Trả về Node đã tạo ra (địa chỉ)
}

// Quay trái tại Node Root
void QuayTrai(NODE *&Root)
{
	NODE *cha = Root->Cha;
	NODE *Pivot = Root->Right;

	Root->Right = Pivot->Left;

	if(Pivot->Left != NULL)
		Pivot->Left->Cha = Root; // Phải cập nhật lại tình cha con nếu dùng đến phương pháp khử đệ quy

	Pivot->Left = Root;
	Root->Cha = Pivot; // Phải cập nhật lại tình cha con nếu dùng đến phương pháp khử đệ quy

	Root = Pivot; // cập nhật lại Root mới
	Root->Cha = cha; // Phải cập nhật lại tình cha con nếu dùng đến phương pháp khử đệ quy
}

// Quay phai tại Node Root
void QuayPhai(NODE *&Root)
{
	NODE *cha = Root->Cha;
	NODE *Pivot = Root->Left;

	Root->Left = Pivot->Right;

	if(Pivot->Right != NULL)
		Pivot->Right->Cha = Root; // Phải cập nhật lại tình cha con nếu dùng đến phương pháp khử đệ quy

	Pivot->Right = Root;
	Root->Cha = Pivot; // Phải cập nhật lại tình cha con nếu dùng đến phương pháp khử đệ quy

	Root = Pivot; // cập nhật lại Root mới
	Root->Cha = cha; // Phải cập nhật lại tình cha con nếu dùng đến phương pháp khử đệ quy
}

// return 0: Không thêm thành công (do bị trùng)
// return -1: Không thêm thành công (do không đủ bộ nhớ)
// return 1: Thêm thành công
int ThemNodeVaoCay_DeQuy(NODE *&Root, char x) // x là giá trị cần thêm vào cây
{
	int ketqua;
	if(Root != NULL)
	{
		if(x > Root->Data)
			ketqua = ThemNodeVaoCay_DeQuy(Root->Right, x);
		else if(x < Root->Data)
			ketqua = ThemNodeVaoCay_DeQuy(Root->Left, x);
		else
			return 0; // Không thêm thành công (do bị trùng)
	}
	else // Root == NULL
	{
		NODE *con = GetNode(x);

		if(con == NULL)
			return -1; // Không thêm thành công (do không đủ bộ nhớ)

		// Nếu con được tạo ra thành công thì chạy xuống đây
		Root = con; // Cho Root trỏ tới con

		return 1; // Thêm thành công
	}

	if(ketqua == 1) // Node đã thêm thành công => xét ngược về các Node cha để kiểm tra xem có bị mất cân bằng ở các Node cha trước đó không?
	{
		//int chieucaocontrai = 0;
		//int chieucaoconphai = 0;

		//if(Root->Left != NULL)
		//	chieucaocontrai = TinhChieuCaoCay_DeQuy(Root->Left);

		//if(Root->Right != NULL)
		//	chieucaoconphai = TinhChieuCaoCay_DeQuy(Root->Right);

		//if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
		//{
		//	//printf("\n=> Cay bi mat can bang tai Node %c", Root->Data);

		//	if(chieucaocontrai > chieucaoconphai) // Lệch trái
		//	{
		//		int chieucaocontrai_2 = 0;
		//		int chieucaoconphai_2 = 0;

		//		if(Root->Left->Left != NULL)
		//			chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(Root->Left->Left);

		//		if(Root->Left->Right != NULL)
		//			chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(Root->Left->Right);

		//		if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
		//		{
		//			//printf("\nMat can bang Trai - Trai");
		//			//printf("\n=> Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
		//			QuayPhai(Root);
		//		}
		//		else // Trái - Phải
		//		{
		//			//printf("\nMat can bang Trai - Phai");
		//			//printf("\nBuoc 1: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Left->Data, Root->Left->Data, Root->Left->Right->Data);
		//			QuayTrai(Root->Left);

		//			//printf("\nBuoc 2: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
		//			QuayPhai(Root);
		//		}
		//	}
		//	else // Lệch phải
		//	{
		//		int chieucaocontrai_2 = 0;
		//		int chieucaoconphai_2 = 0;

		//		if(Root->Right->Left != NULL)
		//			chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(Root->Right->Left);

		//		if(Root->Right->Right != NULL)
		//			chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(Root->Right->Right);

		//		if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
		//		{
		//			//printf("\nMat can bang Phai - Phai");
		//			//printf("\n=> Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
		//			QuayTrai(Root);
		//		}
		//		else // Phải - Trái
		//		{
		//			//printf("\nMat can bang Phai - Trai");
		//			//printf("\nBuoc 1: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Right->Data, Root->Right->Data, Root->Right->Left->Data);
		//			QuayPhai(Root->Right);

		//			//printf("\nBuoc 2: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
		//			QuayTrai(Root);
		//		}
		//	}
		//	return 2; // để không cần phải lùi về xét lại cây có mất cân bằng không
		//}
		//return 1; // Tiếp tục xét lùi về các Node trước đó
		int kq = XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);

		if(kq == 1) // bị mất cân bằng và đã cân bằng xong => dừng lại không xét nữa
			return 2;
		else if(kq == 0) // không bị mất cân bằng => tiếp tục lùi về xét các Node trước đó
			return 1;
	}
}

void NLR(NODE *Root)
{
	if(Root != NULL)
	{
		printf("%c ", Root->Data);
		NLR(Root->Left);
		NLR(Root->Right);
	}
}

void GiaiPhongCay(NODE *&Root)
{
	if(Root != NULL)
	{
		GiaiPhongCay(Root->Left);
		GiaiPhongCay(Root->Right);
		free(Root);
		Root = NULL;
	}
}

int TinhChieuCaoCay_DeQuy(NODE *Root)
{
	if(Root == NULL)
		return 0;

	int left = TinhChieuCaoCay_DeQuy(Root->Left);
	int right = TinhChieuCaoCay_DeQuy(Root->Right);

	return left > right ? left + 1 : right + 1;
}

// tìm giá trị x xem có tồn tại ở node nào đó trong cây không? Nếu có thì trả về node đó, nếu không có thì trả về node đứng trước node đó để phục vụ cho mục đích thêm node vào cây
NODE* TimKiemNode_KhuDeQuy(NODE *Root, char x) 
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
						Root = Root->Left;
					}
				}
				else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if(Root->Right != NULL)
					{
						Root = Root->Right;
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

// tìm giá trị x xem có tồn tại ở node nào đó trong cây không? Nếu có thì trả về node đó, nếu không có thì trả về node đứng trước node đó để phục vụ cho mục đích thêm node vào cây
NODE* TimKiemNode_DeQuy(NODE *Root, int x, NODE *NodeTruocNull) 
{
	// Điều kiện dừng: Khi không tìm thấy
	if(Root == NULL)
		return NodeTruocNull;

	// Điều kiện đệ quy
	//if(Root != NULL) // Cũng không cần viết điều kiện này bởi vì chúng ta đã xét nếu Root == NULL ở đầu tiên của hàm nên nếu nó còn chạy được xuống dưới này tức là Root != NULL
	//{
	if(x > Root->Data)
		return TimKiemNode_DeQuy(Root->Right, x, Root);
	else if(x < Root->Data)
		return TimKiemNode_DeQuy(Root->Left, x, Root);
	else // x == Root->Data
		return Root; // Điều kiện dừng: Khi đã tìm thấy
	//}
}

// return 1: Thành công
// return 0: Không thành công (bị trùng)
// return -1: Không thành công (không đủ bộ nhớ để cấp phát cho Node)
int ThemNodeVaoCay_KhuDeQuy(NODE *&Root, char x) // thêm giá trị x vào cây
{
	// Từ ban đầu cây chưa có gì => tạo node gốc cho cây
	if(Root == NULL)
	{
		Root = GetNode(x);
	}
	else // cây đã có node gốc rồi thì tiến hành thêm lần lượt các node tiếp theo vào và so sánh để tìm vị trí thích hợp để thêm
	{
		// p là Node đứng trước Node NULL (nếu trong trường hợp trong cây không có node nào có giá trị trùng với giá trị đang cần thêm)
		// p là Node có giá trị trùng với giá trị đang cần thêm trong trường hợp đã có node có giá trị đó tồn tại


		NODE *p = TimKiemNode_KhuDeQuy(Root, x); 
		//NODE *p = TimKiemNode_DeQuy(Root, x, NULL);

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

			// Bắt đầu kiểm tra tính cân bằng của cây để xem cây có bị mất cân bằng tại Node nào thì tiến hành cân bằng lại
			while(ConMoi->Cha != NULL)
			{
				ConMoi = ConMoi->Cha;

				// Bắt đầu kiểm tra tính cân bằng của ConMoi (chính là cha của Node mới thêm liên tục trỏ về Cha)

				int kq = XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(Root, ConMoi);

				if(kq == 1)
					break;
			}
		}
	}
	return 1; // thành công
}

// Trả về 1: Nếu tại Node có bị mất cân bằng và tiến hành cân bằng lại
// Trả về 0: Nếu tại Node không có mất cân bằng
int XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(NODE *&Root)
{
	int chieucaocontrai = 0;
	int chieucaoconphai = 0;

	if(Root->Left != NULL)
		chieucaocontrai = TinhChieuCaoCay_DeQuy(Root->Left);

	if(Root->Right != NULL)
		chieucaoconphai = TinhChieuCaoCay_DeQuy(Root->Right);

	if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
	{
		//printf("\n=> Cay bi mat can bang tai Node %c", Root->Data);

		if(chieucaocontrai > chieucaoconphai) // Lệch trái
		{
			int chieucaocontrai_2 = 0;
			int chieucaoconphai_2 = 0;

			if(Root->Left->Left != NULL)
				chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(Root->Left->Left);

			if(Root->Left->Right != NULL)
				chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(Root->Left->Right);

			if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
			{
				//printf("\nMat can bang Trai - Trai");
				//printf("\n=> Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
				QuayPhai(Root);
			}
			else // Trái - Phải
			{
				//printf("\nMat can bang Trai - Phai");
				//printf("\nBuoc 1: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Left->Data, Root->Left->Data, Root->Left->Right->Data);
				QuayTrai(Root->Left);

				//printf("\nBuoc 2: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
				QuayPhai(Root);
			}
		}
		else // Lệch phải
		{
			int chieucaocontrai_2 = 0;
			int chieucaoconphai_2 = 0;

			if(Root->Right->Left != NULL)
				chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(Root->Right->Left);

			if(Root->Right->Right != NULL)
				chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(Root->Right->Right);

			if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
			{
				//printf("\nMat can bang Phai - Phai");
				//printf("\n=> Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
				QuayTrai(Root);
			}
			else // Phải - Trái
			{
				//printf("\nMat can bang Phai - Trai");
				//printf("\nBuoc 1: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Right->Data, Root->Right->Data, Root->Right->Left->Data);
				QuayPhai(Root->Right);

				//printf("\nBuoc 2: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
				QuayTrai(Root);
			}
		}
		return 1; // Node bị mất cân bằng và đã cân bằng xong
	}
	return 0; // Node không có mất cân bằng
}

// Trả về 1: Nếu tại Node có bị mất cân bằng và tiến hành cân bằng lại
// Trả về 0: Nếu tại Node không có mất cân bằng
int XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(NODE *&Root, NODE *&NodeDangXet)
{
	int chieucaocontrai = 0;
	int chieucaoconphai = 0;

	if(NodeDangXet->Left != NULL)
		//chieucaocontrai = TinhChieuCaoCay_DeQuy(ConMoi->Left);
			chieucaocontrai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left);

	if(NodeDangXet->Right != NULL)
		//chieucaoconphai = TinhChieuCaoCay_DeQuy(ConMoi->Right);
			chieucaoconphai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right);

	if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
	{
		//printf("\n=> Cay bi mat can bang tai Node %c", NodeDangXet->Data);

		NODE *ChaCuaNodeBiMatCanBang = NULL;

		if(NodeDangXet->Cha != NULL)
			ChaCuaNodeBiMatCanBang = NodeDangXet->Cha;

		if(chieucaocontrai > chieucaoconphai) // Lệch trái
		{
			int chieucaocontrai_2 = 0;
			int chieucaoconphai_2 = 0;

			if(NodeDangXet->Left->Left != NULL)
				//chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Left->Left);
					chieucaocontrai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left->Left);

			if(NodeDangXet->Left->Right != NULL)
				//chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Left->Right);
					chieucaoconphai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left->Right);

			if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
			{
				//printf("\nMat can bang Trai - Trai");
				//printf("\n=> Quay phai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Left->Data);
				QuayPhai(NodeDangXet);

				// Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
				if(NodeDangXet->Cha == NULL)
					Root = NodeDangXet;
			}
			else // Trái - Phải
			{
				//printf("\nMat can bang Trai - Phai");
				//printf("\nBuoc 1: Quay trai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Left->Data, NodeDangXet->Left->Data, NodeDangXet->Left->Right->Data);
				QuayTrai(NodeDangXet->Left);

				//printf("\nBuoc 2: Quay phai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Left->Data);
				QuayPhai(NodeDangXet);

				// Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
				if(NodeDangXet->Cha == NULL)
					Root = NodeDangXet;
			}
		}
		else // Lệch phải
		{
			int chieucaocontrai_2 = 0;
			int chieucaoconphai_2 = 0;

			if(NodeDangXet->Right->Left != NULL)
				//chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Right->Left);
					chieucaocontrai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right->Left);

			if(NodeDangXet->Right->Right != NULL)
				//chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Right->Right);
					chieucaoconphai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right->Right);

			if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
			{
				//printf("\nMat can bang Phai - Phai");
				//printf("\n=> Quay trai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Right->Data);
				QuayTrai(NodeDangXet);

				// Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
				if(NodeDangXet->Cha == NULL)
					Root = NodeDangXet;
			}
			else // Phải - Trái
			{
				//printf("\nMat can bang Phai - Trai");
				//printf("\nBuoc 1: Quay phai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Right->Data, NodeDangXet->Right->Data, NodeDangXet->Right->Left->Data);
				QuayPhai(NodeDangXet->Right);

				//printf("\nBuoc 2: Quay trai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Right->Data);
				QuayTrai(NodeDangXet);

				// Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
				if(NodeDangXet->Cha == NULL)
					Root = NodeDangXet;
			}
		}

		if(ChaCuaNodeBiMatCanBang != NULL)
		{
			if(NodeDangXet->Data > ChaCuaNodeBiMatCanBang->Data)
				ChaCuaNodeBiMatCanBang->Right = NodeDangXet;
			else if(NodeDangXet->Data < ChaCuaNodeBiMatCanBang->Data)
				ChaCuaNodeBiMatCanBang->Left = NodeDangXet;
		}

		return 1;
	}
	return 0;
}


// p là Node thế mạng sẽ xóa
int TimPhanTuTheMang_DeQuy(NODE *&Root, NODE *&p) 
{
	int ketqua;

	if(Root->Left != NULL)
		ketqua = TimPhanTuTheMang_DeQuy(Root->Left, p);
	else // Lúc này Root->Left == NULL => Root là NODE TRÁI nhất => đó là Node thế mạng
	{
		p->Data = Root->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
		p = Root; // Cho con trỏ p trỏ tới Node thế mạng (Root) để kết thúc hàm thì sẽ free(p) chính là free(Root)
		Root = Root->Right; // Mục đích: Giữ liên kết với các Node con của Node bị xóa - Vì Root đang là Node TRÁI nhất => sẽ không có con trái nữa chỉ có thể có con phải hoặc không có con => cứ cho trỏ tới con phải

		return 1;
	}

	if(ketqua == 1)
	{
		//printf("\nXet nguoc ve Node %c", Root->Data);
		XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);
		return 1; // Để tiếp tục xét lùi về cho các cha tiếp theo
	}
}

// trả về 1: xóa thành công
// trả về 0: xóa không thành công
int XoaNodeTrongCay_DeQuy(NODE *&Root, char x) // x là giá trị cần xóa ra khỏi cây
{
	int ketqua;

	// Điều kiện dừng
	if(Root == NULL)
		return 0; // kết thúc vì cây không có gì để xóa hoặc không tìm thấy Node cần xóa (giá trị cần xóa x không tồn tại trong cây)

	// Bước đệ quy
	if(x > Root->Data)
		ketqua = XoaNodeTrongCay_DeQuy(Root->Right, x);
	else if(x < Root->Data)
		ketqua = XoaNodeTrongCay_DeQuy(Root->Left, x);
	else // tìm thấy x trong cây tại Node Root => xóa
	{
		NODE *p = Root; // p là Node sẽ bị xóa

		// TH1: Node cần xóa là Node lá
		// TH2: Node cần xóa là Node có 1 con

		// Giữ liên kết với phần còn lại của Node bị xóa
		if(p->Left == NULL)
		{
			Root = p->Right;
		}
		else if(p->Right == NULL)
		{
			Root = p->Left;
		}
		else // p->Left != NULL && p->Right != NULL => TH3: Node cần xóa là Node có đủ 2 con
		{
			TimPhanTuTheMang_DeQuy(Root->Right, p); // TRÁI nhất của cây con phải

			//printf("\nXet nguoc ve Node %c", Root->Data);
			XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);
		}

		free(p); // giải phóng p

		return 1; // xóa thành công
	}

	if(ketqua == 1)
	{
		// Bắt đầu xét tính cân bằng của Root (Root chính là lần lượt cha của Node BỊ xóa)
		XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);

		//printf("\nXet nguoc ve Node %c", Root->Data);

		return 1; // để tiếp tục xét lùi về các Node trước đó mới có giá trị cho biến ketqua để mà đi so sánh
	}
}

// p là Node thế mạng sẽ xóa
void TimPhanTuTheMang_KhuDeQuy(NODE *&Root, NODE *&p) 
{
	// q là Node thế mạng cần xóa
	NODE *q = Root;
	NODE *k = p; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó. Khởi đầu thì k = p (Node cần xóa)

	while(q->Left != NULL)
	{
		k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
		q = q->Left;
	}

	// Sau vòng lặp thì q là Node trái nhất (Tức là nếu trỏ trái lần nữa thì sẽ là NULL => q là trái nhất)

	// Phải để đoạn lệnh này trước 2 đoạn lệnh sau để cập nhật liên kết cho xong rồi từ đó mới muốn cho trỏ đi đâu thì trỏ. Nếu không sẽ bị lỗi nếu để 2 đoạn lệnh dưới lên trên đoạn lệnh này
	if(q->Data > k->Data)
		k->Right = q->Right; // Lúc này q đã là trái nhất nên sẽ không có con trái nữa => chỉ có thể có con phải => cho giữ lại phần con phải
	else if(q->Data < k->Data)
		k->Left = q->Right; // Lúc này q đã là trái nhất nên sẽ không có con trái nữa => chỉ có thể có con phải => cho giữ lại phần con phải

	if(q->Right != NULL)
		q->Right->Cha = k;

	p->Data = q->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
	p = q; // Cho con trỏ p trỏ tới Node thế mạng (q) để kết thúc hàm thì sẽ free(p) chính là free(q)
}


// return 1: Xóa thành công
// return 0: Không xóa thành công (Node cần xóa không tồn tại trong cây)
int XoaNodeTrongCay_KhuDeQuy(NODE *&Root, char x) // x là giá trị cần xóa ra khỏi cây
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
				TimPhanTuTheMang_KhuDeQuy(q->Right, p); // Tìm phần tử thế mạng: TRÁI nhất của cây con phải
			}

			// 3 dòng code này phải để trước dòng lệnh free(p) vì nếu free(p) rồi thì đâu còn giá trị để trỏ tới cha mà truyền qua Node ChaCuaNodeBiXoa
			NODE *ChaCuaNodeBiXoa = NULL;
			if(p->Cha != NULL)
				ChaCuaNodeBiXoa = p->Cha;

			while(ChaCuaNodeBiXoa != NULL)
			{
				// Xét tính cân bằng của Node ChaCuaNodeBiXoa
				//printf("\nXet tinh can bang cua Node: %c", ChaCuaNodeBiXoa->Data);

				XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(Root, ChaCuaNodeBiXoa);

				ChaCuaNodeBiXoa = ChaCuaNodeBiXoa->Cha;
			}

			free(p); // giải phóng p
			return 1; // Xóa thành công - kết thúc hàm
		}
	}
	return 0; // Không xóa thành công (Node cần xóa không tồn tại trong cây)
}

int main()
{
	//NODE *Root;
	//INit(Root);

	//char a[] = "ABCDEFWZUTKNGHML";
	//char a[] = "FDNBEKUAHMTWGLZ";
	//int size = sizeof(a) - 1; // Phải trừ đi 1 để không lấy ký tự kết thúc chuỗi

	//for(int i = 0; i < size; ++i)
	//{
	//	//ThemNodeVaoCay_DeQuy(Root, a[i]);
	//	ThemNodeVaoCay_KhuDeQuy(Root, a[i]);
	//}

	//char x;
	//do{
	//	fflush(stdin); // giải phóng bộ nhớ đệm
	//	printf("\nNhap vao gia tri can xoa (Nhap '.' de ket thuc qua trinh xoa): ");
	//	scanf("%c", &x);

	//	if(x == '.')
	//		break;

	//	//int kq = ThemNodeVaoCay_DeQuy(Root, x);
	//	//int kq = ThemNodeVaoCay_KhuDeQuy(Root, x);
	//	//int kq = XoaNodeTrongCay_DeQuy(Root, x);
	//	int kq = XoaNodeTrongCay_KhuDeQuy(Root, x);

	//	if(kq == 0)
	//		printf("\nKhong xoa duoc do khong tim thay Node can xoa");
	//	else
	//	{
	//		printf("\nXoa thanh cong Node ra khoi cay");
	//		printf("\nCay sau khi xoa: ");
	//		NLR(Root);
	//	}
	//}while(x != '.');

	//GiaiPhongCay(Root);

	char a[] = "ABCDEFWZUTKNGHML";
	int size = sizeof(a) - 1; // Phải trừ đi 1 để không lấy ký tự kết thúc chuỗi

	/*NODE *Root1, *Root2;
	INit(Root1);
	INit(Root2);

	for(int i = 0; i < size; ++i)
	{
		ThemNodeVaoCay_DeQuy(Root1, a[i]);
		ThemNodeVaoCay_KhuDeQuy(Root2, a[i]);
	}

	printf("\nRoot1 = ");
	NLR(Root1);

	printf("\nRoot2 = ");
	NLR(Root2);*/

	char danhsachnodexoa[] = "KCMLWA";
	int size_danhsachnodexoa = sizeof(danhsachnodexoa) - 1;

	time_t start1 = clock();
	for(int k = 1; k <= 100000; ++k)
	{
		NODE *Root1;
		INit(Root1);
		for(int i = 0; i < size; ++i)
		{
			ThemNodeVaoCay_DeQuy(Root1, a[i]);
		}

		for(int i = 0; i < size_danhsachnodexoa; ++i)
		{
			XoaNodeTrongCay_DeQuy(Root1, danhsachnodexoa[i]);
		}
		GiaiPhongCay(Root1);
	}
	time_t end1 = clock();

	time_t start2 = clock();
	for(int k = 1; k <= 100000; ++k)
	{
		NODE *Root2;
		INit(Root2);
		for(int i = 0; i < size; ++i)
		{
			ThemNodeVaoCay_DeQuy(Root2, a[i]);
		}

		for(int i = 0; i < size_danhsachnodexoa; ++i)
		{
			XoaNodeTrongCay_KhuDeQuy(Root2, danhsachnodexoa[i]);
		}
		GiaiPhongCay(Root2);
	}
	time_t end2 = clock();

	printf("\nDe quy chat mat %lf giay", (double)(end1 - start1) / CLOCKS_PER_SEC);
	printf("\nKhu de quy chat mat %lf giay", (double)(end2 - start2) / CLOCKS_PER_SEC);

	getch();
	return 0;
}
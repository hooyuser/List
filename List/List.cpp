#include "List.h"


// 节点模板结构实现
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)  //将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
{
	ListNodePosi(T) x = new ListNode(e, pred, this);  //创建新节点
	pred->succ = x;
	pred = x;  //设置正向链接
	return x;  //返回新节点的位置
}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)  //将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
{
	ListNodePosi(T) x = new ListNode(e, this, succ);  //创建新节点
	succ->pred = x;
	succ = x;  //设置逆向链接
	return x;  //返回新节点的位置
}


// 列表模板类实现
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)  //列表内部方法：复制列表中自位置p起的n项
{  //p合法，且至少有n-1个真后继节点
	init();  //创建头、尾哨兵节点并做初始化
	while (n--)
	{
		insertAsLast(p->data);  //将起自p的n项依次作为末节点插入
		p = p->succ;
	}
}


template <typename T>
void List<T>::init()  //列表初始化，在创建列表对象时统一调用
{
	header = new ListNode<T>;  //创建头哨兵节点
	trailer = new ListNode<T>;  //创建尾哨兵节点
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	_size = 0;  //记录规模
}


template <typename T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	ListNodePosi(T) p = L.first();  //从首节点出发
	while (0 < r--)
		p = p->succ;
	copyNodes(p, n);
}


template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}


template <typename T>
T& List<T>::operator[] (Rank r) const  //重载下标操作符，以通过秩直接访问列表节点（复杂度O(n)）
{
	ListNodePosi(T) p = first();  //从首节点出发
	while (0 < r--)
		p = p->succ;  //顺数第r个节点即是
	return p->data;  //目标节点，返回其中所存元素
}


template <typename T>  //在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--)  //（0 <= n <= rank(p) < _size）对于p的最近的n个前驱，从右向左逐个比对，直至命中或范围越界
	{
		p = p->pred;
		if (e == p->data) return p;
	}
	return nullptr;  //p越出左边界意味着区间内不含e，查找失败，返回空指针
}


template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)  //e当作首节点插入
{
	_size++;
	return header->insertAsSucc(e);
}


template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)  //e当作末节点插入
{
	_size++;
	return trailer->insertAsPred(e);
}


template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)  //e当作p的后继插入（After）
{
	_size++;
	return p->insertAsSucc(e);
}


template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)  //e当作p的前驱插入（Before）
{
	_size++;
	return p->insertAsPred(e);
}


template <typename T>
T List<T>::remove(ListNodePosi(T) p)  //删除合法节点p，返回其数值
{
	T e = p->data;  //备份待删除节点的数值（假定T类型可直接赋值）
	p->pred->succ = p->succ;  //后继
	p->succ->pred = p->pred;  //前驱
	delete p;  //释放节点
	_size--;  //更新规模
	return e;  //返回备份的数值
}


template <typename T>  //清空列表
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)
		remove(header->succ); //反复删除首节点，直至列表变空
	return oldSize;
}



template <typename T>
int List<T>::deduplicate()  //剔除无序列表中的重复节点
{
	if (_size < 2)
		return 0;  //平凡列表自然无重复
	int oldSize = _size;  //记录原规模
	ListNodePosi(T) p = header;
	Rank r = 0;  //p从首节点开始
	while (trailer != (p = p->succ))  //依次直到末节点
	{
		ListNodePosi(T) q = find(p->data, r, p);  //在p的r个（真）前驱中查找雷同者
		q ? remove(q) : r++;  //若的确存在，则删除之；否则秩加一
	}  //assert: 循环过程中的任意时刻，p的所有前驱互不相同
	return oldSize - _size;  //列表规模变化量，即被删除元素总数
}


template <typename T>
int List<T>::uniquify()  //剔除有序列表中的重复节点
{
	if (_size < 2) return 0;  //平凡列表自然无重复
	int oldSize = _size;  //记录原规模
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;  //p为各区段起点，q为其后继
	while (trailer != (q = p->succ)) //反复考查紧邻的节点对(p, q)
	{
		if (p->data != q->data)
			p = q;  //若互异，则转向下一区段
		else remove(q);  //否则（雷同），删除后者
	}
	return oldSize - _size;  //列表规模变化量，即被删除元素总数

}


template <typename T> //在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
	// assert: 0 <= n <= rank(p) < _size
	do
	{
		p = p->pred; n--;  //从右向左

	} while ((-1 < n) && (e < p->data)); //逐个比较，直至命中或越界
	return p; //返回查找终止的位置

} //失败时，返回区间左边界的前驱（可能是header）


template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) //列表的选择排序算法：对起始于位置p的n个元素排序
{ //valid(p) && rank(p) + n <= size
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ; //待排序区间为(head, tail)
	while (1 < n)
	{ //在至少还剩两个节点之前，在待排序区间内
		ListNodePosi(T) max = selectMax(head->succ, n); //找出最大者（歧义时后者优先）
		insertB(tail, remove(max)); //将其移至无序区间末尾（作为有序区间新的首元素）
		tail = tail->pred; n--;
	}
}


template <typename T>
void List<T>::traverse(void(*visit) (T&))  //借助函数指针机制遍历
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}


template <typename T>  //元素类型
template <typename VST>  //操作器
void List<T>::traverse(VST& visit)  //借助函数对象机制遍历
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}
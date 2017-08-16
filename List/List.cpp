#include "List.h"

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) //将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
{
	ListNodePosi(T) x = new ListNode(e, pred, this); //创建新节点
	pred->succ = x;
	pred = x; //设置正向链接
	return x; //返回新节点的位置
}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) //将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
{
	ListNodePosi(T) x = new ListNode(e, this, succ); //创建新节点
	succ->pred = x;
	succ = x; //设置逆向链接
	return x; //返回新节点的位置
}


template <typename T>
void List<T>::init() //列表初始化，在创建列表对象时统一调用
{
	header = new ListNode<T>; //创建头哨兵节点
	trailer = new ListNode<T>; //创建尾哨兵节点
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	_size = 0; //记录规模
}


template <typename T>
T& List<T>::operator[] (Rank r) const //重载下标操作符，以通过秩直接访问列表节点（复杂度O(n)）
{
	ListNodePosi(T) p = first(); //从首节点出发
	while (0 < r--)
		p = p->succ; //顺数第r个节点即是
	return p->data; //目标节点，返回其中所存元素
}

template <typename T> //在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--) //（0 <= n <= rank(p) < _size）对于p的最近的n个前驱，从右向左逐个比对，直至命中或范围越界
	{
		p = p->pred;
		if (e == p->data) return p; 
	}	 
	return nullptr; //p越出左边界意味着区间内不含e，查找失败，返回空指针
} 
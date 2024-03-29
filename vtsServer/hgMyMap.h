#ifndef HG_MYMAP_H_
#define HG_MYMAP_H_

#include <QObject>
#include <QMap>
/**********************************************************************************************************************************/
/* 
    原理说明：
    mymap继承自QMap，重载了insert，clear，erase，find，begin，end，size等函数，对每一步操作的内部（包括迭代器）进行了加锁操作，用法与QMap一致。

    注意事项：
    为防止因为调用顺序问题引起的死锁问题，在一个线程内用到多个mymap容器的情况下，请按照下面的顺序进行上锁(可以用begin初始化迭代器进行上锁)：
    1.	m_mapTarget
    2.	m_mapAis
    3.	m_mapRadar
*/
/**********************************************************************************************************************************/


#include <map>

#if defined  _WIN32                                                         //Windows
#include <Windows.h>
#define MyMap_CLock_Mutex_t                 HANDLE
#define MyMap_CLock_Mutex_Init(_mutex)      (_mutex = CreateSemaphore(NULL,1,1,NULL))
#define MyMap_CLock_Mutex_Lock(_mutex)      (WaitForSingleObject(_mutex, INFINITE))
#define MyMap_CLock_Mutex_UnLock(_mutex)    (ReleaseSemaphore(_mutex,1,NULL))
#define MyMap_CLock_Mutex_Destroy(_mutex)   (CloseHandle(_mutex))
#define MyMap_Declar_Typename               typename
#define MyMap_Type_Typename

#elif defined __linux                                                       //Linux
#include <pthread.h>
#define MyMap_CLock_Mutex_t                 pthread_mutex_t
#define MyMap_CLock_Mutex_Init(_mutex)      (pthread_mutex_init(&_mutex, NULL))
#define MyMap_CLock_Mutex_Lock(_mutex)      (pthread_mutex_lock(&_mutex))
#define MyMap_CLock_Mutex_UnLock(_mutex)    (pthread_mutex_unlock(&_mutex))
#define MyMap_CLock_Mutex_Destroy(_mutex)   (pthread_mutex_destroy(&_mutex))
#define MyMap_Declar_Typename 
#define MyMap_Type_Typename                 typename
#endif

//************************************  
// 函数名称: PthreadSelf
// 函数说明： 获取线程ID内联函数
// 作 成 者：smallErLang  
// 作成日期：2016/04/22
// 返 回 值: unsigned int ：返回当前线程的ID
//************************************
inline unsigned int PthreadSelf()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif
}

template<class K, class V>
class mymap;

template<class K, class V>
class myiterator;

//lock
class CLock  
{  
public: 
	CLock(){MyMap_CLock_Mutex_Init(_mutex);}
	~CLock(){MyMap_CLock_Mutex_Destroy(_mutex);}

	void Lock() 
    {
        MyMap_CLock_Mutex_Lock(_mutex);
    }
	void UnLock() 
    {
        MyMap_CLock_Mutex_UnLock(_mutex);
    }


private:
	MyMap_CLock_Mutex_t _mutex;
};

//threadlockstats
/************************************************************************/
/* 
	1.CThreadLockStats是保存了当前所有线程调用_mutex_usr.Lock()和_mutex_usr.UnLock()
	的差值,记录同一线程中_mutex_usr的使用情况。
	2.类中可用函数为TryLock(),TryUnLock()，如果同一线程中_mutex_usr已经Lock，则TryLock()
	不再锁，只是将标识自增；如果同一线程中_mutex_usr的Lock次数为1同时需要释放锁的时候，
	调用TryUnLock会释放，不为1则将标识自减。
*/
/************************************************************************/
template<class K, class V>
class CThreadLockStats
{
private:
	CThreadLockStats();
	~CThreadLockStats();

	//************************************  
	// 函数名称: TryLock
	// 函数说明： 防止重锁
	//************************************
	void TryLock();

	//************************************  
	// 函数名称: TryUnLock
	// 函数说明： 与TryLock对应的释放锁
	//************************************
	void TryUnLock();

    void UnLockAll();

private:
	CLock _mutex_usr;

	CLock _mutex_stats;

	std::map<unsigned int, int>* _thread_lock_stats;  //<线程ID,上锁次数>

	friend mymap<K, V>;

	friend myiterator<K, V>;
};

template<class K, class V>
void CThreadLockStats<K, V>::UnLockAll()
{
    bool _isneedusrunlock = false;
    unsigned int _thread_id = PthreadSelf();

    _mutex_stats.Lock();

    if(_thread_lock_stats)
    {
        MyMap_Type_Typename std::map<unsigned int, int>::iterator _finditr = _thread_lock_stats->find(_thread_id);

        if(_finditr != _thread_lock_stats->end())
        {

            if(_finditr->second >= 1)
            {
                _isneedusrunlock = true;
                _finditr->second = 0;
            }
        }
    }

    _mutex_stats.UnLock();

    if(_isneedusrunlock)
    {
        _mutex_usr.UnLock();
    }
}

template<class K, class V>
void CThreadLockStats<K, V>::TryUnLock()
{
	bool _isneedusrunlock = false;
	unsigned int _thread_id = PthreadSelf();

	_mutex_stats.Lock();

	if(_thread_lock_stats)
    {
		MyMap_Type_Typename std::map<unsigned int, int>::iterator _finditr = _thread_lock_stats->find(_thread_id);

		if(_finditr != _thread_lock_stats->end())
        {

			if(_finditr->second == 1)
            {
				_isneedusrunlock = true;
			}

			_finditr->second -= 1;

		}
        else
        {

			int _new_lock_counts = 0;

			_thread_lock_stats->insert(MyMap_Type_Typename std::map<unsigned int, int>::value_type(_thread_id, _new_lock_counts));
		}
	}

	_mutex_stats.UnLock();

	if(_isneedusrunlock)
    {
        _mutex_usr.UnLock();
        //vtsError << "@@@@@@ " <<GetCurrentThreadId() << " " << "unlock";
	}
}

template<class K, class V>
void CThreadLockStats<K, V>::TryLock()
{
	bool _isneedusrlock = false;
	unsigned int _thread_id = PthreadSelf();

	_mutex_stats.Lock();

	if(_thread_lock_stats)
    {

		MyMap_Type_Typename std::map<unsigned int, int>::iterator _finditr = _thread_lock_stats->find(_thread_id);

		if(_finditr != _thread_lock_stats->end())
        {

			if(_finditr->second <= 0)
            {

				_finditr->second = 0;

				_isneedusrlock = true;
			}

			_finditr->second += 1;
		}
        else
        {

			int _new_lock_counts = 1;

			_thread_lock_stats->insert(MyMap_Type_Typename std::map<unsigned int, int>::value_type(_thread_id, _new_lock_counts));

			_isneedusrlock = true;
		}
	}

	_mutex_stats.UnLock();

	//将_mutex_usr.Lock放置于_mutex_stats释放后，防止死锁
	//函数中非成对出现的锁加上其他锁在多线程调用时一定会出现死锁
	if(_isneedusrlock)
    {
        //vtsError << "@@@@@@ " <<GetCurrentThreadId() << " "<< "lock";
		_mutex_usr.Lock();
	}
}

template<class K, class V>
CThreadLockStats<K, V>::~CThreadLockStats()
{
	_mutex_stats.Lock();

	delete _thread_lock_stats;

	_thread_lock_stats = NULL;

	_mutex_stats.UnLock();
}

template<class K, class V>
CThreadLockStats<K, V>::CThreadLockStats()
{
	_thread_lock_stats = new std::map<unsigned int, int>;
}

//myiterator:迭代器继承标准迭代器,减少运算符和一些函数的重载
template<class K, class V>
class myiterator: public MyMap_Type_Typename QMap<K, V>::iterator
{
public:
	myiterator();
	//************************************  
	// 函数名称: myiterator
	// 函数说明： 重载拷贝构造，方便拷贝时就Lock,释放时就UnLock；
	//************************************
	myiterator(const myiterator& val_);
	~myiterator();

	//************************************  
	// 函数名称: operator=
	// 函数说明： 赋值运算会隐藏父类赋值函数，不会继承，需要重载
	//************************************
	myiterator& operator=(const myiterator& val_);

private:
	myiterator& operator=(const MyMap_Declar_Typename QMap<K, V>::iterator& val_);

private:
	CThreadLockStats<K, V>* _mutex_stats;

	friend mymap<K, V>;
};

template<class K, class V>
myiterator<K, V>& myiterator<K, V>::operator=( const myiterator<K, V>& val_ )
{
	_mutex_stats = val_._mutex_stats;

	if(_mutex_stats)
    {
		_mutex_stats->TryLock();
	}

	this->QMap<K, V>::iterator::operator=(val_);

	return *this;
}

template<class K, class V>
myiterator<K, V>::myiterator( const myiterator& val_ )
{
	_mutex_stats = val_._mutex_stats;

	if(_mutex_stats)
    {

		_mutex_stats->TryLock();
	}

	this->QMap<K, V>::iterator::operator=(val_);
}

template<class K, class V>
myiterator<K, V>& myiterator<K, V>::operator=( const MyMap_Declar_Typename QMap<K, V>::iterator& val_ )
{
	this->QMap<K, V>::iterator::operator=(val_);

	return *this;
}

//************************************  
// 函数名称: ~myiterator
// 函数说明： 迭代器赋值和拷贝构造时Lock，析构时需要释放锁
//************************************
template<class K, class V>
myiterator<K, V>::~myiterator()
{
	if(_mutex_stats)
    {
		_mutex_stats->TryUnLock();
	}
	_mutex_stats = NULL;
}

template<class K, class V>
myiterator<K, V>::myiterator()
{
	_mutex_stats = NULL;
}

//mymap
/************************************************************************/
/* 
	由于iterator默认构造函数没有TryLock，所以在返回该类型临时变量时需要TryLock一次，
临时变量析构时TryUnLock一次；将返回的值进行拷贝构造或者拷贝赋值会TryLock一次，使用
完后析构TryUnLock一次。达到成对锁和释放锁的目的。
*/
/************************************************************************/
template<class K, class V>
class mymap: private QMap<K, V>
{
public:
	mymap();
	mymap(const mymap& val_);
	~mymap();

	mymap& operator=(const mymap& val_);

	typedef MyMap_Declar_Typename myiterator<K, V> iterator;

	void insert(const K& key_, const V& val_);
    void clear();
	void erase(const K& key_);
	//void erase_s(iterator& itr_);
    iterator erase(iterator& itr_);
	iterator find(const K& key_);

	iterator begin();
	iterator end();

	unsigned int size();

    void UnLockAll(); 

private:
	CThreadLockStats<K, V> _mutex_stats;
};

template<class K, class V>
void mymap<K, V>::UnLockAll()
{
    _mutex_stats.UnLockAll();
}

template<class K, class V>
void mymap<K, V>::clear()
{
    _mutex_stats.TryLock();

    this->QMap::clear();

    _mutex_stats.TryUnLock();
}

template<class K, class V>
unsigned int mymap<K, V>::size()
{
	unsigned int _size = 0;

	_mutex_stats.TryLock();

	_size = this->QMap::size();

	_mutex_stats.TryUnLock();

	return _size;
}

template<class K, class V>
typename mymap<K, V>::iterator mymap<K, V>::end()
{
	mymap<K, V>::iterator _ret;

	_ret._mutex_stats = &_mutex_stats;

	_mutex_stats.TryLock();

	_ret = this->QMap::end();

	return _ret;
}

template<class K, class V>
typename mymap<K, V>::iterator mymap<K, V>::begin()
{
	mymap<K, V>::iterator _ret;

	_ret._mutex_stats = &_mutex_stats;

	_mutex_stats.TryLock();

	_ret = this->QMap::begin();

	return _ret;
}

template<class K, class V>
typename mymap<K, V>::iterator mymap<K, V>::find( const K& key_ )
{
	mymap<K, V>::iterator _ret;

	_ret._mutex_stats = &_mutex_stats;

	_mutex_stats.TryLock();

	_ret = this->QMap::find(key_);

	return _ret;
}

/*template<class K, class V>
void mymap::map<K, V>::erase_s( typename mymap::map<K, V>::iterator& itr_ )
{
    _mutex_stats.TryLock();

	this->erase(itr_);

	_mutex_stats.TryUnLock();
}*/

template<class K, class V>
void mymap<K, V>::erase( const K& key_ )
{
	_mutex_stats.TryLock();

	this->QMap::erase(key_);

	return ;
}


template<class K, class V>
typename mymap<K, V>::iterator mymap<K, V>::erase(iterator& itr_)
{
    mymap<K, V>::iterator _ret;

    _ret._mutex_stats = &_mutex_stats;

    _mutex_stats.TryLock();

    _ret = this->QMap::erase(itr_);

    return _ret;
}

template<class K, class V>
void mymap<K, V>::insert( const K& key_, const V& val_ )
{
	_mutex_stats.TryLock();

	this->QMap::insert(key_, val_);

	_mutex_stats.TryUnLock();

	return ;
}	

template<class K, class V>
mymap<K, V>& mymap<K, V>::operator=( const mymap& val_ )
{
	val_._mutex_stats.TryLock();

	this->std::map<K, V>::operator =(val_);

	val_._mutex_stats.TryUnLock();

	return *this;
}

template<class K, class V>
mymap<K, V>::~mymap()
{

}

template<class K, class V>
mymap<K, V>::mymap( const mymap<K, V>& val_ )
{
	val_._mutex_stats.TryLock();

	this->std::map<K, V>::operator =(val_);

	val_._mutex_stats.TryUnLock();
}

template<class K, class V>
mymap<K, V>::mymap()
{

}

#endif //HG_MYMAP_H_
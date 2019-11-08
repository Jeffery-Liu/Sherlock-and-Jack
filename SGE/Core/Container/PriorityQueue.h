#ifndef INCLUDED_PRIORITYQUEUE_H
#define INCLUDED_PRIORITYQUEUE_H

//====================================================================================================
// Filename:	PriorityQueue.h
// Description:	A collection of items where each item is assigned a priority. 
//				Items having higher priority are processed before items with lower priority.
//				If there is more than one item with the same priority, they are processed in the
//				order they are added to the queue (FIFO).
//====================================================================================================

#include <vector>

template<typename T>
class PriorityQueue
{
public:
	PriorityQueue()
	{
	}

	~PriorityQueue()
	{
		mList.clear();
	}

	void Clear()
	{
		mList.clear();
	}

	bool Empty() const
	{
		return (mList.size() == 0);
	}

	void Enqueue(T data, int priority)
	{
		bool enqueued = false;

		if (mList.size() > 0)
		{
			for (auto it = mList.begin(); it != mList.end(); ++it)
			{
				if (priority >= it->second)
				{
					mList.insert(it, PriorityPair(data, priority));
					enqueued = true;
					break;
				}
			}
		}

		if (enqueued == false)
		{
			mList.insert(mList.end(), PriorityPair(data, priority));
		}
	}

	T Dequeue()
	{
		if (mList.size() > 0)
		{
			PriorityPair data = mList.back();
			mList.pop_back();
			return data.first;
		}
		return T();
	}

private:
	typedef std::pair<T, int> PriorityPair;
	std::vector<PriorityPair> mList;
};

#endif // #ifndef INCLUDED_PRIORITYQUEUE_H
#ifndef OPERATIONSTACK
#define OPERATIONSTACK

#include <deque>
#include <QtOpenGL>
#include <vector>
#include <exception>
#include <stdexcept>
#include "treeinfo.h"

using namespace std;


struct TreeNode
{
	QString name;//»­²¼±àºÅ
	TreeInfo info;
	QVector3D position;
	QVector3D angle;
	QVector3D scale;
};

struct ActionNode
{
	int operation;
	vector<TreeNode> changedTrees;
	int count()
	{
		return changedTrees.size();
	}
	static const int ADD = 1;
	static const int REMOVE = 2;
	static const int ALTER = 3;
};

class OperationStack
{
private:
	deque<ActionNode> undo;
	deque<ActionNode> redo;
	const int SIZE;
public:
	void PushToUndo(ActionNode x)
	{
		while (undo.size() >= SIZE)
		{
			undo.pop_front();
		}
		undo.push_back(x);
	}

	ActionNode PopFromUndo()
	{
		if (undo.empty())
		{
			throw range_error("Stack is Empty£¡");
		}
		ActionNode x = undo.back();
		undo.pop_back();
		redo.push_back(x);
		return x;
	}

	void PushToRedo(ActionNode x)
	{
		if (redo.size() >= SIZE)
		{
			redo.erase(redo.begin(), redo.begin() + redo.size() - SIZE);
		}
		redo.push_back(x);
	}

	ActionNode PopFromRedo()
	{
		if (redo.empty())
		{
			throw range_error("Stack is Empty£¡");
		}
		ActionNode x = redo.back();
		redo.pop_back();
		undo.pop_back();
		return x;
	}

	void ClearRedo()
	{
		redo.clear();
	}
public:
	OperationStack(int size) :SIZE(size){}
};

#endif
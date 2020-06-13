#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QMimeData>
#include <QIODevice>
#include <QDataStream>

class TreeNode
{
public:
    TreeNode(const QString& text = "") :mText(text) {}
    ~TreeNode(){}

    QString mText;

    TreeNode* mParentNode;                  //父结点
    QList<TreeNode*> mChildNodes;			//子结点
};

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(QObject* parent = nullptr);
    ~TreeModel();
    void SetRootNode(TreeNode *node);
    bool AddTreeNode(TreeNode* pNode);																			//添加一个子节点
    int TreeNodeHaveEqualInfo(TreeNode* parentNode, TreeNode* pAddChildNode);								//判断待加入节点，在父节点中是否有相同信息
    TreeNode* FindParentNode(TreeNode* pNode, TreeNode* childNode);									//根据给定的字节点，再根节点中，寻找其父节点

    //结点所在的位置，和其父结点
    TreeNode* NodeFromIndex(const QModelIndex &index) const;

    //实现 QAbstractItemModel的类的成员函数
    QModelIndex index(int row, int column,
        const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        Qt::ItemFlags flag = QAbstractItemModel::flags(index);
        return flag | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;				//允许Model拖动，这个很重要
    }

    QMimeData*  mimeData(const QModelIndexList &indexes) const
    {
        QMimeData* mimeD = QAbstractItemModel::mimeData(indexes);				//先获取原始的mimeData;

        if (indexes.size() > 0)
        {
            QModelIndex index = indexes.at(0);

            TreeModel* node = static_cast<TreeModel*>(index.internalPointer());
            QByteArray encoded;
            QDataStream stream(&encoded, QIODevice::WriteOnly);
            stream << qint64(node);
            mimeD->setData("Node/NodePtr", encoded);							//将自己需要的数据 存入到MimeData中
        }
        else
            mimeD->setData("Node/NodePtr", "NULL");

        return mimeD;
        //mimeD->setData()
    }

public:
    TreeNode* mRootNode;							//树的根结点
};

#endif // TREEMODEL_H

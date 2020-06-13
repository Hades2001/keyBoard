#include "treemodel.h"

TreeModel::TreeModel(QObject* parent) : QAbstractItemModel(parent)
{
    this->mRootNode = nullptr;
    //构造一个根节点，在Qt中根节点的父节点为空，默认不显示，构造一个空节点充当父节点

    mRootNode = new TreeNode();
    mRootNode->mParentNode = nullptr;
}

TreeModel::~TreeModel()
{
    //将设备的根结点才此位置析构
    if (mRootNode)
        delete mRootNode;
    mRootNode = nullptr;
}

//设置设备树的根结点
void TreeModel::SetRootNode(TreeNode *node)
{
    //要更新model数据时，先调用beginResetModel,结束时调用endResetModel，所有绑定在Model上的视图都会更新
    this->beginResetModel();
    if (mRootNode)
    {
        delete mRootNode;
        mRootNode = nullptr;
    }
    mRootNode = node;
    endResetModel();
}

//往某个父节点，添加一个子节点，如果parentNode为空，添加到父节点下
bool TreeModel::AddTreeNode(TreeNode* pNode)
{
    if (this->TreeNodeHaveEqualInfo(mRootNode, pNode) > 0)			//如果待加入节点，在根节点中有相同Ip，不允许加入
    {
        //TODO MSG
        delete pNode;												//不加入的节点 析构掉。
        return true;
    }
    this->beginResetModel();
    do
    {
        if (!pNode->mParentNode)						//parentNode为空，直接加载在根节点下
        {
            mRootNode->mChildNodes.append(pNode);
            pNode->mParentNode = mRootNode;
            break;
        }
    } while (0);

    //如果parentNode在现有的树体系中，加入现有树体系，如果不在，加入根节点中
    /*TreeNode* pNode = FindParentNode(mRootNode, pNode->mParentNode);
    if (!pNode)
    {
        mRootNode->mChildNodes.append(pNode);
        pNode->mParentNode = mRootNode;
        return true;
    }*/

    this->endResetModel();
    return true;
}

//pNode 为要查找节点， childNode 为被查找节点，返回被查找节点的父节点,pNode和childNode之间有层级关系
TreeNode* TreeModel::FindParentNode(TreeNode* pNode, TreeNode* childNode)
{
    Q_UNUSED(pNode);
    Q_UNUSED(childNode);
    //if (!pNode)
    //	return NULL;

    //if (pNode->mChildNodes.indexOf(childNode))								//如果子节点在所在的父节点，返回父节点
    //	return pNode;
    //for (int i = 0; i < pNode->mChildNodes.count(); i++)
    //{
    //	return FindParentNode(pNode->mChildNodes.at(i), childNode);
    //}
    return nullptr;
}

int TreeModel::TreeNodeHaveEqualInfo(TreeNode* parentNode, TreeNode* pAddChildNode)
{
    Q_UNUSED(parentNode);
    Q_UNUSED(pAddChildNode);
    /*for (int i = 0; i < parentNode->mChildNodes.size(); i++)
    {
        if (parentNode->mChildNodes.at(i)->mDeviceInfo.mDevIp != pAddChildNode->mDeviceInfo.mDevIp)
            continue;
        else
            return 1;
    }
    */
    return 0;
}

//根据QModelIndex，返回指向其父结点的指针
TreeNode* TreeModel::NodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid())				//如果是有效结点
        return static_cast<TreeNode*>(index.internalPointer());
    else
        return mRootNode;
}

//重载实现的QAbstractItemModel类的函数，基类中带const的函数，重载时也要是const
//index函数，根据行，列，返回一个父结点为parent的元素
QModelIndex TreeModel::index(int row, int column,
    const QModelIndex &parent) const
{
    //如果参数条件不满足，返回为空
    if (!mRootNode || row < 0 || column < 0)
        return QModelIndex();

    TreeNode* parentNode = NodeFromIndex(parent);		//获取指向此结点的指针
    if (!parentNode)					//如果没有父结点
        return QModelIndex();

    TreeNode* rowNode = parentNode->mChildNodes.at(row);
    if (!rowNode)
        return QModelIndex();
    return this->createIndex(row, column, rowNode);			//创建一个QModelIndex,参数3为结点指向数据指针
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    TreeNode *node = NodeFromIndex(child);
    if (!node)
        return QModelIndex();
    TreeNode *parentNode = node->mParentNode;
    if (!parentNode)
        return QModelIndex();
    TreeNode *grandparentNode = parentNode->mParentNode;
    if (!grandparentNode)
        return QModelIndex();

    int row = grandparentNode->mChildNodes.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

//返回给定父结点下，行的个数
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    TreeNode* parentNode = NodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->mChildNodes.count();				//返回父结点中子结点个数
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;											//返回列数，此处为1列
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{

    //qDebug() << "TreeModel::data";
    switch (role)
    {
    case Qt::DisplayRole:										//显示汉字
    {
        TreeNode *node = NodeFromIndex(index);
        if (!node)
            return QVariant();
        if (index.column() == 0)
            return node->mText;				//显示设备的Ip
    }
    break;
    case Qt::DecorationRole:									//图标相关的role
    {
        //qDebug() << "Qt::DecorationRole";
        //QPixmap Icon = QPixmap("D:/QtProject/QtGuiApplication1/release/33.png");		//在树上画图标
        QVariant var;
        //var.setValue(Icon);
        return var;
    }
    //break;
    /*case Qt::UserRole:
    {
        TreeNode *node = NodeFromIndex(index);

        QVariant var;
        var.setValue<TreeNode*>(node);
        return var;
    }
    break;*/
    default:
        break;
    }


    return QVariant();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
        {
            return tr("Txt");
        }

    }
    return QVariant();
}

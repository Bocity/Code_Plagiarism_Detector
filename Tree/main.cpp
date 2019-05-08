#include "TextToTree.h"
#include "Tree.h"
#include "mynode.h"
#include <bits/stdc++.h>
using namespace std;
int TD[MAXNODE][MAXNODE];

int Zss(Tree &tree1, Tree &tree2);
int treedist(vector<int> left1, vector<int> left2, int i, int j, Tree tree1, Tree tree2);
vector<Node> test2(int &root);
vector<Node> test1(int &root);
map<string, int> costmap;
int Default;
void test();
void mmapini();
void getmodifycost(Tree tree1, Tree tree2);
double fun(char file1[], char file2[]);
void getPathAndSrcp(char tufile[], char path[], char outfile[], char srcp[]);

int main(int argc, char **argv) 
{
    char *file1 = argv[1]; 
    char *file2 = argv[2]; 
    if (argc < 2) {
        printf("lack  parameters  ,please check！！！   \n");
        return -1;
    }
    mmapini();

    return fun(file1, file2);
}

double fun(char file1[], char file2[]) {
    vector<Node> nodeL1; 
    vector<Node> nodeL2; 
    int root1, root2;
    char path1[100], outfile1[100], srcp1[100];
    char path2[100], outfile2[100], srcp2[100];
    getPathAndSrcp(file1, path1, outfile1, srcp1);
    getPathAndSrcp(file2, path2, outfile2, srcp2);
    nodeL1 = TextToTree().convert(root1, path1, outfile1, srcp1);
    nodeL2 = TextToTree().convert(root2, path2, outfile2, srcp2);
    freopen("/dev/tty", "w", stdout);
    freopen("/dev/tty", "r", stdin);
    if (nodeL1.size() == 0 || nodeL2.size() == 0) {
        printf("There is no node,Please check the input path or srcp file name!!!\n");
        printf("nodeL1.size()=%d  nodeL2.size()=%d\n", nodeL1.size(), nodeL2.size());
        return -1;
    }
    Tree tree1(nodeL1, root1), tree2(nodeL2, root2);
    int distance = Zss(tree1, tree2);
    double treesim = 1.0 * ((tree1.nodelist.size() + tree2.nodelist.size()) * Default - distance) /
                     ((tree1.nodelist.size() + tree2.nodelist.size()) * Default);
    printf("%s和%s的带权最小编辑树距离为：%d 相似度量化值为：%.3f%%\n", path1, path2, distance, treesim * 100);
    return treesim * 100;
}

void getPathAndSrcp(char tufile[], char path[], char outfile[], char srcp[]) {
    strcpy(path, tufile); /// path
    char tmp[100];
    // cout<<path<<endl;
    int idx = -1;
    int len = strlen(path);
    for (int i = 0; i < len; i++)
        if (path[i] == '/') idx = i;
    //    cout<<idx<<" "<<len<<endl;
    int j = 0;
    for (int i = idx + 1; i < len; i++) {
        //     cout<<i<<"   ";
        tmp[j++] = path[i];
    }
    //   cout<<j<<endl;
    tmp[j] = '\0'; ///获取文件名
                   // cout<<endl<<tmp<<endl;
    len = strlen(tmp);
    int pos = 0, i;
    while (tmp[pos] != '.' && pos < len) pos++;
    for (i = 0; i < pos; i++) srcp[i] = tmp[i];
    srcp[i] = '\0';        /// srcp;
    strcpy(outfile, srcp); /// outfile
    strcat(outfile, ".txt");

    // cout<<path<<"---"<<outfile<<"---"<<srcp<<endl;
}

void printfinfo(Tree tree) {
    cout << "==========节点信息=============\n nodename index leftmost child_number\n";
    for (int i = 0; i < tree.nodelist.size(); i++)
        // if(tree)
        cout << tree.nodelist[i].nodename << ' ' << tree.nodelist[i].index << ' ' << tree.nodelist[i].leftmost << ' '
             << tree.nodelist[i].edgelist.size() << endl;

    cout << "\n=============最左节点信息==============\n";
    for (int i = 0; i < tree.left.size(); i++) cout << tree.left[i] << ' ';

    cout << "\n=============keyroots点信息==============\n";
    for (int i = 0; i < tree.keyroots.size(); i++) cout << tree.keyroots[i] << ' ';

    cout << "\n============提取的节点名称信息==============\n";
    for (int i = 0; i < tree.labels.size(); i++) cout << tree.labels[i] << ' ';

    cout << "\n\n\n";
    return;
}
int Zss(Tree &tree1, Tree &tree2) {
    //   cout<<"debug :come in Zhang-shasha \n";
    tree1.getindex();
    // cout<<"debug : tree1 getindex is over \n";
    // return 0;
    //  cout<<"debug :finish tree1 getindex \n";
    tree1.getleftarr();
    //   cout<<"debug :finish tree1 getleftarr \n";
    tree1.getkeyroots();
    tree1.traverse();
    //  cout<<"debug :finish tree1 initial \n";

    tree2.getindex();
    tree2.getleftarr();
    tree2.getkeyroots();
    tree2.traverse();
    //  cout<<"debug :initial is over \n";
    // printfinfo(tree1);
    //  printfinfo(tree2);

    vector<int> left1 = tree1.left;
    vector<int> keyroots1 = tree1.keyroots;

    vector<int> left2 = tree2.left;
    vector<int> keyroots2 = tree2.keyroots;
    // cout<<keyroots1.size()<<" "<<keyroots2.size()<<endl;
    // space complexity of the algorithm

    getmodifycost(tree1, tree2);

    //  cout<<"getmodifycost is over!!!!\n";
    // solve subproblems
    for (int i1 = 1; i1 < keyroots1.size() + 1; i1++) 
    {
        for (int j1 = 1; j1 < keyroots2.size() + 1; j1++) 
        {
            int i = keyroots1[i1 - 1];
            int j = keyroots2[j1 - 1];
            TD[i][j] = treedist(left1, left2, i, j, tree1, tree2);
            // cout<<i<<" "<<j<<" "<<TD[i][j]<<endl;
        }
    }
    return TD[left1.size()][left2.size()];
}

int forestdist[MAXNODE][MAXNODE]; ///???????????????????
int delcost1[MAXNODE], relcost[MAXNODE][MAXNODE];
int inscost2[MAXNODE];

void getmodifycost(Tree tree1, Tree tree2) {
    int Delete = 1;
    int Insert = 1;
    int Relabel = 1;
    int len1 = tree1.labels.size(), len2 = tree2.labels.size();
    map<string, int>::iterator ite;
    int cost, cost1, cost2;
    for (int i = 0; i < len1; i++) {
        ite = costmap.find(tree1.labels[i]);
        cost = (ite == costmap.end() ? Default : costmap[tree1.labels[i]]);
        delcost1[i] = Delete * cost;
    }
    for (int i = 0; i < len2; i++) {
        ite = costmap.find(tree2.labels[i]);
        cost = (ite == costmap.end() ?: costmap[tree2.labels[i]]);
        inscost2[i] = Insert * cost;
    }
    for (int i = 0; i < len1; i++) {
        ite = costmap.find(tree1.labels[i]);
        cost1 = (ite == costmap.end() ? Default : costmap[tree1.labels[i]]);
        for (int j = 0; j < len2; j++) {
            ite = costmap.find(tree2.labels[j]);
            cost2 = (ite == costmap.end() ? Default : costmap[tree2.labels[j]]);
            relcost[i][j] = max(cost1, cost2) * Relabel;
        }
    }
}

int treedist(vector<int> left1, vector<int> left2, int i, int j, Tree tree1, Tree tree2) {
    //   int **forestdist = new int*[i + 1];
    //   for(int k=0;k<i+1;k++)
    //      forestdist[k]=new int[j + 1];

    // costs of the three atomic operations

    forestdist[0][0] = 0;
    for (int i1 = left1[i - 1]; i1 <= i; i1++) {
        forestdist[i1][0] = forestdist[i1 - 1][0] + delcost1[i1];
    }
    for (int j1 = left2[j - 1]; j1 <= j; j1++) {
        forestdist[0][j1] = forestdist[0][j1 - 1] + inscost2[j1];
    }
    for (int i1 = left1[i - 1]; i1 <= i; i1++) {
        for (int j1 = left2[j - 1]; j1 <= j; j1++) {
            int i_temp = (left1[i - 1] > i1 - 1) ? 0 : i1 - 1;
            int j_temp = (left2[j - 1] > j1 - 1) ? 0 : j1 - 1;
            if ((left1[i1 - 1] == left1[i - 1]) && (left2[j1 - 1] == left2[j - 1])) /// i在i1的左子树上
            {
                int Cost = (tree1.labels[i1 - 1] == tree2.labels[j1 - 1]) ? 0 : relcost[i1][j1];
                forestdist[i1][j1] = min(min(forestdist[i_temp][j1] + delcost1[i1], forestdist[i1][j_temp] + inscost2[j1]), forestdist[i_temp][j_temp] + Cost);
                TD[i1][j1] = forestdist[i1][j1];
                // if(TD[i1][j1]!=0)
                //     printf("debug: TD[%d][%d]=%d\n",i1,j1,TD[i1][j1]);
                // println(i1 + " " + j1);
            } else 
            {
                int i1_temp = left1[i1 - 1] - 1;
                int j1_temp = left2[j1 - 1] - 1;

                int i_temp2 = (left1[i - 1] > i1_temp) ? 0 : i1_temp;
                int j_temp2 = (left2[j - 1] > j1_temp) ? 0 : j1_temp;

                forestdist[i1][j1] = min(min(forestdist[i_temp][j1] + delcost1[i1], forestdist[i1][j_temp] + inscost2[j1]), forestdist[i_temp2][j_temp2] + TD[i1][j1]);
            }
        }
    }
    return forestdist[i][j];
}

void mmapini() {
    costmap.clear();
    string strfun = "function_decl";
    string strbrc = "branch";
    string strslc = "selection";
    string strgtx = "goto_expr";
    Default = 2;
    costmap[strfun] = 5;
    costmap[strbrc] = 5;
    costmap[strslc] = 5;
    costmap[strgtx] = 5;
}

void test() {
    vector<Node> nodeL1; 
    vector<Node> nodeL2; 
    int root1, root2;

    nodeL1 = test1(root1), nodeL2 = test2(root2);

    Tree tree1(nodeL1, root1), tree2(nodeL2, root2);
    int distance = Zss(tree1, tree2);
    printf("tree1和tree2的最小编辑树距离为：%d", distance);
}

vector<Node> test1(int &root) {
    root = 0;
    vector<Edge> edge;
    vector<Node> node;
    /// 0
    edge.clear();
    edge.push_back(Edge(1));
    edge.push_back(Edge(2));
    node.push_back(Node(edge, "f"));

    /// 1
    edge.clear();
    edge.push_back(Edge(3));
    edge.push_back(Edge(4));
    node.push_back(Node(edge, "d"));

    /// 2
    edge.clear();
    node.push_back(Node(edge, "e"));

    /// 3
    edge.clear();
    node.push_back(Node(edge, "a"));

    /// 4
    edge.clear();
    edge.push_back(Edge(5));
    node.push_back(Node(edge, "c"));

    /// 5
    edge.clear();
    node.push_back(Node(edge, "b"));
    return node;
}

vector<Node> test2(int &root) {
    root = 0;
    vector<Edge> edge;
    vector<Node> node;
    /// 0
    edge.clear();
    edge.push_back(Edge(1));
    edge.push_back(Edge(2));
    node.push_back(Node(edge, "f"));

    /// 1
    edge.clear();
    edge.push_back(Edge(3));
    node.push_back(Node(edge, "c"));

    /// 2
    edge.clear();
    node.push_back(Node(edge, "e"));

    /// 3
    edge.clear();
    edge.push_back(Edge(4));
    edge.push_back(Edge(5));
    node.push_back(Node(edge, "d"));

    /// 4
    edge.clear();
    node.push_back(Node(edge, "a"));

    /// 5
    edge.clear();
    node.push_back(Node(edge, "b"));
    return node;
}
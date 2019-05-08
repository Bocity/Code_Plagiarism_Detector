#include "TextToTree.h"
char FILENAME[100];
int FILELEN;
TextToTree::TextToTree() {}

TextToTree::~TextToTree() {}
int has[MAXN];
int useful_mark[MAXN];
vector<string> str;
vector<string> nomStr;
vector<Node> nodelist;

const int STYPES_SIZE = 3;
string simpleTypes[STYPES_SIZE] = {"integer_type", "real_type", "void_type"};

string trim(char tmp[]) {
    int len = strlen(tmp), i = 0, pnt = 0;
    while (tmp[i] == ' ' && i < len) i++;
    for (; i < len; i++) {
        if (i >= 1 && (tmp[i - 1] == ' ' || tmp[i - 1] == ':') && tmp[i] == ' ') continue;
        if (i + 1 < len && tmp[i] == ' ' && tmp[i + 1] == ':') continue;
        tmp[pnt++] = tmp[i];
    }
    tmp[pnt] = '\0';
    string ss(tmp);
    return ss;
}

void getstr() {
    char tmp[200];
    fgets(tmp, 200, stdin);

    if (tmp[strlen(tmp) - 1] == '\n') tmp[strlen(tmp) - 1] = '\0';
    string last = trim(tmp);
    ;
    while (fgets(tmp, 200, stdin)) {
        if (tmp[strlen(tmp) - 1] == '\n') tmp[strlen(tmp) - 1] = '\0';
        //     cout<<tmp<<endl;
        if (tmp[0] == '@')
            str.push_back(last), last = trim(tmp);
        else
            last += trim(tmp);
        // getchar();
    }
    str.push_back(last);
}

void strHashToNomstr() {
    int len = str.size();
    int cnt = 0, tmpstrlen, pos;
    string tmpstr, s;
    char ch[10];

    cout << "==============筛选出的有用节点信息=================\n";
    for (int i = 0; i < len; i++)
        if (useful_mark[i] == 1) {
            has[i] = cnt++;
            cout << useful_mark[i] << ' ' << str[i] << endl;
        }
    cout << "总结点个数" << cnt << "\n\n\n\n\n" << endl;

    cout << "==============hash编号结果=================\n";
    for (int i = 0; i < len; i++) {
        if (useful_mark[i] == 1) {
            tmpstr = str[i], pos = 0, tmpstrlen = tmpstr.length();
            pos = tmpstr.find('@', pos);
            while (pos != string::npos && pos < tmpstrlen) {
                int t = tmpstr.find(' ', pos);
                s = tmpstr.substr(pos + 1, t - pos - 1);
                sprintf(ch, "%d", has[atoi(s.c_str()) - 1]); /// itoa(has[atoi(s.c_str())-1],ch,10);
                tmpstr.replace(pos + 1, t - pos - 1, ch);
                pos = tmpstr.find('@', pos + 1);
            }
            nomStr.push_back(tmpstr);
            cout << tmpstr << endl;
        }
    }
    cout << "\n\n\n\n\n";
}

void normalizationTextTree() {
    int mark;
    int len1 = FILELEN, len = str.size();
    for (int i = 0; i < len; i++) {
        mark = str[i].find("srcp");
        if (mark != -1) {
            useful_mark[i] = str[i].substr(mark + 5, len1) == FILENAME ? 1 : 0;
        } else
            useful_mark[i] = 2;
    }

    // cout<<"**************************\n*****************************\n*********************************\n";

    int res, pos, t, tmpstrlen;
    string tmpstr, s;
    for (int i = 0; i < len; i++) {
        if (useful_mark[i] == 2) continue;

        res = useful_mark[i] == 1 ? 1 : 0;
        tmpstr = str[i], pos = 0, tmpstrlen = tmpstr.length();
        pos = tmpstr.find('@', pos);
        while (pos != string::npos && pos < tmpstrlen) {
            t = tmpstr.find(' ', pos);
            s = tmpstr.substr(pos + 1, t - pos - 1);
            if (useful_mark[atoi(s.c_str()) - 1] == 2 || useful_mark[atoi(s.c_str()) - 1] == 0) ///如果没有0有些固定参数会丢失
                useful_mark[atoi(s.c_str()) - 1] = res;
            pos = tmpstr.find('@', pos + 1);
        }
    }
    for (int i = 0; i < len; i++) {
        s = str[i];
        int pos = s.find("call_expr");
        if (pos != string::npos) useful_mark[i] = 1;
    }

    strHashToNomstr(); /// hash
}

bool isElimanatenode(string nodename) {
    for (int i = 0; i < STYPES_SIZE; i++)
        if (nodename == simpleTypes[i]) {
            /// cout<<"!!!!!!\n";
            return true;
        }
    return false;
}

bool isElimanate(string nodename, string attrstr, string &restr, int &nodenum) ///根据节点类型判断是否删掉s代表的字段
{
    ///  节点名称        属性节点内容
    restr = "", nodenum = -1;
    /// cout<<"debug iselimanate:nodename="<<nodename<<endl;
    if (isElimanatenode(nodename)) return true;
    if (nodename.compare("identifier_node") == 0 && attrstr.find("lngt") != string::npos) /// identifier_node 标识符节点 lngt在标识符节点中 字符串长度字段
        return true;
    if (nodename.compare("scope_stmt") == 0 && attrstr.compare("begin") != 0 && attrstr.compare("end") != 0 && attrstr.compare("line") != 0 && attrstr.compare("next") != 0)
        return true;
    if (attrstr.find("algn") != string::npos || attrstr.find("srcp") != string::npos) ///字段出现algn srcp来源字段
        return true;

    int pos = 0, num;
    string tmp;
    if ((pos = attrstr.find('@')) != string::npos) {
        tmp = attrstr.substr(pos + 1, attrstr.length() - pos - 1); ///@后的节点号
        num = atoi(tmp.c_str());

        tmp = attrstr.substr(0, pos - 1); ///@之前的内容
        // cout<<tmp<<"33333333333333\n";

        nodenum = num; ///返回@后的节点号
        restr = tmp;   ///@之前的字段
        return num == -1 ? true : false; ///出现了没用或者待定的节点，也就是没有出现在规范语法树中的节点///有用节点
    }
    ///没发现@，也就是没有子节点
    nodenum = -1;
    restr = attrstr;
    return false;
}

void buildTree() {
    int cnt = 0; //节点个数
    int len = nomStr.size(), tmplen, j = 1, eend, cldnum;
    string tmp, subtmp, name, attri;

    for (int i = 0; i < len; i++) {
        tmp = nomStr[i], j = 1, tmplen = tmp.length();
        while (!isalpha(tmp[j]) && j < tmplen) j++;
        eend = tmp.find(' ', j);
        name = tmp.substr(j, eend - j); ///节点名称

        Node node;
        node.nodename = name;
        j = eend + 1;
        while (j < tmplen) {
            eend = tmp.find(':', j);
            while (tmp[eend] != ' ') eend++;
            subtmp = tmp.substr(j, eend - j);
            if (!isElimanate(name, subtmp, attri, cldnum)) {
                //  cout<<"PPPPPPPPPPPPPp\n";
                if (cldnum == -1)
                    node.attribute.push_back(attri);
                else
                    node.edgelist.push_back(Edge(attri, cldnum));
            }
            j = eend + 1;
        }
        nodelist.push_back(node);
        cnt++;
    }
    return;
}

void printTree(string info) {
    int len, cnt = nodelist.size();
    cout << "\n\n\n====================" << info << "=================\n";
    for (int i = 0; i < cnt; i++) {
        if (useful_mark[i] == 0) continue;
        vector<Edge> edge = nodelist[i].edgelist;
        vector<string> attri = nodelist[i].attribute;
        cout << i << ' ' << nodelist[i].nodename << "  有" << edge.size() << "个子节点  "
             << " 有" << attri.size() << "个属性值";

        len = edge.size();
        for (int j = 0; j < len; j++) cout << "==>" << edge[j].attribute << ":@" << edge[j].childnodenum;

        len = attri.size();
        for (int j = 0; j < len; j++) cout << "  ++>" << attri[j];

        cout << endl;
    }
}

string numToStr(int cnt) {
    char ch[10];
    sprintf(ch, "%d", cnt); /// itoa(cnt,ch,10);
    string str(ch);
    return str;
}

int treeNormalization() {
    int fakeroot = -1;

    int len = nodelist.size(), sstart = -1; // return sstart;
    string strmain = "main";
    for (int i = 0; i < len; i++) {
        if (nodelist[i].nodename == "function_decl") {
            int nameidx = nodelist[i].edgelist[0].childnodenum;
            if (nodelist[nameidx].attribute.size() > 0 && nodelist[nameidx].attribute[0].substr(5) == strmain) { ///库函数可能没有name节点需判断
                sstart = i;
                break;
            } else {
                fakeroot = i;
            }
        }
    }

    vector<Edge> tmpedge;
    len = nodelist.size();
    for (int i = 0; i < len; i++) // nite=nodelist.begin(); nite!=nodelist.end(); nite++)
    {
        tmpedge.clear();
        int elen = nodelist[i].edgelist.size();
        for (int j = 0; j < elen; j++) // eite=(*nite).edgelist.begin();eite!=(*nite).edgelist.end();eite++){
        {
            int tmpnum = nodelist[i].edgelist[j].childnodenum;
            if (tmpnum < 0) {
                nodelist[i].edgelist[j] = nodelist[i].edgelist.back();
                nodelist[i].edgelist.pop_back();
                elen--;
                continue;
            }
            if (((fakeroot == -1) && tmpnum < sstart) || ((fakeroot != -1 && tmpnum < fakeroot))) {
                if (nodelist[tmpnum].attribute.size() == 0) {
                    string attri = nodelist[i].edgelist[j].attribute;
                    nodelist[i].attribute.push_back(attri + ":" + nodelist[tmpnum].nodename);
                } else {
                    // cout<<i<<j<<"+++++++++++++++++++\n";
                    int tmpattrilen = nodelist[tmpnum].attribute.size();
                    string attri = nodelist[i].edgelist[j].attribute;
                    for (int k = 0; k < tmpattrilen; k++)
                        nodelist[i].attribute.push_back(attri + "-" + nodelist[tmpnum].attribute[k]);
                }
            } else {
                if (tmpnum < i) {
                    string attri = nodelist[i].edgelist[j].attribute;
                    nodelist[i].attribute.push_back(attri + ":@" + numToStr(tmpnum));
                } else
                    tmpedge.push_back(nodelist[i].edgelist[j]);
            }
        }
        nodelist[i].edgelist = tmpedge;
    }

    return sstart;
}

void nomif_else(int i, int j, int cond_idx) {
    int cnt = 1;
    string strbrc = "branch", strslc = "selection", strcnd = "cond_expr";
    vector<Edge> edgel;
    edgel.clear();
    nodelist.push_back(Node(edgel, strslc));

    int index = nodelist.size() - 1;
    nodelist[i].edgelist[j].childnodenum = index;

    while (nodelist[cond_idx].nodename == strcnd) {
        int tmpidx = nodelist[cond_idx].edgelist.size() == 3 ? nodelist[cond_idx].edgelist[2].childnodenum : -1;
        if (tmpidx < 0) {
            nodelist[cond_idx].nodename = strbrc;
            nodelist[index].edgelist.push_back(Edge(strbrc + numToStr(cnt), cond_idx));
            return;
        }
        nodelist[cond_idx].edgelist.pop_back();
        nodelist[cond_idx].nodename = strbrc;
        nodelist[index].edgelist.push_back(Edge(strbrc + numToStr(cnt), cond_idx));
        cnt++;
        cond_idx = tmpidx;
    }
    edgel.clear();
    nodelist.push_back(Node(edgel, strbrc));
    nodelist[nodelist.size() - 1].edgelist.push_back(Edge("op 0", cond_idx));

    nodelist[index].edgelist.push_back(Edge(strbrc + numToStr(cnt), nodelist.size() - 1));
}

void nomswitch(int i, int j, int switch_idx) {
    // cout<<"come in nomswitch() function!!!\n";
    string strslc = "selection";
    string strbrc = "branch";
    string streqx = "eq_expr";
    string strcnd = "cond";
    string strop0 = "op 0";
    string strop1 = "op 1";
    string strgte = "goto_expr";
    string strcle = "case_label_expr";
    string strstl = "statement_list";
    string strtyp = "type";
    string strexl = "executive_list";
    vector<string> tmpattri;
    int brccnt = 1;
    tmpattri.clear();
    nodelist[switch_idx].nodename = strslc;

    int attrilen = nodelist[switch_idx].attribute.size();
    for (int k = 0; k < attrilen; k++) {
        if (nodelist[switch_idx].attribute[k].substr(0, 4) == strcnd)
            tmpattri.push_back(strop0 + nodelist[switch_idx].attribute[k].substr(4));
        else {
            tmpattri.push_back(nodelist[switch_idx].attribute[k]);
        }
    }

    int body_idx = nodelist[switch_idx].edgelist[0].childnodenum;
    useful_mark[body_idx] = 0;
    nodelist[switch_idx].edgelist.clear();
    int bcldlen = nodelist[body_idx].edgelist.size();
    vector<Edge> newedge, stateList, edgel = nodelist[body_idx].edgelist;
    vector<int> caseExp;
    vector<string> caseattri;
    // cout<<"+++++++nodename list:+++++++++++++\n";
    for (int i = 0; i < bcldlen; i++) {
        // cout<<nodelist[ edgel[i].childnodenum ].nodename<<endl;
        if (nodelist[edgel[i].childnodenum].nodename == strcle) {
            caseExp.push_back(i);
            nodelist[edgel[i].childnodenum].nodename = streqx;
        }
    }
    for (int x = 0; x < caseExp.size(); x++) {
        // cout<<"come in branchadd for loop!!!\n";
        i = caseExp[x];
        int mark = nodelist[edgel[i].childnodenum].attribute.size() < 2 ? 1 : 0;
        for (int j = 0; j < nodelist[edgel[i].childnodenum].edgelist.size(); j++) /// case_label_expr子节点转属性 后清空子节点
        {
            string attri = nodelist[edgel[i].childnodenum].edgelist[j].attribute;
            int tmpnum = nodelist[edgel[i].childnodenum].edgelist[j].childnodenum;
            nodelist[edgel[i].childnodenum].attribute.push_back(attri + ":@" + numToStr(tmpnum));
            useful_mark[tmpnum] = 0;
        }
        nodelist[edgel[i].childnodenum].edgelist.clear();

        caseattri = tmpattri;
        for (int j = 0, pos; j < nodelist[edgel[i].childnodenum].attribute.size(); j++) {
            if (nodelist[edgel[i].childnodenum].attribute[j].substr(0, 4) != strtyp) {
                if ((pos = nodelist[edgel[i].childnodenum].attribute[j].find('-')) != string::npos) {
                    caseattri.push_back(strop1 + nodelist[edgel[i].childnodenum].attribute[j].substr(pos));
                } else {
                    caseattri.push_back(nodelist[edgel[i].childnodenum].attribute[j]);
                }
            }
        }

        int j = i + 1, cnt = 0;
        newedge.clear();
        stateList.clear();
        nodelist[edgel[i].childnodenum].attribute = caseattri;
        if (!(x == caseExp.size() - 1 && mark)) {
            newedge.push_back(Edge(strop0, edgel[i].childnodenum));
        }

        while (j < bcldlen && nodelist[edgel[j].childnodenum].nodename != strgte) {
            if (nodelist[edgel[j].childnodenum].nodename != streqx) {
                nodelist.push_back(nodelist[edgel[j].childnodenum]);
                stateList.push_back(Edge(numToStr(cnt) + " ", nodelist.size() - 1));
                useful_mark[edgel[j].childnodenum] = 0;
            }
            j++;
        }
        if (j < bcldlen && nodelist[edgel[j].childnodenum].nodename == strgte) ///添加goto_expr 如果将switch中的goto标准化为break，则注释掉
        {
            ; // stateList.push_back(Edge(numToStr(cnt)+" ",edgel[j].childnodenum));
        }

        if (stateList.size() == 1) {
            cout << "debug : child number:" << stateList[0].childnodenum << endl;
            newedge.push_back(Edge(strop1, stateList[0].childnodenum));
            useful_mark[stateList[0].childnodenum] = 1;
        } else {
            nodelist.push_back(Node(stateList, strstl));
            newedge.push_back(Edge(strop1, nodelist.size() - 1));
        }

        /*else{
           useful_mark[edgel[i+1].childnodenum] = 1;
           newedge.push_back(Edge(strop1,edgel[i+1].childnodenum));
        }*/

        nodelist.push_back(Node(newedge, strbrc));
        nodelist[switch_idx].edgelist.push_back(Edge(strbrc + numToStr(brccnt++), nodelist.size() - 1));
    }
}
bool mark[1000];

void nomfor_while_dowhile(int stateidx) {
    vector<Edge> edge = nodelist[stateidx].edgelist;
    string strlbe = "label_expr";
    int len = edge.size();
    for (int i = 0; i < len; i++) {
        if (nodelist[edge[i].childnodenum].nodename == strlbe) {
            string attri = nodelist[edge[i].childnodenum].edgelist[0].attribute;
            int num = nodelist[edge[i].childnodenum].edgelist[0].childnodenum;
            nodelist[edge[i].childnodenum].attribute.push_back(attri + numToStr(num));
            nodelist[edge[i].childnodenum].edgelist.pop_back();
        }
    }
}

void nomwhile() {
    ;
}

void nomdo_while() {
    ;
}

void normalizeLoopAndCase() {
    // return ;
    memset(useful_mark, -1, sizeof(int) * (nodelist.size() + 100));
    int len = nodelist.size();
    string strcond = "cond_expr", strswh = "switch_expr", strgtx = "statement_list";
    for (int i = 0; i < len; i++) {
        /// cout<<"debug normalizeLoopAndCase "<<i<<' '<<nodelist[i].nodename<<endl;
        int elen = nodelist[i].edgelist.size();
        for (int j = 0; j < elen; j++) {
            int cld_idx = nodelist[i].edgelist[j].childnodenum;
            cout << "++++++++++++++++" << cld_idx << endl;
            if (nodelist[cld_idx].nodename == strcond) {
                nomif_else(i, j, cld_idx);
            } else if (nodelist[cld_idx].nodename == strswh) {
                nomswitch(i, j, cld_idx);
            } else if (nodelist[cld_idx].nodename == strgtx) {
                nomfor_while_dowhile(cld_idx);
            } else if (0) {
                nomwhile();
            } else if (0) {
                nomdo_while();
            }
        }
    }

    return;
}

void normalizeCall() {
    cout << "\n\n\ndebug log: come in normalizeCall\n";
    string strcon = ":@";
    int visit[MAXNODE];
    memset(visit, 0, sizeof visit);
    int len = nodelist.size();
    for (int i = 0; i < len; i++) {
        int elen = nodelist[i].edgelist.size();
        vector<Edge> edge = nodelist[i].edgelist;
        for (int j = 0; j < elen; j++) {
            if (!visit[edge[j].childnodenum])
                visit[edge[j].childnodenum] = 1;
            else {
                cout << "i=" << i << " j=" << j
                     << "  convert to attribute:" << edge[j].attribute + strcon + numToStr(edge[j].childnodenum) << endl;
                nodelist[i].attribute.push_back(edge[j].attribute + strcon + numToStr(edge[j].childnodenum));
                nodelist[i].edgelist[j] = nodelist[i].edgelist.back();
                nodelist[i].edgelist.pop_back();
            }
        }
    }
    cout << "\n\n\n";
}

void ini() {
    memset(useful_mark, -1, sizeof useful_mark); /// 0无用 1有用 2待定
    memset(has, -1, sizeof has);
    str.clear();
    nomStr.clear();
    nodelist.clear();
}

vector<Node> TextToTree::convert(int &root, const char InputFileName[], const char OutputFileName[], const char filename[]) {
    strcpy(FILENAME, filename);
    FILELEN = strlen(filename);
    //   cout<<"debug : >>>ini()   \n";
    ini();
    int rootnum; ///树节点个数
    freopen(InputFileName, "r", stdin);
    FILE *fp = freopen(OutputFileName, "w", stdout);
    // cout<<"debug : >>>getstr";
    getstr();
    //    cout<<"debug: come in normalizationTextTree\n";
    normalizationTextTree();
    if (nomStr.size() == 0) {
        printf("There is no node,Please check the input path or srcp file name!!!\n");
        cout << "return nodelist.size()=" << nodelist.size();
        return nodelist;
    }

    /// cout<<"debug"<<nomStr.size()<<endl;

    buildTree();
    memset(useful_mark, -1, sizeof(int) * nodelist.size());
    printTree("节点信息筛选后生成的树结构");

    root = treeNormalization();
    printTree("生成树结构后二次标准化(图->树   子节点->属性节点)");
    printf("\n\n到目前为止获得的根节点为%d，前面的标号已经在树中剔除！！！\n\n", root);

    normalizeLoopAndCase();
    printTree("生成树结构后三次标准化(循环语句和选择语句)");

    normalizeCall();
    printTree("最后一次调用出现环规范化！！！");

    // fflush(fp);//将输出缓冲区清空

    fclose(stdout);
    fclose(stdin);

    // printTree("结果返回之前的结果");
    /*
    cout<<"结果返回之前的结果:\n"<<endl;
    for(int i=0;i<nodelist.size();i++)
       cout<<nodelist[i].nodename<<' '<<nodelist[i].index<<' '<<nodelist[i].leftmost<<' '<<nodelist[i].edgelist.size()<<endl;
    */
    return nodelist;
}

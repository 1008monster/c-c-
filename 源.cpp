
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include <fstream>  
#include <iomanip>  
#include<ctime>
using namespace std;
FILE* f3;
void SiZeYS(int NumS, int SuanF, int MaxS, int KuoH, int XiaoS, int WJ);
int main()
{
    int NumS;//题目数量
    int SuanF;//算法
    int MaxS;//最大数
    int KuoH;//是否有括号
    int XiaoS;//是否有小数
    int WJ;//输出到文件
    f3 = fopen("stud.txt", "w");
    cout << "请输入生成题目数量：\n";
    cin >> NumS;
    while (1)
    {
        if (NumS > 100 || NumS <= 0)
        {
            cout << "输入错误\n";
            system("pause");
            cin >> NumS;
        }
        else
            break;
    }
    cout << "请输入生成题目类型：\n";
    cout << "1.加法 2.减法 3.加减混合法 4.乘法 5.除法 6乘除混合法 7加减乘除法\n";
    cin >> SuanF;
    while (1)
    {
        if ((SuanF != 1) && (SuanF != 2) && (SuanF != 3) && (SuanF != 4) && (SuanF != 5) && (SuanF != 6) && (SuanF != 7))
        {
            cout << "输入错误\n";
            system("pause");
            cin >> SuanF;
        }
        else
            break;
    }
    cout << "请输入生成最大数：\n";
    cin >> MaxS;
    while (1)
    {
        if (MaxS < 0 || MaxS>10000)
        {
            cout << "输入错误\n";
            system("pause");
            cin >> MaxS;
        }
        else
            break;
    }
    if (SuanF == 7)
    {
        cout << "请输入是否有括号：\n";
        cout << "1.没有 2.有\n";
        cin >> KuoH;
        while (1)
        {
            if (KuoH != 1 && KuoH != 2)
            {
                cout << "输入错误\n";
                system("pause");
                cin >> KuoH;
            }
            else
                break;
        }
    }
    cout << "请输入是否有小数：\n";
    cout << "1.没有 2.有\n";
    cin >> XiaoS;
    while (1)
    {
        if (XiaoS != 1 && XiaoS != 2)
        {
            cout << "输入错误\n";
            system("pause");
            cin >> XiaoS;
        }
        else
            break;
    }
    //SiZeYS(NumS,SuanF,MaxS,KuoH,XiaoS);//四则运算调用函数
    cout << "是否要输出文件：\n";
    cout << "1.不需要 2.需要\n";
    cin >> WJ;
    while (1)
    {
        if (WJ > 2 || WJ < 1)
        {
            cout << "输入错误\n";
            system("pause");
            cin >> NumS;
        }
        else
            break;
    }
    SiZeYS(NumS, SuanF, MaxS, KuoH, XiaoS, WJ);//四则运算调用函数
    system("pause");
    return 0;
}
void  SiZeYS(int NumS, int SuanF, int MaxS, int KuoH, int XiaoS, int WJ)
{
    //f3 = fopen("stud.txt", "w");
    int i;
    srand((unsigned int)time(0));
    double A[1000];
    double B[1000];
    double C[1000];
    double D[1000];
    for (i = 0;i < NumS;i++)
    {
        A[i] = rand() % MaxS + 1;
        B[i] = rand() % MaxS + 1;
        C[i] = rand() % MaxS + 1;
        D[i] = rand() % MaxS + 1;
        //fout<<A[i]<<"+"<<B[i]<<"="<<endl;
        //cout<<A[i]<<C[i]<<B[i]<< D[i]<<endl;
    }
    if (XiaoS == 2)
    {
        for (i = 0;i < NumS;i++)
        {
            A[i] = A[i] * 0.01;
            B[i] = B[i] * 0.01;
            C[i] = C[i] * 0.01;
            D[i] = D[i] * 0.01;
        }
    }
    if (SuanF == 1)//加法运算
    {
        for (i = 0;i < NumS;i++)
        {
            if (WJ == 1)
                cout << A[i] << "+" << B[i] << "+" << C[i] << "+" << D[i] << "=" << endl;
            if (WJ == 2)
                fprintf(f3, "%.4lf+%.4lf+%.4lf+%.4lf=\n", A[i], B[i], C[i], D[i]);

        }
    }
    if (SuanF == 2)//减法运算
    {
        for (i = 0;i < NumS;i++)
        {
            if (WJ == 1)
                cout << A[i] << "-" << B[i] << "-" << C[i] << "-" << D[i] << "=" << endl;
            if (WJ == 2)
                fprintf(f3, "%.4lf-%.4lf-%.4lf-%.4lf=\n", A[i], B[i], C[i], D[i]);
        }
    }
    if (SuanF == 3)//加减运算
    {
        for (i = 0;i < NumS;i++)
        {
            if (i % 2 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "+" << B[i] << "+" << C[i] << "-" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf+%.4lf+%.4lf-%.4lf=\n", A[i], B[i], C[i], D[i]);

            }
            else if (i % 3 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "+" << B[i] << "-" << C[i] << "+" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf+%.4lf-%.4lf+%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
            else if (i % 5 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "+" << B[i] << "-" << C[i] << "-" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf+%.4lf-%.4lf-%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
            else if (i % 7 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "-" << B[i] << "+" << C[i] << "+" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf-%.4lf+%.4lf+%.4lf=\n", A[i], B[i], C[i], D[i]);

            }
            else
            {
                if (WJ == 1)
                    cout << A[i] << "-" << B[i] << "+" << C[i] << "-" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf-%.4lf+%.4lf-%.4lf=\n", A[i], B[i], C[i], D[i]);

            }
        }
    }
    if (SuanF == 4)//乘法运算
    {
        for (i = 0;i < NumS;i++)
        {
            if (WJ == 1)
                cout << A[i] << "*" << B[i] << "*" << C[i] << "*" << D[i] << "=" << endl;
            if (WJ == 2)
                fprintf(f3, "%.4lf*%.4lf*%.4lf*%.4lf=\n", A[i], B[i], C[i], D[i]);

        }
    }
    if (SuanF == 5)//除法运算
    {
        for (i = 0;i < NumS;i++)
        {
            if (WJ == 1)
                cout << A[i] << "/" << B[i] << "/" << C[i] << "/" << D[i] << "=" << endl;
            if (WJ == 2)
                fprintf(f3, "%.4lf/%.4lf/%.4lf/%.4lf=\n", A[i], B[i], C[i], D[i]);
        }
    }
    if (SuanF == 6)//乘除运算
    {
        for (i = 0;i < NumS;i++)
        {
            if (i % 2 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "*" << B[i] << "*" << C[i] << "/" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf*%.4lf*%.4lf/%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
            else if (i % 3 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "*" << B[i] << "/" << C[i] << "*" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf*%.4lf/%.4lf*%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
            else if (i % 5 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "/" << B[i] << "*" << C[i] << "*" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf/%.4lf*%.4lf*%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
            else if (i % 7 == 0)
            {
                if (WJ == 1)
                    cout << A[i] << "/" << B[i] << "*" << C[i] << "*" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf/%.4lf*%.4lf*%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
            else
            {
                if (WJ == 1)
                    cout << A[i] << "/" << B[i] << "*" << C[i] << "/" << D[i] << "=" << endl;
                if (WJ == 2)
                    fprintf(f3, "%.4lf/%.4lf*%.4lf/%.4lf=\n", A[i], B[i], C[i], D[i]);
            }
        }
    }
    if (SuanF == 7)//四则混合运算
    {
        if (KuoH == 2)//四则运算中有括号
        {
            for (i = 0;i < NumS;i++)
            {
                if (i % 2 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "*" << B[i] << "-" << C[i] << "+" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf*%.4lf-%.4lf+%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else if (i % 3 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "+" << B[i] << "*" << "(" << C[i] << "-" << D[i] << ")" << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf+%.4lf*(%.4lf-%.4lf)=\n", A[i], B[i], C[i], D[i]);
                }
                else if (i % 5 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "+" << B[i] << "*" << C[i] << "-" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf+%.4lf*%.4lf-%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else if (i % 7 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "+" << "(" << B[i] << "-" << C[i] << ")" << "*" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf+(%.4lf-%.4lf)*%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else
                {
                    if (WJ == 1)
                        cout << A[i] << "/" << "(" << B[i] << "+" << C[i] << ")" << "-" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf/(%.4lf+%.4lf)-%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
            }
        }
        if (KuoH == 1)//四则运算中没有括号
        {
            for (i = 0;i < NumS;i++)
            {
                if (i % 2 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "*" << B[i] << "-" << C[i] << "+" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf*%.4lf-%.4lf+%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else if (i % 3 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "+" << B[i] << "*" << C[i] << "-" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf+%.4lf*%.4lf-%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else if (i % 5 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "+" << B[i] << "*" << C[i] << "+" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf+%.4lf*%.4lf+%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else if (i % 7 == 0)
                {
                    if (WJ == 1)
                        cout << A[i] << "+" << B[i] << "-" << C[i] << "/" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf+%.4lf-%.4lf/%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
                else
                {
                    if (WJ == 1)
                        cout << A[i] << "/" << B[i] << "-" << C[i] << "*" << D[i] << "=" << endl;
                    if (WJ == 2)
                        fprintf(f3, "%.4lf/%.4lf-%.4lf*%.4lf=\n", A[i], B[i], C[i], D[i]);
                }
            }
        }
    }
}